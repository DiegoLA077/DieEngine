#include "DieDevice.h"
#include <d3d11.h>


namespace dieEngineSDK {

  struct DeviceDX
  {
    ID3D11Device* pDie_Device;
    void Destroy() { if (pDie_Device != nullptr) pDie_Device->Release(); };
  };

  DieDevice::DieDevice()
  {
    m_pDevice = nullptr;
    m_pDevice = new DeviceDX();
  }

  DieDevice::~DieDevice()
  {
    Destroy();
  }

  void DieDevice::Create()
  {
  }

  void DieDevice::Destroy()
  {
    if (m_pDevice != nullptr)
    {
      m_pDevice->Destroy();
      delete m_pDevice;
      m_pDevice = nullptr;
    }
  }

  void* DieDevice::GetDevice()
  {
    return reinterpret_cast<void*>(m_pDevice->pDie_Device);
  }

  void** DieDevice::GetReference()
  {
    return reinterpret_cast<void**>(&m_pDevice->pDie_Device);
  }

}