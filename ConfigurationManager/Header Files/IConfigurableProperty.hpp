#pragma once
#include<string>
#include<any>

namespace ConfigurationManager {
    class IConfigurableProperty {
     protected:
      std::any m_value = std::any();
      std::string m_name = std::string();

     public:
      bool operator==(const IConfigurableProperty& rhs) const {
        return m_name == rhs.m_name;
      }
      bool operator==(const std::string& rhsName) const {
        return m_name == rhsName;
      }
      virtual auto getName()->std::string { return m_name; };
      virtual auto setValue(const std::any&) -> bool = 0;
      virtual auto getValue() const -> std::any = 0;
    };
}  // namespace ConfigurationManager