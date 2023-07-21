// HpmConfigurationManager.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ConfigurationManager.hpp"

int main()
{
  std::filesystem::path currentPath = std::filesystem::current_path();
  std::cout << "Current Directory: " << currentPath << std::endl;
  auto configManager = ConfigurationManager::ConfigurationManager::ConfigurationManager();

}

