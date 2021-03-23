#ifndef GPCPP_CHAPTER03_POSITIONWRAPCOMPONENT_HPP
#define GPCPP_CHAPTER03_POSITIONWRAPCOMPONENT_HPP

#include "component.hpp"

namespace gpcpp::c03 {

class PositionWrapComponent : public Component {
public:
  explicit PositionWrapComponent(class Actor *Owner, int UpdateOrder = 11);

  void update(float DeltaTime) override;

  void setWidth(float W) { Width = W; }
  void setHeight(float H) { Height = H; }
  void setMargin(float M) { Margin = M; }

private:
  float Width;
  float Height;
  float Margin;
};

} // namespace gpcpp::c03

#endif //GPCPP_CHAPTER03_POSITIONWRAPCOMPONENT_HPP
