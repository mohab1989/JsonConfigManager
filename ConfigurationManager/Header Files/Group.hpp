#pragma once
#include <vector>
#include <set>
#include "NumericProperty.hpp"
#include "ChoiceProperty.hpp"
#include "IConfigurableProperty.hpp"

enum PropertyType {
  ChoiceProperty,
  Numeric,
  Value3
};
namespace ConfigurationManager {

    class Group {
     private:
      std::vector<IConfigurableProperty> m_numericProperties;
      std::vector<ChoiceProperty> m_choiceProperties;
      std::vector<Group> m_subgroups;
     public:

      Group(const std::string& name);
      //Append(std::vector<IConfigurableProperty>);
    };
}  // namespace ConfigurationManager