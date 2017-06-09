#include "DieMatrix4D.h"


namespace dieEngineSDK {

  DieMatrix4D::DieMatrix4D()
  {
  }


  DieMatrix4D::DieMatrix4D(float a, float b, float c, float d,
    float e, float f, float g, float h,
    float i, float j, float k, float l,
    float m, float n, float o, float p)
  {
    fMatrix[0][0] = a;
    fMatrix[0][1] = b;
    fMatrix[0][2] = c;
    fMatrix[0][3] = d;

    fMatrix[1][0] = e;
    fMatrix[1][1] = f;
    fMatrix[1][2] = g;
    fMatrix[1][3] = h;

    fMatrix[2][0] = i;
    fMatrix[2][1] = j;
    fMatrix[2][2] = k;
    fMatrix[2][3] = l;

    fMatrix[3][0] = m;
    fMatrix[3][1] = n;
    fMatrix[3][2] = o;
    fMatrix[3][3] = p;
  }

  DieMatrix4D::DieMatrix4D(DieVector4D* a, DieVector4D* b,
    DieVector4D* c, DieVector4D* d)
  {
    fMatrix[0][0] = a->x;
    fMatrix[0][1] = a->y;
    fMatrix[0][2] = a->z;
    fMatrix[0][3] = a->w;

    fMatrix[1][0] = b->x;
    fMatrix[1][1] = b->y;
    fMatrix[1][2] = b->z;
    fMatrix[1][3] = b->w;

    fMatrix[2][0] = c->x;
    fMatrix[2][1] = c->y;
    fMatrix[2][2] = c->z;
    fMatrix[2][3] = c->w;

    fMatrix[3][0] = d->x;
    fMatrix[3][1] = d->y;
    fMatrix[3][2] = d->z;
    fMatrix[3][3] = d->w;
  }


  DieMatrix4D::~DieMatrix4D()
  {
  }


  void  DieMatrix4D::add(const DieMatrix4D& fMa)
  {
    for (int i = 0; i < 4; i++)
    {

      for (int j = 0; i < 4; i++)
      {
        fMatrix[i][j] = fMatrix[i][j] + fMa.fMatrix[i][j];
      }

    }

  }
  void DieMatrix4D::rest(const DieMatrix4D& fMa)
  {


    for (int i = 0; i < 4; i++)
    {

      for (int j = 0; i < 4; i++)
      {
        fMatrix[i][j] = fMatrix[i][j] - fMa.fMatrix[i][j];
      }

    }


  }
  DieMatrix4D DieMatrix4D::mult(const DieMatrix4D& fMa)
  {

    DieMatrix4D Result;

    Result.fMatrix[0][0] = (fMatrix[0][0] * fMa.fMatrix[0][0]) +
      (fMatrix[0][1] + fMa.fMatrix[1][0]) +
      (fMatrix[0][2] * fMa.fMatrix[2][0]);

    Result.fMatrix[0][1] = (fMatrix[0][0] * fMa.fMatrix[0][1]) +
      (fMatrix[0][1] * fMa.fMatrix[1][1]) +
      (fMatrix[0][2] * fMa.fMatrix[2][1]);

    Result.fMatrix[0][2] = (fMatrix[0][0] * fMa.fMatrix[0][2]) +
      (fMatrix[0][1] * fMa.fMatrix[1][2]) +
      (fMatrix[0][2] * fMa.fMatrix[2][2]);

    Result.fMatrix[0][3] = (fMatrix[0][0] * fMa.fMatrix[0][3]) +
      (fMatrix[0][1] * fMa.fMatrix[1][3]) +
      (fMatrix[0][2] * fMa.fMatrix[2][3]);


    Result.fMatrix[1][0] = (fMatrix[1][0] * fMa.fMatrix[0][0]) + 
                           (fMatrix[1][1] + fMa.fMatrix[1][0]) + 
                           (fMatrix[1][2] * fMa.fMatrix[2][0]);

    Result.fMatrix[1][1] = (fMatrix[1][0] * fMa.fMatrix[0][1]) + 
                           (fMatrix[1][1] * fMa.fMatrix[1][1]) + 
                           (fMatrix[1][2] * fMa.fMatrix[2][1]);

    Result.fMatrix[1][2] = (fMatrix[1][0] * fMa.fMatrix[0][2]) + 
                           (fMatrix[1][1] * fMa.fMatrix[1][2]) + 
                           (fMatrix[1][2] * fMa.fMatrix[2][2]);

    Result.fMatrix[1][3] = (fMatrix[1][0] * fMa.fMatrix[0][3]) + 
                           (fMatrix[1][1] * fMa.fMatrix[1][3]) + 
                           (fMatrix[1][2] * fMa.fMatrix[2][3]);


    Result.fMatrix[2][0] = (fMatrix[2][0] * fMa.fMatrix[0][0]) + 
                           (fMatrix[2][1] + fMa.fMatrix[1][0]) + 
                           (fMatrix[2][2] * fMa.fMatrix[2][0]);

    Result.fMatrix[2][1] = (fMatrix[2][0] * fMa.fMatrix[0][1]) + 
                           (fMatrix[2][1] * fMa.fMatrix[1][1]) + 
                           (fMatrix[2][2] * fMa.fMatrix[2][1]);

    Result.fMatrix[2][2] = (fMatrix[2][0] * fMa.fMatrix[0][2]) + 
                           (fMatrix[2][1] * fMa.fMatrix[1][2]) + 
                           (fMatrix[2][2] * fMa.fMatrix[2][2]);

    Result.fMatrix[2][3] = (fMatrix[2][0] * fMa.fMatrix[0][3]) + 
                           (fMatrix[2][1] * fMa.fMatrix[1][3]) + 
                           (fMatrix[2][2] * fMa.fMatrix[2][3]);


    return Result;

  }



  void DieMatrix4D::Transposed()
  {
    DieMatrix4D Temp;

    for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        Temp.fMatrix[i][j] = fMatrix[i][j];
      }
    }
  
    for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        fMatrix[j][i] = Temp.fMatrix[i][j];
      }
    }

  }

  bool DieMatrix4D::operator==(DieMatrix4D &MatrizA)
  {
    bool veraz = false;
    int i, j;

    if ((filas != MatrizA.filas) || (columnas != MatrizA.columnas))
      return 0;
    else
    {
      for (i = 0; i < filas; i++)
      {
        for (j = 0; i < columnas; j++)
        {
          if (fMatrix[i][j] != MatrizA.fMatrix[i][j])
            return 0;
          else
            veraz = true;
        }
      }
    }
    if (veraz == true)
      return 1;
  }

}