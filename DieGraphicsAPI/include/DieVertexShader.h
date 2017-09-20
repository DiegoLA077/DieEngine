#pragma once
#include "DieShader.h"
//TODO: Encapsular
class ID3D11VertexShader;

namespace dieEngineSDK
{

  class DIE_GRAPHICS_EXPORT DieVertexShader : public DieShader
  {
  public:
    DieVertexShader() : DieShader(), m_pIVertexShader(nullptr) {}
    virtual~DieVertexShader() {}

    void Create(DieDevice* Device, const String& fileName, const String& entryPoint);

    ID3D11VertexShader* m_pIVertexShader;
  };
}
