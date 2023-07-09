#include "NumericProperty.hpp"

namespace ConfigurationManager {
    NumericProperty::NumericProperty(const std::string& name, const Minimum& minimum,
        const Maximum& maximum) {
      m_name = name;
      m_minimum = minimum;
      m_maximum = maximum;
    }

    auto NumericProperty::setValue(const std::any& value) -> bool {
      const std::type_info& type = value.type();
      if (type != typeid(double)) {
        return false;
      }
      auto value_double = std::any_cast<double>(value);
      // Check lower limit
      if (value_double < this->m_minimum.value) {
        return false;
      }
      if (m_minimum.minimumExclusive &&
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