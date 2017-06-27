#include "DieDevice.h"

namespace dieEngineSDK {

  DieDevice::DieDevice()
  {
    pDie_Device = NULL;
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
    if (pDie_Device != nullptr)
    {
      pDie_Device->Release();
      pDie_Device = nullptr;
    }
  }

  void* DieDevice::GetObject()
  {
    return reinterpret_cast<void*>(pDie_Device);
  }

  void** DieDevice::GetReference()
  {
    return reinterpret_cast<void**>(&pDie_Device);
  }

}