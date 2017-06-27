#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>

namespace dieEngineSDK {

  class DieRenderTargetView
  {
    DieRenderTargetView();
    ~DieRenderTargetView();


    ID3D11RenderTargetView* Die_RenderTargetView;
  };
}