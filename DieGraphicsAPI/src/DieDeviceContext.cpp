#include "DieDeviceContext.h"
#include <d3d11.h>

namespace dieEngineSDK
{
  struct DeviceContextDX
  {
    ID3D11DeviceContext* pDie_DeviceContext;
    void Destroy() { if (pDie_DeviceContext != nullptr)pDie_DeviceContext->Release(); }
  };
  DieDeviceContext::DieDeviceContext()
  {
    m_DeviceContext = nullptr;
    m_DeviceContext = new DeviceContextDX();
  }

  DieDeviceContext::~DieDeviceContext()
  {
    Destroy();
  }

  void DieDeviceContext::Create()
  {
  }

  void DieDeviceContext::Destroy()
  {
    if (m_DeviceContext != nullptr)
    {
      m_DeviceContext->Destroy();
      delete m_DeviceContext;
      m_DeviceContext  = nullptr;
    }
  }

  void* DieDeviceContext::GetDeviceContext()
  {
    return reinterpret_cast<void*>(m_DeviceContext->pDie_DeviceContext);
  }

  void** DieDeviceContext::GetReference()
  {
    return reinterpret_cast<void**>(&m_DeviceContext->pDie_DeviceContext);
  }
}