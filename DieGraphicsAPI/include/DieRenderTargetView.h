#pragma once

#include <DiePrerequisitesGraphics.h>
#include <d3d11.h>
//TODO: Cambiar include a cpp y hacer encapsulacion
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