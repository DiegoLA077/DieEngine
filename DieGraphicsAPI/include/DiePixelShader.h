#pragma once

#include "DieShader.h"

class ID3D11PixelShader;

namespace dieEngineSDK
{
  class DieDevice;

  class DIE_GRAPHICS_EXPORT DiePixelShader : public DieShader
  {
  public:
    DiePixelShader() : DieShader(), m_pIPixelShader(nullptr) {}
    ~DiePixelShader() {};

    void Create(DieDevice* pDevice, String fileName, String entryPoint);

    ID3D11PixelShader* m_pIPixelShader;
  };
}
