#pragma once

#include "DiePrerequisitesGraphics.h"

namespace dieEngineSDK {

  class DIE_GRAPHICS_EXPORT DieSwapChain
  {
  private:
    IDXGISwapChain* pDie_SwapChain;
  public:
    DieSwapChain();
    ~DieSwapChain();

    void Create();
    void Destroy();
    void* GetObject();
    void** GetReference();
  };
}
