#include <iostream>
#include <fstream>
#include "ConfigurationManager.hpp"

namespace ConfigurationManager {

auto JsonUtilites::writeJson(
    json data, std::filesystem::path pathToJsonConfig) -> bool {
  // write prettified JSON to another file
  std::ofstream o(pathToJsonConfig);
  o << std::setw(4) << data << std::endl;
  return true;
}

auto JsonUtilites::loadJson(
    std::filesystem::path pathToJsonConfig) -> json {
  // read a JSON file
  std::ifstream f(pathToJsonConfig);
  return json::parse(f);
}

Group ConfigurationManager::DeserializeGroupConstraints(
    const std::string groupName, const json& groupObject) {
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
        std::cout << "subGroup name: " << subGroup.key() << std::endl;
        subgroups.push_back(std::make_shared<Group>(
            DeserializeGroupConstraints(subGroup.key(), subGroup.value())));
      }
  }

  return Group(groupName,std::move(properties),std::move(subgroups));
}

 ConfigurationManager::ConfigurationManager(
    json constraints) {
  if (constraints.empty()) {
    constraints = JsonUtilites::loadJson("constraints.json");
  }

  for (auto& group : constraints.items()) {
    std::cout << "Object name: " << group.key() << std::endl;
    // Deserialize Groups
    m_groups.insert(DeserializeGroupConstraints(group.key(), group.value()));
  }
}
}  // namespace ConfigurationManager