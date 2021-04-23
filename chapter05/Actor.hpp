#ifndef GPCPP_CHAPTER05_ACTOR_HPP
#define GPCPP_CHAPTER05_ACTOR_HPP

#include <glm/glm.hpp>
#include <vector>

namespace gpcpp::c05 {

class Actor {
public:
  enum State { Active, Paused, Dead };

  explicit Actor(class Game *Game);
  virtual ~Actor();

  void update(float DeltaTime);
  void updateComponents(float DeltaTime);
  virtual void updateActor(float DeltaTime);
  void addComponent(class Component *C);
  void removeComponent(class Component *C);
  void processInput(const uint8_t *KeyState);
  void computeWorldTransform();
  virtual void ActorInput(const uint8_t *KeyState);

  [[nodiscard]] State getState() const { return State; }
  [[nodiscard]] const glm::vec2 &getPosition() const { return Position; }
  [[nodiscard]] float getRotation() const { return Rotation; }
  [[nodiscard]] glm::vec2 getForward() const {
    return {glm::cos(Rotation), -glm::sin(Rotation)};
  }
  [[nodiscard]] float getScale() const { return Scale; }
  class Game *getGame() {
    return Game;
  }
  [[nodiscard]] const glm::mat4 &getWorldTransform() const {
    return WorldTransform;
  }

  void setState(State S) {
    State = S;
    RecomputeWorldTransform = true;
  }
  void setPosition(const glm::vec2 &P) {
    Position = P;
    RecomputeWorldTransform = true;
  }
  void setRotation(float R) {
    Rotation = R;
    RecomputeWorldTransform = true;
  }
  void setScale(float S) {
    Scale = S;
    RecomputeWorldTransform = true;
  }

private:
  State State;

  glm::mat4 WorldTransform;
  bool RecomputeWorldTransform;

  glm::vec2 Position;
  float Rotation;
  float Scale;
  std::vector<class Component *> Components;
  class Game *Game;
};

} // namespace gpcpp::c05

#endif // GPCPP_CHAPTER05_ACTOR_HPP
