#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>

namespace dieEngineSDK {

  class DieDeviceContext
  {
    DieDeviceContext();
    ~DieDeviceContext();


    ID3D11DeviceContext* Die_DeviceContext;
  };
}