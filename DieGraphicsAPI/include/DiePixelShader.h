#pragma once
#include "DieShader.h"

namespace dieEngineSDK
{
  class DIE_GRAPHICS_EXPORT DiePixelShader : public DieShader
  {
  public:
    DiePixelShader() : DieShader(), m_pIPixelShader(nullptr) {}
    virtual~DiePixelShader() {}

    void Create(DieDevice* Device, const String& fileName, const String& entryPoint);

    ID3D11PixelShader* m_pIPixelShader;
  };
}
