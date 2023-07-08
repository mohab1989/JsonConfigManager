#pragma once
#include <vector>
#include <set>
#include "NumericProperty.hpp"
#include "ChoiceProperty.hpp"

namespace ConfigurationManager {

class Group {
 private:
  std::vector<NumericProperty> m_numericProperties;
  std::vector<ChoiceProperty> m_choiceProperties;
  std::vector<Group> m_subgroups;
 public:

  Group(const std::string& name);
  //Append(std::vector<IConfigurableProperty>);
};
}  // namespace ConfigurationManager