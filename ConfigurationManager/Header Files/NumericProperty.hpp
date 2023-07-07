#pragma once
#include"IConfigurableProperty.hpp"

namespace ConfigurationManager {
struct Minimum {
  double value = std::numeric_limits<double>::min();
  bool minimumExclusive = false;
};

struct Maximum {
  double value = std::numeric_limits<double>::max();
  bool maximumExclusive = false;
};

class NumericProperty : public IConfigurableProperty<double> {
 private:
  Minimum m_minimum;
  Maximum m_maximum;

 public:
  NumericProperty(const std::string& name, const Minimum& minimum = Minimum(),
                  const Maximum& maximum = Maximum());

  auto setValue(const double&) -> bool override;
  virtual auto getValue() -> double override;
};
}  // namespace ConfigurationManager