#include "Game.hpp"

#include "Actor.hpp"
#include "Asteroid.hpp"
#include "Math.hpp"
#include "Shader.hpp"
#include "Ship.hpp"
#include "SpriteComponent.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"

using namespace gpcpp::c05;

const int NumberOfAsteroid = 20;

Game::Game()
    : Window(nullptr), Context(nullptr), IsRunning(true), UpdatingActors(false),
      TicksCount(0), Ship(nullptr) {}

bool Game::initialize() {
  int SDLResult = SDL_Init(SDL_INIT_VIDEO);
  if (SDLResult != 0) {
    SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
    return false;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

  Window = SDL_CreateWindow("Game Programming in C++ (Chapter 05)", 100, 100,
                            Width, Height, SDL_WINDOW_OPENGL);
  if (!Window) {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    return false;
  }

  Context = SDL_GL_CreateContext(Window);
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    SDL_Log("Failed to initialize GLEW");
    return false;
  }

  glGetError();

  if (!loadShaders()) {
    SDL_Log("Failed to load shaders");
    return false;
  }

  createSpriteVertices();

  loadData();
  TicksCount = SDL_GetTicks();

  return true;
}

void Game::runLoop() {
  while (IsRunning) {
    processInput();
    updateGame();
    generateOutput();
  }
}
void Game::shutdown() {
  unloadData();
  delete SpriteVertexArray;
  SpriteShader->unload();
  delete SpriteShader;
  SDL_GL_DeleteContext(Context);
  SDL_DestroyWindow(Window);
  SDL_Quit();
}

void Game::addActor(Actor *A) {
  if (UpdatingActors)
    PendingActors.emplace_back(A);
  else
    Actors.emplace_back(A);
}

void Game::removeActor(Actor *A) {
  auto E = PendingActors.end();
  auto I = std::find(PendingActors.begin(), E, A);
  if (I != E) {
    std::iter_swap(I, E - 1);
    PendingActors.pop_back();
  }

  E = Actors.end();
  I = std::find(Actors.begin(), E, A);
  if (I != E) {
    std::iter_swap(I, E - 1);
    Actors.pop_back();
  }
}

void Game::addSprite(SpriteComponent *SC) {
  auto Order = SC->getDrawOrder();
  auto I = Sprites.begin();
  for (; I != Sprites.end(); ++I) {
    if (Order < (*I)->getDrawOrder()) {
      break;
    }
  }
  Sprites.insert(I, SC);
}

void Game::removeSprite(SpriteComponent *SC) {
  auto E = Sprites.end();
  auto I = std::find(Sprites.begin(), Sprites.end(), SC);
  if (I != E)
    Sprites.erase(I);
}

void Game::addAsteroid(struct Asteroid *A) { Asteroids.emplace_back(A); }

void Game::removeAsteroid(struct Asteroid *A) {
  auto E = Asteroids.end();
  auto I = std::find(Asteroids.begin(), E, A);
  if (I != E)
    Asteroids.erase(I);
}

Texture *Game::getTexture(const std::string &FileName) {
  Texture *T = nullptr;
  auto I = Textures.find(FileName);
  if (I != Textures.end()) {
    T = I->second;
    return T;
  }

  T = new Texture();
  if (T->load(FileName)) {
    Textures.emplace(FileName.c_str(), T);
  } else {
    delete T;
    T = nullptr;
  }
  return T;
}

void Game::processInput() {
  SDL_Event Event;
  while (SDL_PollEvent(&Event)) {
    switch (Event.type) {
    case SDL_QUIT:
      IsRunning = false;
      break;
    }
  }

  const uint8_t *State = SDL_GetKeyboardState(nullptr);
  if (State[SDL_SCANCODE_ESCAPE])
    IsRunning = false;

  UpdatingActors = true;
  for (auto A : Actors) {
    A->processInput(State);
  }
  UpdatingActors = false;
}

void Game::updateGame() {
  while (!SDL_TICKS_PASSED(SDL_GetTicks(), TicksCount + DeltaCount))
    ;
  Uint32 CurrentTicks = SDL_GetTicks();
  float DeltaTime =
      std::min(static_cast<float>(CurrentTicks - TicksCount) / 1000, 0.05f);
  TicksCount = CurrentTicks;

  UpdatingActors = true;
  for (auto A : Actors) {
    A->update(DeltaTime);
  }
  UpdatingActors = false;

  for (auto A : PendingActors) {
    A->computeWorldTransform();
    Actors.emplace_back(A);
  }
  PendingActors.clear();

  std::vector<Actor *> DeadActors;
  for (auto A : Actors) {
    if (A->getState() == Actor::Dead)
      DeadActors.emplace_back(A);
  }

  for (auto A : DeadActors) {
    delete A;
  }
}

void Game::generateOutput() {
  glClearColor(0.86f, 0.86f, 0.86f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  SpriteShader->setActive();
  SpriteVertexArray->setActive();
  for (auto S : Sprites) {
    S->draw(SpriteShader);
  }

  SDL_GL_SwapWindow(Window);
}

bool Game::loadShaders() {
  SpriteShader = new Shader();
  if (!SpriteShader->load("shaders/Transform.vert", "shaders/Basic.frag"))
    return false;

  SpriteShader->setActive();

  auto ViewProjection = createSimpleViewProjection(static_cast<float>(Width),
                                                   static_cast<float>(Height));
  SpriteShader->setMatrixUniform("uViewProjection", ViewProjection);

  return true;
}

void Game::createSpriteVertices() {

  float vertices[] = {
      -0.5f, 0.5f,  0.0f, 0.0f, 0.0f, // v0
      0.5f,  0.5f,  0.0f, 1.0f, 0.0f, // v1
      0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, // v2
      -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // v3
  };

  unsigned int indices[] = {0, 1, 2, 2, 3, 0};

  SpriteVertexArray = new VertexArray(vertices, 4, indices, 6);
}

void Game::loadData() {
  Ship = new class Ship(this);
  Ship->setPosition({Width / 2, Height / 2});
  Ship->setRotation(static_cast<float>(gpcpp::PI / 2));

  for (int I = 0; I < NumberOfAsteroid; ++I) {
    new Asteroid(this);
  }
}

void Game::unloadData() {
  while (!Actors.empty()) {
    delete Actors.back();
  }

  for (const auto &I : Textures) {
    I.second->unload();
    delete I.second;
  }

  Textures.clear();
}
