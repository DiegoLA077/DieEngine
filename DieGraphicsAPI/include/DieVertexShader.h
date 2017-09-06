#pragma once

#include "DieShader.h"

class ID3D11VertexShader;

namespace dieEngineSDK
{
  class DieDevice;

  class DIE_GRAPHICS_EXPORT DieVertexShader : public DieShader
  {
  public:
    DieVertexShader() : DieShader(), m_pIVertexShader(nullptr) {};
    ~DieVertexShader() {};

    void Create(DieDevice* pDevice, const String& fileName, const String& entryPoint);

    ID3D11VertexShader* m_pIVertexShader;
  };
}
