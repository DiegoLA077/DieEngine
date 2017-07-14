#pragma once

#include <DiePrerequisitesGraphics.h>

namespace dieEngineSDK {

  class DIE_GRAPHICS_EXPORT DieRenderTargetView
  {
  private:
    ID3D11RenderTargetView* pDie_RenderTargetView;
  public:
    DieRenderTargetView();
    ~DieRenderTargetView();

    void Create();
    void Destroy();
    void* GetObject();
    void** GetReference();
  };
}