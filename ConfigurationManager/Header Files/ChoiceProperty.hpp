#pragma once
#include <set>
#include <string>
#include <variant>
#include "IConfigurableProperty.hpp"

namespace ConfigurationManager {
class ChoiceProperty
    : public IConfigurableProperty<std::variant<std::string, double>> {
 private:
  std::set<double> m_accpetedNumericProperties;
  std::set<std::string> m_acceptedStrings;

 public:
  __declspec(dllexport) ChoiceProperty(const std::string name,
                     std::set<std::string>& acceptedStrings,
                 const std::set<double>& accpetedNumericProperties);

  auto setValue(const std::variant<std::string, double>& value)
      -> bool override;
  virtual auto getValue() -> std::variant<std::string, double> override;
};
}  // namespace ConfigurationManager