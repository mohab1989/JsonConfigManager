#include "pch.h" // Include First !!
#include "NumericProperty.hpp"
#include "ChoiceProperty.hpp"
#include "Group.hpp"

namespace ConfigurationManager {

// The fixture for GroupTest
class GroupTest : public ::testing::Test {
 public:
  NumericProperty m_numbericProperty;
  ChoiceProperty m_choiceProperty;
  std::vector<IConfigurableProperty*> m_properties =
      std::vector<IConfigurableProperty*>();
  Group m_group;

 protected:
  GroupTest() {
    m_numbericProperty = NumericProperty("flush");
    m_numbericProperty.setValue((double)10);
    std::set<std::string> acceptedStrings{"trace", "error", "warning"};
    std::set<double> acceptedNumbers{0, 1, 2};
    m_choiceProperty =
        ChoiceProperty("level", acceptedStrings, acceptedNumbers);
    m_choiceProperty.setValue(std::string("warning"));
    m_properties.push_back(&m_numbericProperty);
    m_properties.push_back(&m_choiceProperty);
    m_group = Group("logging", m_properties);
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