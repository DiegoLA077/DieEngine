#pragma once

#include "DiePrerequisitesGraphics.h"

namespace dieEngineSDK {

  class DIE_GRAPHICS_EXPORT DieDevice
  {
  private:
    ID3D11Device* pDie_Device;
  public:
    DieDevice();
    ~DieDevice();

    void Create();
    void Destroy();
    void* GetObject();
    void** GetReference();
  };
}
