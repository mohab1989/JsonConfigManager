#include "pch.h"
#include "NumericProperty.hpp"
#include "IConfigurableProperty.hpp"

namespace ConfigurationManager {

// The fixture for ChoicePropertyTest
class NumericPropertyTest : public ::testing::Test {
 public:
  NumericProperty m_defaultNumbericProperty;
  IConfigurableProperty* m_property;
  Minimum m_min_m_10{-10, false};
  Minimum m_exclusiveMin_m_10{-10, true};

  Maximum m_max_10{10, false};
  Maximum m_max_exlusiveMin_10{10, true};

 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.
  NumericPropertyTest() {

    std::set<double> acceptedNumbers{0, 1, 2};
    m_defaultNumbericProperty =
        NumericProperty("flush");
    m_property = &m_defaultNumbericProperty;
  }

  ~NumericPropertyTest() override {
  }
};

TEST_F(NumericPropertyTest, SetValueWithinRangeReturnTrue) {
  EXPECT_TRUE(m_property->setValue(std::numeric_limits<double>::min()));
  auto value = std::any_cast<double>(m_property->getValue());
  EXPECT_EQ(std::numeric_limits<double>::min(), value);

  EXPECT_TRUE(m_property->setValue(std::numeric_limits<double>::max()));
  value = std::any_cast<double>(m_property->getValue());
  EXPECT_EQ(std::numeric_limits<double>::max(), value);
}

TEST_F(NumericPropertyTest, SetValueOtsideRangeReturnFalse) {
  NumericProperty numericProperty("number", m_exclusiveMin_m_10, m_max_10);
  m_property = &numericProperty;
  EXPECT_TRUE(m_property->setValue((double) - 9));
  EXPECT_FALSE(m_property->setValue((double) - 10));
  auto value = std::any_cast<double>(m_property->getValue());
  EXPECT_EQ((double)-9, value);

  EXPECT_TRUE(m_property->setValue((double)10));
  EXPECT_FALSE(m_property->setValue((double) 11));
  value = std::any_cast<double>(m_property->getValue());
  EXPECT_EQ((double)10, value);
}

}  // namespace ConfigurationManager