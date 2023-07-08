#include "NumericProperty.hpp"

namespace ConfigurationManager {
    NumericProperty::NumericProperty(const std::string& name, const Minimum& minimum,
        const Maximum& maximum) {
      //this->m_name = name;
      this->m_minimum = minimum;
      this->m_maximum = maximum;
    }

    auto NumericProperty::setValue(const std::any& value) -> bool {
      auto value_double = std::any_cast<double>(value);
      // Check lower limit
      if (value_double < this->m_minimum.value) {
        return false;
      }
      if (this->m_minimum.minimumExclusive &&
          value_double == this->m_minimum.value) {
          return false;
      }

      // Check upper limit
      if (value_double > this->m_maximum.value) {
        return false;
      }
      if (this->m_maximum.maximumExclusive &&
          value_double == this->m_maximum.value) {
          return false;
      }

      this->m_value = value_double;
      return true;
    }

    auto NumericProperty::getValue() const -> std::any { return this->m_value;}
    }  // namespace ConfigurationManager