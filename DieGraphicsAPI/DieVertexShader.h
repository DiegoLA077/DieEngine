#pragma once
#include "DieShaderBase.h"

namespace dieEngineSDK
{
  class DIE_GRAPHICS_EXPORT DieVertextShader : public DieShaderBase
  {
  public:
    DieVertextShader();
    ~DieVertextShader();

  public:
    ID3D11VertexShader* m_pVertecShader;

    void create(std::string prmFileName, std::string prmEntryPoint);
    void destroy();
  };
}
