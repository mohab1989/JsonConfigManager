#include "pch.h"
#include "ChoiceProperty.hpp"
#include "IConfigurableProperty.hpp"

namespace ConfigurationManager {

// The fixture for ChoicePropertyTest
class NumericPropertyTest : public ::testing::Test {
 public:
  ChoiceProperty m_choiceProperty;
  IConfigurableProperty* m_property;
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.
  NumericPropertyTest() {}

  ~NumericPropertyTest() override {
    // You can do clean-up work that doesn't throw exceptions here.
  }
};

TEST_F(NumericPropertyTest, SetValueStringAllowedReturnsTrue) {

}


//int main(int argc, char** argv) {
//  ::testing::InitGoogleTest(&argc, argv);
//  return RUN_ALL_TESTS();
//}

}  // namespace ConfigurationManager