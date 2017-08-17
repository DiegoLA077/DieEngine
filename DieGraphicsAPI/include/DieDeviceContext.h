#pragma once

#include "DiePrerequisitesGraphics.h"

namespace dieEngineSDK {

  class DIE_GRAPHICS_EXPORT DieDeviceContext
  {
  private:
    ID3D11DeviceContext* pDie_DeviceContext;
  public:
    DieDeviceContext();
    ~DieDeviceContext();

    void Create();
    void Destroy();
    void* getObject();
    void** GetReference();
    
  };
}