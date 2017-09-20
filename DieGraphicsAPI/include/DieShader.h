#pragma once

#include "DiePrerequisitesGraphics.h"
#include "DieDevice.h"
#include <d3dcompiler.h>
#include <d3d11.h>
//TODO: Cambiar include a cpp y hacer encapsulacion
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