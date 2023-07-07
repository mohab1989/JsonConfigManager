#include "ChoiceProperty.hpp"

namespace ConfigurationManager {
ChoiceProperty::ChoiceProperty(
    const std::string name, std::set<std::string>& acceptedStrings,
    const std::set<double>& accpetedNumericProperties) {
  this->m_name = name;
  this->m_acceptedStrings = acceptedStrings;
  this->m_accpetedNumericProperties = accpetedNumericProperties;
}

auto ChoiceProperty::setValue(const std::variant<std::string, double>& value)
    -> bool {
  // Check if value in lists
  if (std::holds_alternative<std::string>(value)) {
    auto it = m_acceptedStrings.find(std::get<std::string>(value));
    if (it == m_acceptedStrings.end()) {
      return false;
    }
  } else if (std::holds_alternative<double>(value)) {
    auto it = m_accpetedNumericProperties.find(std::get<double>(value));
    if (it == m_accpetedNumericProperties.end()) {
      return false;
    }
  } else {
    return false;
  }
  m_value = value;
  return true;
}

auto ChoiceProperty::getValue() -> std::variant<std::string, double> {
  return m_value;
}
}  // namespace ConfigurationManager