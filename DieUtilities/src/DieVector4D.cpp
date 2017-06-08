#include "DieVector4D.h"

namespace dieEngineSDK
{
  DieVector4D::~DieVector4D()
  {
  }
  DieVector4D::DieVector4D(float x, float y, float z, float w)
  {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
  }

  bool DieVector4D::operator==(DieVector4D &vectorA)
  {
    return (x == vectorA.x && y == vectorA.y && z == vectorA.z && w == vectorA.w);
  }

  bool DieVector4D::operator==(float escalar)
  {
    return (x == escalar && y == escalar && z == escalar && w == escalar);
  }

  bool DieVector4D::operator!=(DieVector4D &vectorA)
  {
    return !(*this == vectorA);
  }

  DieVector4D& DieVector4D::operator+=(DieVector4D &vectorA)
  {
    x += vectorA.x;
    y += vectorA.y;
    z += vectorA.z;
    w += vectorA.w;
    return *this;
  }
  DieVector4D& DieVector4D::operator-=(DieVector4D &vectorA)
  {
    x -= vectorA.x;
    y -= vectorA.y;
    z -= vectorA.z;
    w -= vectorA.w;
    return *this;
  }
  DieVector4D& DieVector4D::operator*=(DieVector4D &vectorA)
  {
    x *= vectorA.x;
    y *= vectorA.y;
    z *= vectorA.z;
    w *= vectorA.w;
    return *this;
  }
  DieVector4D& DieVector4D::operator/=(DieVector4D &vectorA)
  {
    x /= vectorA.x;
    y /= vectorA.y;
    z /= vectorA.z;
    w /= vectorA.w;
    return *this;
  }
  DieVector4D& DieVector4D::operator*=(float escalar)
  {
    x *= escalar;
    y *= escalar;
    z *= escalar;
    w *= escalar;
    return *this;
  }

  DieVector4D DieVector4D::operator*(const DieVector4D &vectorA)
  {
    return DieVector4D(vectorA.x*x, vectorA.y*y, vectorA.z*z, vectorA.w*w);
  }

  DieVector4D DieVector4D::operator+(const float f)
  {
    DieVector4D Resp;
    Resp.x = x + f;
    Resp.y = y + f;
    Resp.z = z + f;
    Resp.w = w + f;
    return Resp;
  }
  DieVector4D DieVector4D::operator+(const DieVector4D &vectorA)
  {
    DieVector4D Resp;
    Resp.x = x + vectorA.x;
    Resp.y = y + vectorA.y;
    Resp.z = z + vectorA.z;
    Resp.w = w + vectorA.w;
    return Resp;
  }
  DieVector4D DieVector4D::operator-(const DieVector4D &vectorA)
  {
    DieVector4D Resp;
    Resp.x = x - vectorA.x;
    Resp.y = y - vectorA.y;
    Resp.x = x - vectorA.z;
    Resp.y = y - vectorA.w;
    return Resp;
  }
  DieVector4D DieVector4D::operator/(const DieVector4D &vectorA)
  {
    return DieVector4D(vectorA.x / x, vectorA.y / y, vectorA.z / z, vectorA.w / w);
  }
  DieVector4D DieVector4D::operator/(float escalar)
  {
    return DieVector4D(x / escalar, y / escalar, z / escalar, w / escalar);
  }
  DieVector4D DieVector4D::operator*(float escalar)
  {
    return DieVector4D(x*escalar, y*escalar, z*escalar, w*escalar);
  }

  DieVector4D DieVector4D::DistanceVector(DieVector4D & Vector4d)
  {
    DieVector4D NewVector;
    NewVector.x = Vector4d.x - x;
    NewVector.y = Vector4d.y - y;
    NewVector.x = Vector4d.z - z;
    NewVector.y = Vector4d.w - w;
    return NewVector;
  }

  DieVector4D DieVector4D::Truncate(float MagFuerza)
  {
    DieVector4D New;
    New = Normalize() * MagFuerza;
    return New;
  }

  float DieVector4D::Dot(DieVector4D &vectorA)
  {
    return x*vectorA.x + y*vectorA.y + z*vectorA.z + w*vectorA.w;
  }
  DieVector4D DieVector4D::Cruz(DieVector4D &vectorA, DieVector4D &vectorB)
  {
    DieVector4D NewVector;
    NewVector.x = vectorA.y*vectorB.z - vectorA.z*vectorB.y;
    NewVector.y = vectorA.x*vectorB.z - vectorA.z*vectorB.x;
    NewVector.z = vectorA.x*vectorB.y - vectorA.y*vectorB.x;
    NewVector.w = 0;
    return NewVector;
  }
  float DieVector4D::Mag()
  {
    return sqrt(Dot(*this));
  }
  DieVector4D DieVector4D::Normalize()
  {
    DieVector4D New;
    New = *this / Mag();
    return New;
  }

  void DieVector4D::Clear()
  {
    x = 0;
    y = 0;
    z = 0;
    w = 0;
  }

}