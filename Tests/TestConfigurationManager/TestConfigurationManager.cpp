#include <fstream>
#include "pch.h"
#include "ConfigurationManager.hpp"
#include "ChoiceProperty.hpp"
#include "IConfigurableProperty.hpp"

namespace ConfigurationManager {

// The fixture for ChoicePropertyTest
class ChoicePropertyTest : public ::testing::Test {
 public:
  ChoiceProperty m_choiceProperty;
  IConfigurableProperty* m_property;
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.
  ChoicePropertyTest() {
    // You can do set-up work for each test here.
    std::set<std::string> acceptedStrings{"trace", "error", "warning"};
    std::set<double> acceptedNumbers{0, 1, 2};
    m_choiceProperty =
        ChoiceProperty("logging", acceptedStrings, acceptedNumbers);
    m_property = &m_choiceProperty;
  }

  ~ChoicePropertyTest() override {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
    // Code here will be called immediately after the constructor (right
    // before each test).
  }

  void TearDown() override {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }
};

TEST_F(ChoicePropertyTest, SetValueStringAllowedReturnsTrue) {
  EXPECT_EQ("logging", m_property->getName());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

}  // namespace ConfigurationManager