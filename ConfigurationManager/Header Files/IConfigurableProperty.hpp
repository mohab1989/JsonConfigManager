#pragma once
#include<string>
#include<any>

namespace ConfigurationManager {
class IConfigurableProperty {
 protected:
  std::any m_value = NULL;
  std::string m_name = NULL;

 public:
  auto getName() -> std::string { return m_name; };
  virtual auto setValue(const std::any&) -> bool = 0;
  virtual auto getValue() const -> std::any = 0;
};
}  // namespace ConfigurationManager