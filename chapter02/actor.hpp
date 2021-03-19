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
  void SetState(State state) { _state = state; }
  const gpcpp::utils::Vector2 &GetPosition() const { return _position; }
  void SetPosition(const gpcpp::utils::Vector2 &position) { _position = position; }
  float GetRotation() const { return _rotation; }
  void SetRotation(float rotation) { _rotation = rotation; }
  float GetScale() const { return _scale; }
  void SetScale(float scale) { _scale = scale; }
  class Game *GetGame() { return _game; }

  void Update(float deltaTime);
  void UpdateComponents(float deltaTime);
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
