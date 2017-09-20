#pragma once

#include "DiePrerequisitesGraphics.h"

namespace dieEngineSDK {

  struct DeviceDX;
  class DIE_GRAPHICS_EXPORT DieDevice
  {

  public:
    DieDevice();
    ~DieDevice();

    DeviceDX* m_pDevice;

    void Create();
    void Destroy();
    void* GetDevice();
    void** GetReference();
  };
}
