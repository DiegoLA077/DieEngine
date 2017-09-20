#include "DieRenderTargetView.h"
namespace dieEngineSDK
{
  DieRenderTargetView::DieRenderTargetView()
  {
    pDie_RenderTargetView = NULL;
  }

  DieRenderTargetView::~DieRenderTargetView()
  {
    Destroy();
  }

  void DieRenderTargetView::Create()
  {
  }

  void DieRenderTargetView::Destroy()
  {
    if (pDie_RenderTargetView != nullptr)
    {
      pDie_RenderTargetView->Release();
      pDie_RenderTargetView = nullptr;
    }
  }

  void* DieRenderTargetView::GetObject()
  {
    return reinterpret_cast<void*>(pDie_RenderTargetView);
  }

  void** DieRenderTargetView::GetReference()
  {
    return reinterpret_cast<void**>(&pDie_RenderTargetView);
  }
}