#pragma once
#ifdef CONFIGURATION_MANAGER_EXPORTS
#define CONFIGURATION_MANAGER __declspec(dllexport)
#else
#define CONFIGURATION_MANAGER __declspec(dllimport)
#endif
#include <filesystem>
#include <deque>

#include "nlohmann/json.hpp"
#include "Group.hpp"
#include "NumericProperty.hpp"
#include "ChoiceProperty.hpp"

using json = nlohmann::json;
namespace ConfigurationManager {

class JsonUtilites {
 public:
  static CONFIGURATION_MANAGER auto loadJson(
      std::filesystem::path pathToJsonConfig) -> json;

  static CONFIGURATION_MANAGER bool writeJson(
      json data, std::filesystem::path pathToJsonConfig);
};

class ConfigurationManager {
 private:
  std::vector<Group> m_groups = std::vector<Group>();
  auto deserializeGroupConstraints(const std::string& groupName,
                                   const json& groupObject) -> Group;
  auto serializeConfigurationGroup(const Group& group)
      -> json;
  auto getNestedGroups(std::deque<std::string> nestingGroups) -> Group*;

 public:
  CONFIGURATION_MANAGER ConfigurationManager(json constaints = {});
  CONFIGURATION_MANAGER auto setPropertyValue(
      std::deque<std::string> nestingGroups,
      const std::string& propertyName, const std::any& value) -> bool;
  CONFIGURATION_MANAGER auto getPropertyValue(
      const std::deque<std::string>& nestingGroups, const std::string& propertyName)
      -> std::any;

  CONFIGURATION_MANAGER auto addSubgroup(
      const std::deque<std::string>& nestingGroups, const std::string& groupName,
      std::vector<std::unique_ptr<IConfigurableProperty>>&& properties =
          std::vector<std::unique_ptr<IConfigurableProperty>>(),
      std::vector<std::shared_ptr<Group>>&& subgroups =
          std::vector<std::shared_ptr<Group>>()) -> bool;
  CONFIGURATION_MANAGER auto removeSubgroup(
      const std::deque<std::string>& nestingGroups) -> bool;

  CONFIGURATION_MANAGER auto saveCurrentConfig(std::filesystem::path configPath) -> bool;
};
}  // namespace ConfigurationManager