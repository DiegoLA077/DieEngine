#include "DiePlaformMath.h"

float dieEngineSDK::DiePlatformMath::Sqrt(float Value) {
  return sqrtf(Value);
}

float dieEngineSDK::DiePlatformMath::InverseSqrt(float Value)
{
  return(1.0f / sqrtf(Value));
}

float dieEngineSDK::DiePlatformMath::Exponente(float Value) {
  return expf(Value);
}

float dieEngineSDK::DiePlatformMath::Potencia(float A, float B) {
  return powf(A, B);
}

float dieEngineSDK::DiePlatformMath::Loge(float Value) {
  return logf(Value);
}

float dieEngineSDK::DiePlatformMath::Logx(float Base, float Value) {
  return Loge(Value) / Loge(Base);
}

float dieEngineSDK::DiePlatformMath::Sin(float Value) {
  return sinf(Value);
}

float dieEngineSDK::DiePlatformMath::Cos(float Value) {
  return cosf(Value);
}

float dieEngineSDK::DiePlatformMath::Tan(float Value) {
  return tanf(Value);
}

float dieEngineSDK::DiePlatformMath::Asin(float Value) {
  return asinf((Value < -1.f) ? -1.f : ((Value < 1.f) ? Value : 1.f));
}

float dieEngineSDK::DiePlatformMath::Acos(float Value) {
  return acosf((Value < -1.f) ? -1.f : ((Value < 1.f) ? Value : 1.f));
}

float dieEngineSDK::DiePlatformMath::Atan(float Value) {
  return atanf(Value);
}

float dieEngineSDK::DiePlatformMath::Plane(float z, float x) {
  return 0.2 * cos(4 * z) * sin(4 * x);
}

int dieEngineSDK::DiePlatformMath::Truncate(float Value) {
  return (int)Value;
}



int dieEngineSDK::DiePlatformMath::Round(float Value) {
  return Floor(Value + 0.5f);
}

int dieEngineSDK::DiePlatformMath::Ceil(float Value) {
  return Truncate(ceilf(Value));
}

int dieEngineSDK::DiePlatformMath::Floor(float Value) {
  return Truncate(floorf(Value));
}

//DieVector4D dieEngineSDK::DiePlatformMath::Sphere(float u, float v, void*)
//{
//  return DieVector4D(cos(PI2*u)*sin(PI*v), cos(PI*v), sin(PI2*u)*sin(PI*v), 1);
//}