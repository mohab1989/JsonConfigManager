#include "pch.h" // Include First !!
#include "NumericProperty.hpp"
#include "ChoiceProperty.hpp"
#include "Group.hpp"

namespace ConfigurationManager {

// The fixture for GroupTest
class GroupTest : public ::testing::Test {
 public:
  std::vector<std::unique_ptr<IConfigurableProperty>> m_properties =
      std::vector<std::unique_ptr<IConfigurableProperty>>();
  Group m_group;

 protected:

void SetUp() override {
    // prepare numeric property
    auto numbericProperty =
        std::make_unique<NumericProperty>("flush");
    numbericProperty->setValue((double)10);

    // prpare choice property
    std::set<std::string> acceptedStrings{"trace", "error", "warning"};
    std::set<double> acceptedNumbers{0, 1, 2};
    auto choiceProperty =
        std::make_unique <ChoiceProperty>("level", acceptedStrings, acceptedNumbers);
    choiceProperty->setValue(std::string("warning"));

    // prepare list of properties
    m_properties.push_back(std::move(numbericProperty));
    m_properties.push_back(std::move(choiceProperty));
    m_group = Group("logging", std::move(m_properties));
  }
  ~GroupTest() override {}
};

TEST_F(GroupTest, getPropertyValue) {
   auto numericProperty = m_group.getPropertyValue("flush");
   EXPECT_EQ((double)10, std::any_cast<double>(numericProperty));
   auto choiceProperty = m_group.getPropertyValue("level");
   EXPECT_EQ(std::string("warning"),
             std::any_cast<std::string>(choiceProperty));
}

TEST_F(GroupTest, setPropertyValue) {
   EXPECT_TRUE(m_group.setPropertyValue("flush",(double)100));
   auto numericProperty = m_group.getPropertyValue("flush");
   EXPECT_EQ((double)100, std::any_cast<double>(numericProperty));

   EXPECT_TRUE(m_group.setPropertyValue("level", (double)2));
   auto choiceProperty = m_group.getPropertyValue("level");
   EXPECT_EQ((double)2, std::any_cast<double>(choiceProperty));
}

TEST_F(GroupTest, appendProperty) {
   EXPECT_TRUE(m_group.appendProperty(std::make_unique<NumericProperty>("appnededProperty")));
   EXPECT_TRUE(m_group.setPropertyValue("appnededProperty", (double)20));
   auto numericProperty = m_group.getPropertyValue("appnededProperty");
   EXPECT_EQ((double)20, std::any_cast<double>(numericProperty));
   EXPECT_FALSE(m_group.appendProperty(std::make_unique<NumericProperty>("appnededProperty")));
   numericProperty = m_group.getPropertyValue("appnededProperty");
   EXPECT_EQ((double)20, std::any_cast<double>(numericProperty));
}

TEST_F(GroupTest, appendSubGroup) {
   auto subPropetiers = std::vector<std::unique_ptr<IConfigurableProperty>>();
   subPropetiers.push_back(
       std::make_unique<NumericProperty>("newNumericValue"));
   EXPECT_TRUE(m_group.appendSubgroup(std::make_unique<Group>("appnededGroup1",std::move(subPropetiers))));
   //access subgroup
   auto addedGroup = m_group.getSubgroup("appnededGroup1");
   EXPECT_TRUE(addedGroup->setPropertyValue("newNumericValue", (double)20));
   auto numericProperty = addedGroup->getPropertyValue("newNumericValue");
   EXPECT_EQ((double)20, std::any_cast<double>(numericProperty));
   EXPECT_FALSE(m_group.appendSubgroup(std::make_unique<Group>(
       "appnededGroup1",
       std::move(std::vector<std::unique_ptr<IConfigurableProperty>>()))));
   // Previous step didnt succeed, get old value of flush;
   numericProperty = addedGroup->getPropertyValue("newNumericValue");
   EXPECT_EQ((double)20, std::any_cast<double>(numericProperty));
}

TEST_F(GroupTest, removeSubGroup) {
   EXPECT_TRUE(m_group.appendSubgroup(
       std::make_unique<Group>("appnededGroup2", std::move(m_properties))));
   EXPECT_TRUE(m_group.removeSubgroup("appnededGroup2"));
   // nothing to delete
   EXPECT_FALSE(m_group.removeSubgroup("appnededGroup2"));
}

}  // namespace ConfigurationManager