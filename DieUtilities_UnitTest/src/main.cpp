#include <gtest/gtest.h>
#include <DiePlaformMath.h>

using namespace dieEngineSDK;

TEST(Diego1, Trigonometria) {
  DiePlatformMath a;
  ASSERT_TRUE(a.Sin(90.0f) == 0.8939966636f);
  ASSERT_TRUE(a.Cos(45.0f) == 0.5253219888f);
  ASSERT_TRUE(a.Tan(45.0f) == 1.619775191f);
  ASSERT_TRUE(a.Asin(1) == 1.57079633f);
  ASSERT_TRUE(a.Acos(-1) == 3.14159265f);
  ASSERT_TRUE(a.Atan(1) == 0.78539816f);
}


//void main() {
//  
//}