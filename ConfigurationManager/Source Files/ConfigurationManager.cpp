#include "ConfigurationManager.hpp"

#include <fstream>
#include <iostream>

namespace ConfigurationManager {

auto JsonUtilites::writeJson(json data, std::filesystem::path pathToJsonConfig)
    -> bool {
  // write prettified JSON to another file
  std::ofstream o(pathToJsonConfig);
  o << std::setw(4) << data << std::endl;
  return true;
}

auto JsonUtilites::loadJson(std::filesystem::path pathToJsonConfig) -> json {
  // read a JSON file
  std::ifstream f(pathToJsonConfig);
  return json::parse(f);
}

auto ConfigurationManager::deserializeGroupConstraints(
    const std::string& groupName, const json& groupObject) -> Group {
  // Iterate over poperties constraints
  auto properties = std::vector<std::unique_ptr<IConfigurableProperty>>();

  // Deserialize numeric properties constraints
  if (groupObject.contains("numeric_properties")) {
    auto numericProperties = groupObject.at("numeric_properties");
    for (auto& numericPropertyJson : numericProperties) {
      properties.emplace_back(std::make_unique<NumericProperty>(
          numericPropertyJson.at("name"),
          Minimum{(double)numericPropertyJson.at("minimum"),
                  numericPropertyJson.at("minimumExlusive")},
          Maximum{(double)numericPropertyJson.at("maximum"),
                  numericPropertyJson.at("maximumExlusive")}));
    }
  }

  // Deserialize choice properties constraints.
  if (groupObject.contains("choice_properties")) {
    auto choiceProperties = groupObject.at("choice_properties");
    for (auto& choicePropertyJson : choiceProperties) {
      properties.emplace_back(std::make_unique<ChoiceProperty>(
          choicePropertyJson.at("name"),
          choicePropertyJson.at("accepted_string_properties"),
          choicePropertyJson.at("accepted_numeric_properties")));
    }
  }

  auto subgroups = std::vector<std::shared_ptr<Group>>();
  // Deserialize subgroups constraints.
  if (groupObject.contains("subgroups")) {
    auto subGroups = groupObject.at("subgroups");
    for (auto& subGroup : subGroups.items()) {
      subgroups.push_back(std::make_shared<Group>(
          deserializeGroupConstraints(subGroup.key(), subGroup.value())));
    }
  }

  return Group(groupName, std::move(properties), std::move(subgroups));
}

auto ConfigurationManager::serializeConfigurationGroup(const Group& group) -> json {
  // Srialize Properties
  auto groupJson = json();
  for (const auto& propertyName : group.getPropertiesNames()) {
    auto value = group.getPropertyValue(propertyName);
    if (value.type() == typeid(double)) {
      groupJson[propertyName] = std::any_cast<double>(value);
    } else if (value.type() == typeid(std::string)) {
      groupJson[propertyName] = std::any_cast<std::string>(value);
    } else {
      groupJson[propertyName] = nullptr;
    }
  }
  // Srialize Subgroups
  for (const auto& subGroupName : group.getSubgroupsNames()) {
    auto subgroup = group.getSubgroup(subGroupName);
    groupJson[subGroupName] =
        serializeConfigurationGroup(*subgroup);
  }

  return groupJson;
}

ConfigurationManager::ConfigurationManager(json constraints) {
  if (constraints.empty()) {
    constraints = JsonUtilites::loadJson("constraints.json");
  }

  for (auto& group : constraints.items()) {
    // Deserialize Groups
    auto existingGroup =
        std::find(m_groups.begin(), m_groups.end(), std::string(group.key()));
    // If Group already exists.
    if (existingGroup != m_groups.end()) {
      // define requirements
      // for the time being assume: ignore.
      continue;
    }
    m_groups.push_back(deserializeGroupConstraints(group.key(), group.value()));
  }
}

auto ConfigurationManager::getNestedGroups(
    std::deque<std::string> nestingGroups) -> Group* {
  if (nestingGroups.empty()) {
    return nullptr;
  }
  auto rootGroupIter =
      std::find(m_groups.begin(), m_groups.end(), nestingGroups.front());
  if (rootGroupIter == m_groups.end()) {
    return nullptr;
  }
  Group* currentGroup(&(*rootGroupIter));
  nestingGroups.pop_front();

  // access subgroups
  for (const auto& groupName : nestingGroups) {
    auto subGroup = currentGroup->getSubgroup(groupName);
    if (subGroup == nullptr) {
      return nullptr;
    }
    currentGroup = subGroup.get();
  }
  return currentGroup;
}

auto ConfigurationManager::setPropertyValue(
    std::deque<std::string> nestingGroups, const std::string& propertyName,
    const std::any& value) -> bool {
  auto group = getNestedGroups(nestingGroups);
  if (group == nullptr) {
    return false;
  }
  return group->setPropertyValue(propertyName, value);
}

auto ConfigurationManager::getPropertyValue(
    const std::deque<std::string>& nestingGroups,
    const std::string& propertyName) -> std::any {
  auto group = getNestedGroups(nestingGroups);
  if (group == nullptr) {
    return std::any();
  }
  return group->getPropertyValue(propertyName);
}

auto ConfigurationManager::addSubgroup(
    const std::deque<std::string>& nestingGroups, const std::string& groupName,
    std::vector<std::unique_ptr<IConfigurableProperty>>&& properties,
    std::vector<std::shared_ptr<Group>>&& subgroups) -> bool {
  // root group
  if (nestingGroups.size() == 1) {
    auto existingGroup = std::find_if(
        m_groups.begin(), m_groups.end(),
        [groupName](const Group& g) { return g.getName() == groupName; });
    // If Group already exists.
    if (existingGroup != m_groups.end()) {
      return false;
    }
    m_groups.emplace_back(groupName, std::move(properties),
                          std::move(subgroups));
    return true;
  }

  auto parentGroup = getNestedGroups(nestingGroups);
  if (parentGroup == nullptr) {
    return false;
  }
  return parentGroup->appendSubgroup(std::make_unique<Group>(
      groupName, std::move(properties), std::move(subgroups)));
}

auto ConfigurationManager::removeSubgroup(
    const std::deque<std::string>& nestingGroups) -> bool {
  // root group
  if (nestingGroups.size() == 1) {
    auto rootGroup = nestingGroups.front();
    auto it = std::remove_if(
        m_groups.begin(), m_groups.end(),
        [rootGroup](const Group& g) { return g.getName() == rootGroup; });
    if (it == m_groups.end()) {
      return false;
    }
    return true;
  }

  auto groupTobeRemoved = nestingGroups.back();
  auto nestingSubGroups = nestingGroups;
  nestingSubGroups.pop_back();

  Group* group = getNestedGroups(nestingSubGroups);
  if (group == nullptr) {
    return false;
  }
  return group->removeSubgroup(groupTobeRemoved);
}

auto ConfigurationManager::saveCurrentConfig(std::filesystem::path configPath)
    -> bool {
  configPath = std::filesystem::absolute(configPath);
  auto parentDirectortyPath = configPath.parent_path();
  if (!std::filesystem::exists(parentDirectortyPath)) {
    try {
      std::filesystem::create_directories(parentDirectortyPath);
      std::cout << "Directory path created successfully!" << std::endl;
    } catch (const std::exception& e) {
      std::cout << "Error creating directory path: " << e.what() << std::endl;
      return false;
    }
  }

  auto jsonConfig = json();
  for (const auto& group : m_groups) {
    jsonConfig[group.getName()] =
        serializeConfigurationGroup(group);
  }
  JsonUtilites::writeJson(jsonConfig, configPath);
}
}  // namespace ConfigurationManager