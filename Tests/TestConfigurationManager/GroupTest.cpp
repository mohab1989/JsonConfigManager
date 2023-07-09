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
  GroupTest() {
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

}  // namespace ConfigurationManager