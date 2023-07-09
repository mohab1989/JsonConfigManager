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
  std::vector<std::unique_ptr<IConfigurableProperty>> m_properties =
      std::vector<std::unique_ptr<IConfigurableProperty>>();
  std::vector<std::shared_ptr<Group>> m_subgroups =
      std::vector<std::shared_ptr<Group>>();

 public:
  Group() = default;
  CONFIGURATION_MANAGER Group(
      const std::string& name,
      std::vector<std::unique_ptr<IConfigurableProperty>>&& properties,
      std::vector<std::shared_ptr<Group>>&& subgroups = std::vector<std::shared_ptr<Group>>())
      : m_name(name),
      m_properties(std::move(properties)),
      m_subgroups(std::move(subgroups)){};

  CONFIGURATION_MANAGER auto getName() -> std::string { return m_name; };

  CONFIGURATION_MANAGER auto getPropertyValue(std::string name) -> std::any;
  CONFIGURATION_MANAGER auto getSubgroup(std::string name) -> std::shared_ptr<Group>;
  CONFIGURATION_MANAGER auto setPropertyValue(std::string name, std::any value)
      -> bool;
  CONFIGURATION_MANAGER auto appendProperty(
      std::unique_ptr<IConfigurableProperty>&& property)
      -> bool;
  CONFIGURATION_MANAGER auto appendSubgroup(std::unique_ptr<Group>&& group)
      ->bool;
  CONFIGURATION_MANAGER auto removeSubgroup(const std::string& name)->bool;
};
}  // namespace ConfigurationManager