#include "pch.h"
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
};

TEST_F(ChoicePropertyTest, GetNameReturnsNameOfProperty) {
  EXPECT_EQ("logging", m_property->getName());
}

TEST_F(ChoicePropertyTest, SetValueStringAllowedReturnsTrue) {
  EXPECT_TRUE(m_property->setValue(std::string("error")));
}

TEST_F(ChoicePropertyTest, SetValueStringNotAllowedReturnsFalse) {
  EXPECT_FALSE(m_property->setValue(std::string("never")));
}
TEST_F(ChoicePropertyTest, SetValueDoubleAllowedReturnsTrue) {
  EXPECT_TRUE(m_property->setValue((double) 1));
}
TEST_F(ChoicePropertyTest, SetValueDoubleNotAllowedReturnsFalse) {
  EXPECT_FALSE(m_property->setValue((double) 100));
}

 // Get Value
TEST_F(ChoicePropertyTest, GetValueReturnsNoValue) {
  EXPECT_FALSE(m_property->setValue(std::string("never")));
  EXPECT_FALSE(m_property->getValue().has_value());
}

TEST_F(ChoicePropertyTest, GetValueReturnsString) {
  EXPECT_TRUE(m_property->setValue(std::string("trace")));
  auto value = m_property->getValue();
  EXPECT_TRUE(value.has_value());
  if (value.type() == typeid(std::string)) {
    EXPECT_EQ(std::string("trace"), std::any_cast<std::string>(value));
  } else {
    FAIL();
  }
  }

TEST_F(ChoicePropertyTest, GetValueReturnsDouble) {
  EXPECT_TRUE(m_property->setValue((double)1));
  auto value = m_property->getValue();
  EXPECT_TRUE(value.has_value());
  if (value.type() == typeid(double)) {
    EXPECT_EQ(1, std::any_cast<double>(value));
  } else {
    FAIL();
  }
  }

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

}  // namespace ConfigurationManager