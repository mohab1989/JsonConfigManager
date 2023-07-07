#include "NumericProperty.hpp"

namespace ConfigurationManager {
    NumericProperty::NumericProperty(const std::string& name, const Minimum& minimum,
        const Maximum& maximum) {
      this->m_name = name;
      this->m_minimum = minimum;
      this->m_maximum = maximum;
    }

    auto NumericProperty::setValue(const double& value) -> bool {

      // Check lower limit
      if (value < this->m_minimum.value) {
        return false;
      }
      if (this->m_minimum.minimumExclusive && value == this->m_minimum.value) {
          return false;
      }

      // Check upper limit
      if (value > this->m_maximum.value) {
        return false;
      }
      if (this->m_maximum.maximumExclusive && value == this->m_maximum.value) {
          return false;
      }

      this->m_value = value;
      return true;
    }

    auto NumericProperty::getValue() -> double { return this->m_value;}
    }  // namespace ConfigurationManager