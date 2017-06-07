#include <gtest/gtest.h>
#include <DiePlaformMath.h>
//#include <DieMatrix4D.h>
#include <DieVector4D.h>

using namespace dieEngineSDK;

TEST(Diego, Trigonometria) {
  DiePlatformMath Die;
  ASSERT_TRUE(Die.Sin(90.0f) == 0.8939966636f);
  ASSERT_TRUE(Die.Cos(45.0f) == 0.5253219888f);
  ASSERT_TRUE(Die.Tan(45.0f) == 1.619775191f);
  ASSERT_TRUE(Die.Asin(1) == 1.57079633f);
  ASSERT_TRUE(Die.Acos(-1) == 3.14159265f);
  ASSERT_TRUE(Die.Atan(1) == 0.78539816f);
}

//TEST(Diego, Matrizes) {
//  DieMatrix4D Matriz;
//  Matriz.m_Elements.m00 = 1; Matriz.m_Elements.m10 = 5; Matriz.m_Elements.m20 = 9;  Matriz.m_Elements.m30 = 0;
//  Matriz.m_Elements.m01 = 2; Matriz.m_Elements.m11 = 6; Matriz.m_Elements.m21 = 10; Matriz.m_Elements.m31 = 0;
//  Matriz.m_Elements.m02 = 3; Matriz.m_Elements.m12 = 7; Matriz.m_Elements.m22 = 11; Matriz.m_Elements.m32 = 0;
//  Matriz.m_Elements.m03 = 4; Matriz.m_Elements.m13 = 8; Matriz.m_Elements.m23 = 12; Matriz.m_Elements.m33 = 0;
//
//  DieMatrix4D Matriz1;
//  Matriz1.m_Elements.m00 = 1; Matriz1.m_Elements.m10 = 2;  Matriz1.m_Elements.m20 = 3;  Matriz1.m_Elements.m30 = 4;
//  Matriz1.m_Elements.m01 = 5; Matriz1.m_Elements.m11 = 6;  Matriz1.m_Elements.m21 = 7;  Matriz1.m_Elements.m31 = 8;
//  Matriz1.m_Elements.m02 = 9; Matriz1.m_Elements.m12 = 10; Matriz1.m_Elements.m22 = 11; Matriz1.m_Elements.m32 = 12;
//  Matriz1.m_Elements.m03 = 0; Matriz1.m_Elements.m13 = 0;  Matriz1.m_Elements.m23 = 0;  Matriz1.m_Elements.m33 = 0;
// 
//  ASSERT_TRUE(Matriz1 == Matriz.Transposed());
//}

TEST(Diego, Vectores) {
  DieVector4D Vector;
  DieVector4D vector1;

  ASSERT_TRUE(Vector == vector1.Normalize());
}

//void main() {
//  
//}