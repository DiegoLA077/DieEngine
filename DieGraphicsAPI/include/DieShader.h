#pragma once

#include "DiePrerequisitesGraphics.h"

namespace dieEngineSDK
{
  class DIE_GRAPHICS_EXPORT DieShader
  {
  public:
    DieShader() : m_pBlob(nullptr){};
    virtual ~DieShader() {};

    void Compile(const String& fileName, const String& entryPoint, const String& targetStr);

    ID3DBlob* m_pBlob;
  };
}
