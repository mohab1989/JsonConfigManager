#pragma once
#ifdef CONFIGURATION_MANAGER_EXPORTS
#define CONFIGURATION_MANAGER __declspec(dllexport)
#else
#define CONFIGURATION_MANAGER __declspec(dllimport)
#endif

#include <memory>
#include <unordered_set>  // TODO: turn vectors to unordered_set later !!
#include <vector>

#include "IConfigurableProperty.hpp"

namespace ConfigurationManager {

class Group {
 private:
  std::string m_name;
  std::vector<std::unique_ptr<IConfigurableProperty>> m_properties;
  // std::vector<Group> m_subgroups;

 public:
   Group() = default;
  //Group(const Group&) = delete;
  CONFIGURATION_MANAGER Group(
      const std::string& name,
      std::vector<std::unique_ptr<IConfigurableProperty>>&& properties,
      const std::vector<Group>& subgroups = std::vector<Group>())
      : m_name(name),
      m_properties(std::move(properties)){};
  // m_subgroups(subgroups){};

  CONFIGURATION_MANAGER auto getName() -> std::string { return m_name; };

  CONFIGURATION_MANAGER auto getPropertyValue(std::string name) -> std::any;
  // auto getSubgroup(std::string name) -> std::shared_ptr<Group>;
  // auto setProperty(std::string name, std::any value) -> bool;
  // auto appendProperty(IConfigurableProperty property);
  // auto appendSubgroup(Group group) -> bool;
  // auto removeSubgroup(Group group) -> bool;
};
}  // namespace ConfigurationManager