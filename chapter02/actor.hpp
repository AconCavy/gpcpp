#ifndef GPCPP_CHAPTER02_ACTOR_HPP_
#define GPCPP_CHAPTER02_ACTOR_HPP_

#include <vector>
#include "vector2.hpp"

namespace gpcpp::c02 {

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
  [[nodiscard]] const gpcpp::Vector2 &getPosition() const { return Position; }
  void setPosition(const gpcpp::Vector2 &P) { Position = P; }
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

private:
  State State;
  gpcpp::Vector2 Position;
  float Rotation;
  float Scale;
  std::vector<class Component *> Component;
  class Game *Game;
};

} // namespace gpcpp::c02

#endif //GPCPP_CHAPTER02_ACTOR_HPP_
