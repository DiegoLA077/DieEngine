#pragma once

#include "DiePrerequisitesGraphics.h"

namespace dieEngineSDK {

  struct DeviceContextDX;
  class DIE_GRAPHICS_EXPORT DieDeviceContext
  {
  public:
    DeviceContextDX* m_DeviceContext;
    
  public:
    DieDeviceContext();
    ~DieDeviceContext();

    void Create();
    void Destroy();
    void* GetDeviceContext();
    void** GetReference();
    
  };
}