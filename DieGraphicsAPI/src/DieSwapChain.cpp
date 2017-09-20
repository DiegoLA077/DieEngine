#include "DieSwapChain.h"

namespace dieEngineSDK
{
  DieSwapChain::DieSwapChain()
  {
    pDie_SwapChain = NULL;
  }

  DieSwapChain::~DieSwapChain()
  {
    Destroy();
  }

  void DieSwapChain::Create()
  {
  }

  void DieSwapChain::Destroy()
  {
    if (pDie_SwapChain != nullptr)
    {
      pDie_SwapChain->Release();
      pDie_SwapChain = nullptr;
    }
  }

  void* DieSwapChain::GetObject()
  {
    return reinterpret_cast<void*>(pDie_SwapChain);
  }

  void** DieSwapChain::GetReference()
  {
    return reinterpret_cast<void**>(&pDie_SwapChain);
  }
}