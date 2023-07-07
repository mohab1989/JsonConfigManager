#include <fstream>
#include "pch.h"
#include "ConfigurationManager.hpp"
#include "ChoiceProperty.hpp"
#include "IConfigurableProperty.hpp"

namespace ConfigurationManager {
TEST(TestChoiceProperty, SetValueStringAllowedReturnsTrue) {
  std::string p = "";
  std::set<std::string> p1{""};
  std::set<double> p2{2};
  auto c = ChoiceProperty(p, p1, p2);
  IConfigurableProperty<std::variant<std::string, double>>* p3 = &c;
}
}  // namespace ConfigurationManager