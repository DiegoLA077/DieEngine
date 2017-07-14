#include "DieSwapChain.h"

dieEngineSDK::DieSwapChain::DieSwapChain()
{
  pDie_SwapChain = NULL;
}

dieEngineSDK::DieSwapChain::~DieSwapChain()
{
  Destroy();
}

void dieEngineSDK::DieSwapChain::Create()
{
}

void dieEngineSDK::DieSwapChain::Destroy()
{
  if (pDie_SwapChain != nullptr)
  {
    pDie_SwapChain->Release();
    pDie_SwapChain = nullptr;
  }
}

void* dieEngineSDK::DieSwapChain::GetObject()
{
  return reinterpret_cast<void*>(pDie_SwapChain);
}

void** dieEngineSDK::DieSwapChain::GetReference()
{
  return reinterpret_cast<void**>(&pDie_SwapChain);
}
