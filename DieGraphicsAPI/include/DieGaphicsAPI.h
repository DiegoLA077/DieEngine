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
    /**
    * @brief Variable miembro DieDevice m_Device: Contiene el device de diretx
    */
    DieDevice                 m_Device;
   
    /**
    * @brief Variable miembro DieDeviceContext m_DeviceContext: Contiene el device context de diretx
    */
    DieDeviceContext          m_DeviceContext;

    /**
    * @brief Variable miembro DieSwapChain m_SwapChain: Contiene el swap chain de diretx
    */
    DieSwapChain              m_SwapChain;

    /**
    * @brief Variable miembro DieRenderTargetView m_pRenderTargetView: Contiene el Render Target View de diretx
    */
    DieRenderTargetView       m_pRenderTargetView;

    /**
    * @brief Constructor de DieGraphicsAPI
    */
    DieGraphicsAPI() {}

    /**
    * @brief Destructor de DieGraphicsAPI
    */
    ~DieGraphicsAPI();
  };

  DIE_GRAPHICS_EXPORT DieGraphicsAPI& g_GraphicsAPI();
}