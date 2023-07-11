#pragma once
#ifdef CONFIGURATION_MANAGER_EXPORTS
#define CONFIGURATION_MANAGER __declspec(dllexport)
#else
#define CONFIGURATION_MANAGER __declspec(dllimport)
#endif
#include <unordered_set>
#include <filesystem>

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

struct GroupHasher {
  std::size_t operator()(const Group& e) const noexcept {
    return std::hash<std::string>{}(e.getName());
  }
};

class ConfigurationManager {
 private:
  std::unordered_set<Group, GroupHasher, std::equal_to<Group>> m_groups =
      std::unordered_set<Group, GroupHasher, std::equal_to<Group>>();
  Group DeserializeGroupConstraints(const std::string groupName, const json& groupObject);
 public:
  CONFIGURATION_MANAGER ConfigurationManager(json constaints = {});
};
}  // namespace ConfigurationManager