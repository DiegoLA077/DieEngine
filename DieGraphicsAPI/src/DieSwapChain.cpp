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

  //--------------------------------------------------------------------------------------
  // Create Direct3D device and swap chain
  //--------------------------------------------------------------------------------------
//  void DieSwapChain::InitDevice()
//  {
//    HRESULT hr = S_OK;
//
//    RECT rc;
//    GetClientRect(Die_hWnd, &rc);
//    UINT width = rc.right - rc.left;
//    UINT height = rc.bottom - rc.top;
//
//    UINT createDeviceFlags = 0;
//#ifdef _DEBUG
//    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
//#endif
//
//    D3D_DRIVER_TYPE driverTypes[] =
//    {
//      D3D_DRIVER_TYPE_HARDWARE,
//      D3D_DRIVER_TYPE_WARP,
//      D3D_DRIVER_TYPE_REFERENCE,
//    };
//    UINT numDriverTypes = ARRAYSIZE(driverTypes);
//
//    D3D_FEATURE_LEVEL featureLevels[] =
//    {
//      D3D_FEATURE_LEVEL_11_0,
//      D3D_FEATURE_LEVEL_10_1,
//      D3D_FEATURE_LEVEL_10_0,
//    };
//    UINT numFeatureLevels = ARRAYSIZE(featureLevels);
//
//    DXGI_SWAP_CHAIN_DESC sd;
//    ZeroMemory(&sd, sizeof(sd));
//    sd.BufferCount = 1;
//    sd.BufferDesc.Width = width;
//    sd.BufferDesc.Height = height;
//    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//    sd.BufferDesc.RefreshRate.Numerator = 60;
//    sd.BufferDesc.RefreshRate.Denominator = 1;
//    sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
//    sd.BufferDesc.Scaling = DXGI_MODE_SCALING_STRETCHED;
//    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_UNORDERED_ACCESS;
//    sd.OutputWindow = Die_hWnd;
//    sd.SampleDesc.Count = 1;
//    sd.SampleDesc.Quality = 0;
//    sd.Windowed = true;
//    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
//    sd.Flags = 0;
//
//    ID3D11Device** ppDevice = reinterpret_cast<ID3D11Device**>(gDie_Device.GetReference());
//    ID3D11DeviceContext** ppDeviceContext = reinterpret_cast<ID3D11DeviceContext**>(gDie_DeviceContext.GetReference());
//    IDXGISwapChain** ppSwapChain = reinterpret_cast<IDXGISwapChain**>(gDie_SwapChain.GetReference());
//
//    for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
//    {
//      //creaamos device , swapchain y deviceContext
//      g_driverType = driverTypes[driverTypeIndex];
//      hr = D3D11CreateDeviceAndSwapChain(NULL, g_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
//        D3D11_SDK_VERSION, &sd, ppSwapChain, ppDevice, &g_featureLevel, ppDeviceContext);
//      if (SUCCEEDED(hr))
//        break;
//    }
//    if (FAILED(hr))
//      return hr;
//
//    ID3D11Device* pDevice = reinterpret_cast<ID3D11Device*>(gDie_Device.GetDevice());
//    ID3D11DeviceContext* pDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(gDie_DeviceContext.GetDeviceContext());
//    IDXGISwapChain* pSwapChain = reinterpret_cast<IDXGISwapChain*>(gDie_SwapChain.GetObject());
//
//    // Create a render target view
//    ID3D11Texture2D* pBackBuffer = nullptr;
//    hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
//    if (FAILED(hr))
//      return hr;
//
//    ID3D11RenderTargetView** pRenderTargetView = reinterpret_cast<ID3D11RenderTargetView**> (gDie_RenderTargetView.GetReference());
//    SetInfoToRender();
//
//    hr = pDevice->CreateRenderTargetView(pBackBuffer, NULL, pRenderTargetView);
//    pBackBuffer->Release();
//    if (FAILED(hr))
//      return hr;
//
//    //TODO Cambiar de nombre a esta funcion y organizar todo. en funciones.
//    createVertexShader();
//
//
//    D3D11_INPUT_ELEMENT_DESC layout[] =
//    {
//      { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//      //vector3 Normal  12 16-28
//      //vector2 texcord 8 
//    };
//
//    ID3DBlob* pErrorBlob;
//    pDevice->CreateInputLayout(layout, 1, g_VS.m_pBlob->GetBufferPointer(), g_VS.m_pBlob->GetBufferSize(), &g_ILayOut);
//
//    pDeviceContext->OMSetRenderTargets(1, pRenderTargetView, NULL);
//    // Setup the viewport
//    D3D11_VIEWPORT vp;
//    vp.Width = (FLOAT)width;
//    vp.Height = (FLOAT)height;
//    vp.MinDepth = 0.0f;
//    vp.MaxDepth = 1.0f;
//    vp.TopLeftX = 0;
//    vp.TopLeftY = 0;
//    pDeviceContext->RSSetViewports(1, &vp);
//    return S_OK;
//  }

}