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

  Actor(class Game *game);
  virtual ~Actor();

  State GetState() const { return _state; }
  const gpcpp::utils::Vector2 &GetPosition() const { return _position; }
  float GetRotation() const { return _rotation; }
  float GetScale() const { return _scale; }

  void Update(float deltaTime);
  void Draw();
  virtual void UpdateActor(float deltaTime);
  void AddComponent(class Component *component);
  void RemoveComponent(class Component *component);

private:
  State _state;
  gpcpp::utils::Vector2 _position;
  float _rotation;
  float _scale;
  std::vector<class Component *> _components;
  class Game *_game;
};

} // namespace gpcpp::c02

#endif //GPCPP_CHAPTER02_ACTOR_HPP_
