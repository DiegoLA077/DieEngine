#include "DieRenderTargetView.h"

dieEngineSDK::DieRenderTargetView::DieRenderTargetView()
{
  pDie_RenderTargetView = NULL;
}

dieEngineSDK::DieRenderTargetView::~DieRenderTargetView()
{
  Destroy();
}

void dieEngineSDK::DieRenderTargetView::Create()
{
}

void dieEngineSDK::DieRenderTargetView::Destroy()
{
  if (pDie_RenderTargetView != nullptr)
  {
    pDie_RenderTargetView->Release();
    pDie_RenderTargetView = nullptr;
  }
}

void* dieEngineSDK::DieRenderTargetView::GetObject()
{
  return reinterpret_cast<void*>(pDie_RenderTargetView);
}

void** dieEngineSDK::DieRenderTargetView::GetReference()
{
  return reinterpret_cast<void**>(&pDie_RenderTargetView);
}
