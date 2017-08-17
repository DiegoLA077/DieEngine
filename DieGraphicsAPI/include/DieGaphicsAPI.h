#pragma once

#include "DiePrerequisites.h"
#include <DieModulo.h>
#include "DieDevice.h"
#include "DieDeviceContext.h"
#include "DieSwapChain.h"
#include "DieRenderTargetView.h"

namespace dieEngineSDK
{

  class DIE_GRAPHICS_EXPORT DieGraphicsAPI : public DieModule<DieGraphicsAPI>
  {
  public:
    DieDevice                 m_Device;
    DieDeviceContext          m_DeviceContext;
    DieSwapChain              m_SwapChain;
    DieRenderTargetView       m_pRenderTargetView;

    DieGraphicsAPI() {}
    ~DieGraphicsAPI();
  };

  DIE_GRAPHICS_EXPORT DieGraphicsAPI& g_GraphicsAPI();
}