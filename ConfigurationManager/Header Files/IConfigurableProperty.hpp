#pragma once
#include<string>

namespace ConfigurationManager {
template <typename T>
class IConfigurableProperty {
 public:
  T m_value = NULL;
  std::string m_name=NULL;

  auto getName() -> std::string { return m_name; };
  virtual auto setValue(const T&) -> bool = 0;
  virtual auto getValue() -> T = 0;
};
}  // namespace ConfigurationManager