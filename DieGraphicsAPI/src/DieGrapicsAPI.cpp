#include "DieGaphicsAPI.h"

namespace dieEngineSDK {
  DieGraphicsAPI::~DieGraphicsAPI()
  {
    m_pRenderTargetView.Destroy();
    m_SwapChain.Destroy();
    m_DeviceContext.Destroy();
    m_Device.Destroy();
  }

  DieGraphicsAPI& g_GraphicsAPI()
  {
    return DieGraphicsAPI::instance();
  }
}