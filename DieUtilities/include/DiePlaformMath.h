#pragma once
#include "DiePrerequisites.h"
#include <math.h>
#include "DieVector4D.h"

namespace dieEngineSDK {

  class DIE_UTILITIES_EXPORT DiePlatformMath
  {
  public:
    float PI = atanf(1) * 4;
    float PI2 = PI*2.0f;
    float INVPI = 1 / PI;
    float EPSILON = 0.0000000000085418781f;
    float DELTA = 0.00001f;
    float EULER = 2.71828182845904523536f;
  public:
    float Sqrt(float Value);
    float InverseSqrt(float Value);
    float Exponente(float Value);
    float Potencia(float A, float B);
   
  public:
    float Loge(float Value);
    float Logx(float Base, float Value);
  public:
    float Sin(float Value);
    float Cos(float Value);
    float Tan(float Value);
    float Asin(float Value);
    float Acos(float Value);
    float Atan(float Value);

    int Truncate(float Value);
    int Ceil(float Value);
    int Floor(float Value);
    int Round(float Value);

    float Plane(float z, float x);
    //DieVector4D Sphere(float u, float v, void*);
  };
}