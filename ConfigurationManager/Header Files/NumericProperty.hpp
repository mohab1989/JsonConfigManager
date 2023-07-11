#pragma once
#ifdef CONFIGURATION_MANAGER_EXPORTS
#define CONFIGURATION_MANAGER __declspec(dllexport)
#else
#define CONFIGURATION_MANAGER __declspec(dllimport)
#endif

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

class NumericProperty : public IConfigurableProperty {
 private:
  Minimum m_minimum;
  Maximum m_maximum;

 public:
  CONFIGURATION_MANAGER NumericProperty() = default;
  CONFIGURATION_MANAGER NumericProperty(const std::string& name,
                  const Minimum& minimum = Minimum(),
                  const Maximum& maximum = Maximum());

  CONFIGURATION_MANAGER auto getValue() const -> std::any override;
  CONFIGURATION_MANAGER auto setValue(const std::any&)->bool override;
};
}  // namespace ConfigurationManager