#include "DieDeviceContext.h"

dieEngineSDK::DieDeviceContext::DieDeviceContext()
{
  pDie_DeviceContext = NULL;
}

dieEngineSDK::DieDeviceContext::~DieDeviceContext()
{
  Destroy();
}

void dieEngineSDK::DieDeviceContext::Create()
{
}

void dieEngineSDK::DieDeviceContext::Destroy()
{
  if (pDie_DeviceContext != nullptr)
  {
    pDie_DeviceContext->Release();
    pDie_DeviceContext = nullptr;
  }
}

void* dieEngineSDK::DieDeviceContext::getObject()
{
  return reinterpret_cast<void*>(pDie_DeviceContext);
}

void** dieEngineSDK::DieDeviceContext::GetReference()
{
  return reinterpret_cast<void**>(&pDie_DeviceContext);
}
