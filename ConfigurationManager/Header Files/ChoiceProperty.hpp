#pragma once
#ifdef CONFIGURATION_MANAGER_EXPORTS
#define CONFIGURATION_MANAGER __declspec(dllexport)
#else
#define CONFIGURATION_MANAGER __declspec(dllimport)
#endif
#include <set>
#include <string>
#include "IConfigurableProperty.hpp"

namespace ConfigurationManager {
    class ChoiceProperty
        : public IConfigurableProperty {
     private:
      std::set<double> m_accpetedNumericProperties;
      std::set<std::string> m_acceptedStrings;

     public:
      CONFIGURATION_MANAGER ChoiceProperty() = default;
      CONFIGURATION_MANAGER ChoiceProperty(
          const std::string name,
                       const std::set<std::string>& acceptedStrings,
                     const std::set<double>& accpetedNumericProperties);

      CONFIGURATION_MANAGER auto setValue(const std::any& value)
          -> bool override;
      CONFIGURATION_MANAGER auto getValue() const -> std::any override;
    };
}  // namespace ConfigurationManager