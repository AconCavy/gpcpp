#ifndef GPCPP_CHAPTER02_COMPONENT_HPP
#define GPCPP_CHAPTER02_COMPONENT_HPP

namespace gpcpp::c02 {

class Component {
public:
  Component(class Actor *owner, int updateOrder = 100);
  virtual ~Component();
  virtual void Update(float deltaTime);
  int GetUpdateOrder() const { return _updateOrder; }

protected:
  class Actor *_owner;
  int _updateOrder;
};

} // namespace gpcpp::c02

#endif //GPCPP_CHAPTER02_COMPONENT_HPP
