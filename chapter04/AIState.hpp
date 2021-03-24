#ifndef GPCPP_CHAPTER04_AISTATE_HPP
#define GPCPP_CHAPTER04_AISTATE_HPP

namespace gpcpp::c04 {

class AIState {
public:
  explicit AIState(class AIComponent *Owner) : Owner(Owner) {}

  virtual void update(float DeltaTime) = 0;
  virtual void onEnter() = 0;
  virtual void onExit() = 0;
  [[nodiscard]] virtual const char *getName() const = 0;

protected:
  class AIComponent *Owner;
};

class AIPatrol : public AIState {
public:
  explicit AIPatrol(class AIComponent *Owner) : AIState(Owner) {}

  void update(float DeltaTime) override;
  void onEnter() override;
  void onExit() override;
  [[nodiscard]] const char *getName() const override { return "Patrol"; }
};

class AIDeath : public AIState {
public:
  explicit AIDeath(class AIComponent *Owner) : AIState(Owner) {}

  void update(float DeltaTime) override;
  void onEnter() override;
  void onExit() override;
  [[nodiscard]] const char *getName() const override { return "Death"; }
};

class AIAttack : public AIState {
public:
  explicit AIAttack(class AIComponent *Owner) : AIState(Owner) {}

  void update(float DeltaTime) override;
  void onEnter() override;
  void onExit() override;
  [[nodiscard]] const char *getName() const override { return "Attack"; }
};

} // namespace gpcpp::c04

#endif // GPCPP_CHAPTER04_AISTATE_HPP
