#pragma once
#include "DieVector4D.h"

namespace dieEngineSDK {

  class DIE_UTILITIES_EXPORT DieMatrix4D
  {
  public:
    DieMatrix4D();
    ~DieMatrix4D();

    float fMatrix[4][4];
    int filas;
    int columnas;

    union
    {
      DieVector4D m_row[4];
      float fMatrix[4][4];
      float m_Linear[16];

      struct
      {
        float m00, m10, m20, m30,
              m01, m11, m21, m31,
              m02, m12, m22, m32,
              m03, m13, m23, m33;
      }m_Elements;

    };

    DieMatrix4D(float a, float b, float c, float d,
                float e, float f, float g, float h,
                float i, float j, float k, float l,
                float m, float n, float o, float p);
  public:
    void add(const DieMatrix4D& fMa);
    void rest(const DieMatrix4D& fMa);
    DieMatrix4D mult(const DieMatrix4D& fMa); 
    void Transposed();
    bool operator==(DieMatrix4D & MatrizA);
    
    DieMatrix4D(DieVector4D* a, DieVector4D* b, DieVector4D* c, DieVector4D* d);

  };

}

