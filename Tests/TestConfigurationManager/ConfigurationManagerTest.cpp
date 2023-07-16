#include "pch.h"  // Include First !!
#include "ConfigurationManager.hpp"
#include "ChoiceProperty.hpp"
#include "Group.hpp"
#include "NumericProperty.hpp"

namespace ConfigurationManager {

// The fixture for ConfigurationManager
class ConfigurationManagerTest : public ::testing::Test {
 public:
  ConfigurationManager m_config = ConfigurationManager();

 protected:
  void SetUp() override {
    // Setup config manager with default constraints
  }
  ~ConfigurationManagerTest() override {}
};

TEST_F(ConfigurationManagerTest, setConfigNumericPropertyPass) { 
    ASSERT_TRUE(m_config.setPropertyValue({"group_1"}, "propety_name_1", (double) 60));
  auto value = m_config.getPropertyValue({"group_1"}, "propety_name_1");
    ASSERT_EQ((double)60, std::any_cast<double>(value));
}

TEST_F(ConfigurationManagerTest, setConfigNumericPropertyFailConstraints) {
    ASSERT_FALSE(
        m_config.setPropertyValue({"group_1"}, "propety_name_1", (double)0));
}

TEST_F(ConfigurationManagerTest, setConfigWrongSubgroupPropertyFail) {
    ASSERT_FALSE(m_config.setPropertyValue({"group_1", "wrongSubgroup"}, "propety_name_1", (double)100));
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

}  // namespace ConfigurationManager