#ifndef GPCPP_CHAPTER03_ACTOR_HPP
#define GPCPP_CHAPTER03_ACTOR_HPP

#include <vector>
#include <glm/glm.hpp>

namespace gpcpp::c03 {

class Actor {
public:
  enum State {
	Active,
	Paused,
	Dead
  };

  explicit Actor(class Game *Game);
  virtual ~Actor();

  [[nodiscard]] State getState() const { return State; }
  void setState(State S) { State = S; }
  [[nodiscard]] const glm::vec2 &getPosition() const { return Position; }
  void setPosition(const glm::vec2 &P) { Position = P; }
  [[nodiscard]] float getRotation() const { return Rotation; }
  void setRotation(float R) { Rotation = R; }
  [[nodiscard]] float getScale() const { return Scale; }
  void setScale(float S) { Scale = S; }
  class Game *getGame() { return Game; }

  void update(float DeltaTime);
  void updateComponents(float DeltaTime);
  virtual void updateActor(float DeltaTime);
  void addComponent(class Component *C);
  void removeComponent(class Component *C);
  void processInput(const uint8_t *KeyState);
  virtual void ActorInput(const uint8_t *KeyState);

private:
  State State;
  glm::vec2 Position;
  float Rotation;
  float Scale;
  std::vector<class Component *> Components;
  class Game *Game;
};

} // namespace gpcpp::c03

#endif //GPCPP_CHAPTER03_ACTOR_HPP
