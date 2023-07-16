#include "pch.h"  // Include First !!
#include "ChoiceProperty.hpp"
#include "ConfigurationManager.hpp"
#include "Group.hpp"
#include "NumericProperty.hpp"

namespace ConfigurationManager {

// The fixture for ConfigurationManager
class ConfigurationManagerTest : public ::testing::Test {
 public:
  // Setup config manager with default constraints
  ConfigurationManager m_config = ConfigurationManager();
  std::vector<std::unique_ptr<IConfigurableProperty>> m_properties =
      std::vector<std::unique_ptr<IConfigurableProperty>>();

 protected:
  void SetUp() override {
    // prepare numeric property
    auto numbericProperty = std::make_unique<NumericProperty>("flush");
    numbericProperty->setValue((double)10);

    // prpare choice property
    std::set<std::string> acceptedStrings{"trace", "error", "warning"};
    std::set<double> acceptedNumbers{0, 1, 2};
    auto choiceProperty = std::make_unique<ChoiceProperty>(
        "level", acceptedStrings, acceptedNumbers);
    choiceProperty->setValue(std::string("warning"));

    // prepare list of properties
    m_properties.push_back(std::move(numbericProperty));
    m_properties.push_back(std::move(choiceProperty));
  }
  ~ConfigurationManagerTest() override {}
};

TEST_F(ConfigurationManagerTest, setConfigNumericPropertyPass) {
  ASSERT_TRUE(
      m_config.setPropertyValue({"group_1"}, "propety_name_1", (double)60));
  auto value = m_config.getPropertyValue({"group_1"}, "propety_name_1");
  ASSERT_EQ((double)60, std::any_cast<double>(value));
}

TEST_F(ConfigurationManagerTest, setConfigNumericPropertyFailConstraints) {
  ASSERT_FALSE(
      m_config.setPropertyValue({"group_1"}, "propety_name_1", (double)0));
}

TEST_F(ConfigurationManagerTest, setConfigWrongSubgroupPropertyFail) {
  ASSERT_FALSE(m_config.setPropertyValue({"group_1", "wrongSubgroup"},
                                         "propety_name_1", (double)100));
}

TEST_F(ConfigurationManagerTest, setConfigSubgroupChoicePropertyPass) {
  ASSERT_TRUE(m_config.setPropertyValue({"group_1", "subgroup_1"},
                                        "propety_name_1", (double)100));
  auto value =
      m_config.getPropertyValue({"group_1", "subgroup_1"}, "propety_name_1");
  ASSERT_EQ((double)100, std::any_cast<double>(value));

  ASSERT_TRUE(m_config.setPropertyValue({"group_1", "subgroup_1"},
                                        "propety_name_1", std::string("C2")));
  value =
      m_config.getPropertyValue({"group_1", "subgroup_1"}, "propety_name_1");
  ASSERT_EQ(std::string("C2"), std::any_cast<std::string>(value));
}

TEST_F(ConfigurationManagerTest, setConfigSubgroupChoicePropertyFail) {
  ASSERT_TRUE(m_config.setPropertyValue({"group_1", "subgroup_1"},
                                        "propety_name_1", (double)100));

  ASSERT_FALSE(m_config.setPropertyValue({"group_1", "subgroup_1"},
                                         "propety_name_1", std::string("C6")));
  auto value =
      m_config.getPropertyValue({"group_1", "subgroup_1"}, "propety_name_1");
  ASSERT_EQ((double)100, std::any_cast<double>(value));
}

TEST_F(ConfigurationManagerTest, addAndRemoveSubgroupPass) {
  ASSERT_TRUE(m_config.addSubgroup({"group_1", "subgroup_1"}, "subgroup_1",
                                   std::move(m_properties)));

  auto value = m_config.getPropertyValue(
      {"group_1", "subgroup_1", "subgroup_1"}, "flush");
  ASSERT_EQ((double)10, std::any_cast<double>(value));

  value = m_config.getPropertyValue({"group_1", "subgroup_1", "subgroup_1"},
                                    "level");
  ASSERT_EQ(std::string("warning"), std::any_cast<std::string>(value));

  // Remove Subgroup
  ASSERT_TRUE(m_config.removeSubgroup({"group_1", "subgroup_1", "subgroup_1"}));
  value = m_config.getPropertyValue({"group_1", "subgroup_1", "subgroup_1"},
                                    "flush");
  ASSERT_FALSE(value.has_value());
}

}  // namespace ConfigurationManager