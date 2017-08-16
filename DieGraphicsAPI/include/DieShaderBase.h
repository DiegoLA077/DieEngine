#pragma once
#include "DiePrerequisitesGraphics.h"
#	include<d3d11.h>


namespace dieEngineSDK
{
  class DIE_GRAPHICS_EXPORT DieShaderBase
  {
  public:
    DieShaderBase();
    ~DieShaderBase();

  public:
    static const String SM_VS;
    static const String SM_PS;

  protected:
    ID3DBlob* m_pBlob;
  };
}
