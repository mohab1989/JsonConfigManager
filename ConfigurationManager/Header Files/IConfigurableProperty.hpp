#pragma once
#include<string>
#include<any>

namespace ConfigurationManager {
    class IConfigurableProperty {
     protected:
      std::any m_value = std::any();
      std::string m_name = std::string();

     public:
      virtual auto getName()->std::string { return m_name; };
      virtual auto setValue(const std::any&) -> bool = 0;
      virtual auto getValue() const -> std::any = 0;
    };
}  // namespace ConfigurationManager