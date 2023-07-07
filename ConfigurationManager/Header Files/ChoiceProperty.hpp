#pragma once
#ifdef CHOICE_PROPERTY_EXPORTS
#define CHOICE_PROPERTY __declspec(dllexport)
#else
#define CHOICE_PROPERTY __declspec(dllimport)
#endif
#include <set>
#include <string>
#include <variant>
#include "IConfigurableProperty.hpp"

namespace ConfigurationManager {
class ChoiceProperty
    : public IConfigurableProperty {
 private:
  std::set<double> m_accpetedNumericProperties;
  std::set<std::string> m_acceptedStrings;

 public:
  CHOICE_PROPERTY ChoiceProperty() = default;
  CHOICE_PROPERTY ChoiceProperty(
      const std::string name,
                     std::set<std::string>& acceptedStrings,
                 const std::set<double>& accpetedNumericProperties);

  CHOICE_PROPERTY auto setValue(const std::any& value)
      -> bool override;
  CHOICE_PROPERTY virtual auto getValue() const -> std::any override;
};
}  // namespace ConfigurationManager