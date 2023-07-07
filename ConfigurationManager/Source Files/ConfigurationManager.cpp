#include <iostream>
#include <fstream>
#include "ConfigurationManager.hpp"

auto ConfigurationManager::JsonManager::writeJson(
    json data, std::filesystem::path pathToJsonConfig)
    -> bool {
  // write prettified JSON to another file
  std::ofstream o(pathToJsonConfig);
  o << std::setw(4) << data << std::endl;
  return true;
}

auto ConfigurationManager::JsonManager::loadJson(
    std::filesystem::path pathToJsonConfig) -> json {
    // read a JSON file
    std::ifstream f(pathToJsonConfig);
    return json::parse(f);
}


auto ConfigurationManager::ConfigReader::getConfig(
    std::filesystem::path pathToJsonConfig)
    -> json {
    return true;

}