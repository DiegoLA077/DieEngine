#pragma once
#include "DieVector4D.h"

namespace dieEngineSDK {

  class DIE_UTILITIES_EXPORT DieMatrix4D
  {
  public:
    DieMatrix4D();
    ~DieMatrix4D();

    float fMatrix[4][4];


    union
    {
      DieVector4D m_row[4];
      float fMatrix[4][4];
      float m_Linear[16];

      struct
      {
        float m00, m01, m02, m03,
          m10, m11, m12, m13,
          m20, m21, m22, m23,
          m30, m31, m32, m33;
      }m_Elements;

    };



    void add(const DieMatrix4D& fMa);
    void rest(const DieMatrix4D& fMa);
    
    void Transposed();

    DieMatrix4D mult(const DieMatrix4D& fMa); 

    DieMatrix4D(float a, float b, float c, float d, 
                float e, float f, float g, float h, 
                float i, float j, float k, float l, 
                float m, float n, float o, float p);

    DieMatrix4D(DieVector4D* a, DieVector4D* b, DieVector4D* c, DieVector4D* d);

  };

}

