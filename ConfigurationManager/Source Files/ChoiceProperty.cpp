#include "ChoiceProperty.hpp"

namespace ConfigurationManager {
ChoiceProperty::ChoiceProperty(
    const std::string name, std::set<std::string>& acceptedStrings,
    const std::set<double>& accpetedNumericProperties) {
  this->m_name = name;
  this->m_acceptedStrings = acceptedStrings;
  this->m_accpetedNumericProperties = accpetedNumericProperties;
}

auto ChoiceProperty::setValue(const std::any& value)
    -> bool {
  // Get the type of std::any object
  const std::type_info& type = value.type();

  if (type == typeid(std::string)) {
    auto it = m_acceptedStrings.find(std::any_cast<std::string>(value));
    if (it == m_acceptedStrings.end()) {
      return false;
    }
  } else if (type == typeid(double)) {
    auto it = m_accpetedNumericProperties.find(std::any_cast<double>(value));
    if (it == m_accpetedNumericProperties.end()) {
      return false;
    }
  }
  else {
    return false;
  }

  m_value = value;
  return true;
}

auto ChoiceProperty::getValue() const -> std::any {
  return m_value;
}
}  // namespace ConfigurationManager