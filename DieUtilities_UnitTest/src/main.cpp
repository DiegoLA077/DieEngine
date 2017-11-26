#include <gtest/gtest.h>
#include <DiePlaformMath.h>
#include <DieMatrix4D.h>
#include <DieVector4D.h>

using namespace dieEngineSDK;
#define  GTEST_OUTPUT 
//TEST(Diego, Constantes) {
TEST(Diego, CreateHardwareBufferVertex) {
  DiePlatformMath Consts;
  ASSERT_TRUE(Consts.PI == 3.141592654f);
  ASSERT_TRUE(Consts.INVPI == 0.3183098862f);
  ASSERT_TRUE(Consts.PI2 == 6.28318530718f);
  ASSERT_TRUE(Consts.EPSILON == 0.0000000000085418781f);
  ASSERT_TRUE(Consts.DELTA == 0.00001f);
  ASSERT_TRUE(Consts.EULER == 2.71828182845904523536f);
  GTEST_OUTPUT "xml:C:\DieEngine";
  system("pause");
}

//TEST(Diego, Trigonometria) {
TEST(Diego, SetHardwareBufferVertex) {
  DiePlatformMath Trig;
  ASSERT_TRUE(Trig.Sin(90.0f) == 0.8939966636f);
  ASSERT_TRUE(Trig.Cos(45.0f) == 0.5253219888f);
  ASSERT_TRUE(Trig.Tan(45.0f) == 1.619775191f);
  ASSERT_TRUE(Trig.Asin(1) == 1.57079633f);
  ASSERT_TRUE(Trig.Acos(-1) == 3.141592654f);
  ASSERT_TRUE(Trig.Atan(1) == 0.78539816f);
}

//TEST(Diego, Operaciones) {
TEST(Diego, CreateHardwareBufferIndex) {
  DiePlatformMath math;
  ASSERT_TRUE(math.Sqrt(9) == 3);
  ASSERT_TRUE(math.InverseSqrt(2) == 0.7071067812f);
  ASSERT_TRUE(math.Exponente(1) == 2.71828182845904523536f);
  ASSERT_TRUE(math.Potencia(2, 3) == 8);

  ASSERT_TRUE(math.Loge(1) == 0.0f);
  ASSERT_TRUE(math.Logx(5, 125) == 3.0f);

  ASSERT_TRUE(math.Truncate(5.1f) == 5);
  ASSERT_TRUE(math.Ceil(7.2) == 8);
  ASSERT_TRUE(math.Floor(3.5) == 3);
  ASSERT_TRUE(math.Round(4.7) == 5);
  system("pause");
}

//TEST(Diego, Matrizes) {
TEST(Diego, SetHardwareBufferIndex) {
  DieMatrix4D Matriz;
  Matriz.m_Elements.m00 = 1; Matriz.m_Elements.m10 = 5; Matriz.m_Elements.m20 = 9;  Matriz.m_Elements.m30 = 0;
  Matriz.m_Elements.m01 = 2; Matriz.m_Elements.m11 = 6; Matriz.m_Elements.m21 = 10; Matriz.m_Elements.m31 = 0;
  Matriz.m_Elements.m02 = 3; Matriz.m_Elements.m12 = 7; Matriz.m_Elements.m22 = 11; Matriz.m_Elements.m32 = 0;
  Matriz.m_Elements.m03 = 4; Matriz.m_Elements.m13 = 8; Matriz.m_Elements.m23 = 12; Matriz.m_Elements.m33 = 0;

  DieMatrix4D Matriz1;
  Matriz1.m_Elements.m00 = 1; Matriz1.m_Elements.m10 = 2;  Matriz1.m_Elements.m20 = 3;  Matriz1.m_Elements.m30 = 4;
  Matriz1.m_Elements.m01 = 5; Matriz1.m_Elements.m11 = 6;  Matriz1.m_Elements.m21 = 7;  Matriz1.m_Elements.m31 = 8;
  Matriz1.m_Elements.m02 = 9; Matriz1.m_Elements.m12 = 10; Matriz1.m_Elements.m22 = 11; Matriz1.m_Elements.m32 = 12;
  Matriz1.m_Elements.m03 = 0; Matriz1.m_Elements.m13 = 0;  Matriz1.m_Elements.m23 = 0;  Matriz1.m_Elements.m33 = 0;
  
  DieMatrix4D Matriz2;
  Matriz2.m_Elements.m00 = 2; Matriz2.m_Elements.m10 = 7;  Matriz2.m_Elements.m20 = 12;  Matriz2.m_Elements.m30 = 4;
  Matriz2.m_Elements.m01 = 7; Matriz2.m_Elements.m11 = 12;  Matriz2.m_Elements.m21 = 17;  Matriz2.m_Elements.m31 = 8;
  Matriz2.m_Elements.m02 = 12; Matriz2.m_Elements.m12 = 17; Matriz2.m_Elements.m22 = 22; Matriz2.m_Elements.m32 = 12;
  Matriz2.m_Elements.m03 = 4; Matriz2.m_Elements.m13 = 8;  Matriz2.m_Elements.m23 = 12;  Matriz2.m_Elements.m33 = 0;

 
  //ASSERT_TRUE(Matriz == Matriz2);
  system("pause");
  system("pause");
}

//TEST(Diego, Vectores) {
TEST(Diego, Vectores) {
  DieVector4D Vector;
  Vector.x = 5;
  Vector.y = 0;
  Vector.z = 0;
  Vector.w = 0;

  DieVector4D Vector1;
  Vector1.x = 1;
  Vector1.y = 0;
  Vector1.z = 0;
  Vector1.w = 0;
  ASSERT_TRUE(Vector1 == Vector.Normalize());

  DieVector4D Vector2;
  float temp;
  Vector2.x = 5;
  Vector2.y = 5;
  Vector2.z = 5;
  Vector2.w = 0;
  temp = Vector2.Dot(Vector2);
  ASSERT_TRUE(temp == 75.0f);

  DieVector4D Vector0;
  Vector0.x = -3;
  Vector0.y = -2;
  Vector0.z = 5;
  Vector0.w = 0;
  DieVector4D Vector01;
  Vector01.x = 10;
  Vector01.y = -6;
  Vector01.z = -1;
  Vector01.w = 0;
  Vector = Vector.Vectorial(Vector0, Vector01);
  DieVector4D Vector03;
  Vector03.x = 32;
  Vector03.y = -47;
  Vector03.z = 38;
  Vector03.w = 0;
  ASSERT_TRUE(Vector == Vector03);
  system("pause");
}

//void main() {
//  
//}
