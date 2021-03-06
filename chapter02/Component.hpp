#ifndef GPCPP_CHAPTER02_COMPONENT_HPP
#define GPCPP_CHAPTER02_COMPONENT_HPP

namespace gpcpp::c02 {

class Component {
public:
  explicit Component(class Actor *Owner, int UpdateOrder = 100);
  virtual ~Component();
  virtual void update(float DeltaTime);

  [[nodiscard]] int getUpdateOrder() const { return UpdateOrder; }

protected:
  class Actor *Owner;
  int UpdateOrder;
};

} // namespace gpcpp::c02

#endif // GPCPP_CHAPTER02_COMPONENT_HPP
