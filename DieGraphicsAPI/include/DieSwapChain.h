#pragma once

#include "DiePrerequisitesGraphics.h"
#include <d3d11.h>
//TODO: Cambiar include a cpp y hacer encapsulacion
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
