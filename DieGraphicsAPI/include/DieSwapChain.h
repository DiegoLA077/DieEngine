#pragma once

#include "DiePrerequisitesGraphics.h"
#include <d3d11.h>
//TODO: Cambiar include a cpp y hacer encapsulacion
namespace dieEngineSDK {

  class DIE_GRAPHICS_EXPORT DieSwapChain
  {
  private:
    IDXGISwapChain* pDie_SwapChain;
    HWND Die_hWnd = NULL;
    D3D_FEATURE_LEVEL DiefeatureLevel = D3D_FEATURE_LEVEL_11_0;
  public:
    DieSwapChain();
    ~DieSwapChain();

    //void InitDevice();
    void Create();
    void Destroy();
    void* GetObject();
    void** GetReference();
  };
}
