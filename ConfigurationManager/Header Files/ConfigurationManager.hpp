#pragma once
#include <filesystem>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
namespace ConfigurationManager {

class IHpmConfigEditor {
 public:
  __declspec(dllexport)
  virtual json loadJson(std::filesystem::path pathToJsonConfig) = 0;
};

class JsonManager : public IHpmConfigEditor
{
 public:
  __declspec(dllexport) auto loadJson(std::filesystem::path pathToJsonConfig)
      -> json override;

  static __declspec(dllexport) bool writeJson(
      json data, std::filesystem::path pathToJsonConfig);
};

//=======================================================

class IHpmConfigReader
{
 public:
  __declspec(dllexport) virtual json
      getConfig(std::filesystem::path pathToJsonConfig) = 0;
};


class ConfigReader : public IHpmConfigReader
{
 public:
  auto getConfig(std::filesystem::path pathToJsonConfig) -> json override;
};

}  // namespace MathFuncs