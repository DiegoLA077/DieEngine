#pragma once
#include "DiePlaformMath.h"
#include "DiePrerequisites.h"
namespace dieEngineSDK {

  class DIE_UTILITIES_EXPORT DieVector4D
  {
  public:
    DieVector4D() {};
    ~DieVector4D();
  public:
    float x, y, z, w;

    DieVector4D(float x, float y, float z, float w);
    DieVector4D& operator-=(DieVector4D &vectorA);
    DieVector4D& operator+=(DieVector4D &vectorA);
    DieVector4D& operator*=(DieVector4D &vectorA);
    DieVector4D& operator/=(DieVector4D &vectorA);
    DieVector4D& operator*=(float escalar);

    DieVector4D operator*(const DieVector4D &vectorA);
    DieVector4D operator+(const DieVector4D &vectorA);
    DieVector4D operator+(const float f);
    DieVector4D operator-(const DieVector4D &vectorA);
    DieVector4D operator/(const DieVector4D &vectorA);
    DieVector4D operator/(float escalar);
    DieVector4D operator*(float escalar);

    DieVector4D DistanceVector(DieVector4D & Vector2d);
    DieVector4D Truncate(float MagFuerza);
    float Dot(DieVector4D &vectorA);
    float Mag();
    DieVector4D Normalize();

    bool operator==(DieVector4D & vectorA);
    bool operator!=(DieVector4D & vectorA);

    void Clear(void);
  };
}
