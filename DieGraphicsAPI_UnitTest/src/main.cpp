#include <Win32/DieMinWindows.h>

#include <d3d11.h>

#include <iostream>
#include <vector>

#include <DieVector4D.h>
#include <DieDevice.h>
#include <DieDeviceContext.h>
#include <DieSwapChain.h>
#include <DieRenderTargetView.h>
#include <DiePixelShader.h>
#include <DieVertexShader.h>
#include <DieBufferVertex.h>
#include <DieBufferIndex.h>
#include <DieModel.h>


using namespace dieEngineSDK;
//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
HINSTANCE               g_hInst = NULL;
HWND                    g_hWnd = NULL;
D3D_DRIVER_TYPE         g_driverType = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL       g_featureLevel = D3D_FEATURE_LEVEL_11_0;

DieDevice               gDie_Device;
DieDeviceContext        gDie_DeviceContext;
DieSwapChain            gDie_SwapChain;

//TODO Hacer esto con mi estructura input layout y encapsular como es devido.
ID3D11InputLayout*      g_ILayOut;
DieRenderTargetView     gDie_RenderTargetView;

DieVertexBuffer         g_VertexBuffer;
DieIndexBuffer          g_IndexBuffer;

DiePixelShader          g_PS;
DieVertexShader         g_VS;

DieModel                g_Model;


//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
HRESULT InitDevice();
void CleanupDevice();
void SetInfoToRender();
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void Render();
void createVertexShader();

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  if (FAILED(InitWindow(hInstance, nCmdShow)))
    return 0;

  if (FAILED(InitDevice()))
  {
    CleanupDevice();
    return 0;
  }



  // Main message loop
  MSG msg = { 0 };
  while (WM_QUIT != msg.message)
  {

    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else
    {
      Render();
    }
  }

  CleanupDevice();

  return (int)msg.wParam;
}


//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow)
{
  //! Registramos ventana
  //HINSTANCE hInstance = GetModuleHandleA(0);
  WNDCLASSEXA wcex;
  memset(&wcex, 0, sizeof(WNDCLASSEXA));

  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = GetModuleHandle(NULL);
  wcex.hIcon = 0;
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
  wcex.lpszMenuName = 0;
  wcex.lpszClassName = "TutorialWindowClass";
  wcex.hIconSm = 0;
  if (!RegisterClassEx(&wcex))
    return E_FAIL;

  // Create window
  g_hInst = hInstance;
  RECT rc = { 0, 0, 1080, 720 };
  AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
  g_hWnd = CreateWindow("TutorialWindowClass", "DieEngine", WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT,1080, 720, NULL, NULL, hInstance,
    nullptr);
  if (!g_hWnd)
    return false;//throw exception("Fallo al crear la ventana"); 

  ShowWindow(g_hWnd, SW_SHOW);

  return S_OK;
}


//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  PAINTSTRUCT ps;
  HDC hdc;

  switch (message)
  {
  
  case WM_DESTROY:
    PostQuitMessage(0);
    break;

  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }

  return 0;
}

//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT InitDevice()
{
  HRESULT hr = S_OK;

  RECT rc;
  GetClientRect(g_hWnd, &rc);
  UINT width = rc.right - rc.left;
  UINT height = rc.bottom - rc.top;

  UINT createDeviceFlags = 0;
#ifdef _DEBUG
  createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

  D3D_DRIVER_TYPE driverTypes[] =
  {
    D3D_DRIVER_TYPE_HARDWARE,
    D3D_DRIVER_TYPE_WARP,
    D3D_DRIVER_TYPE_REFERENCE,
  };
  UINT numDriverTypes = ARRAYSIZE(driverTypes);

  D3D_FEATURE_LEVEL featureLevels[] =
  {
    D3D_FEATURE_LEVEL_11_0,
    D3D_FEATURE_LEVEL_10_1,
    D3D_FEATURE_LEVEL_10_0,
  };
  UINT numFeatureLevels = ARRAYSIZE(featureLevels);

  DXGI_SWAP_CHAIN_DESC sd;
  ZeroMemory(&sd, sizeof(sd));
  sd.BufferCount = 1;
  sd.BufferDesc.Width = width;
  sd.BufferDesc.Height = height;
  sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  sd.BufferDesc.RefreshRate.Numerator = 60;
  sd.BufferDesc.RefreshRate.Denominator = 1;
  sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
  sd.BufferDesc.Scaling = DXGI_MODE_SCALING_STRETCHED;
  sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_UNORDERED_ACCESS;
  sd.OutputWindow = g_hWnd;
  sd.SampleDesc.Count = 1;
  sd.SampleDesc.Quality = 0;
  sd.Windowed = true;
  sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
  sd.Flags = 0;

  ID3D11Device** ppDevice = reinterpret_cast<ID3D11Device**>(gDie_Device.GetReference());
  ID3D11DeviceContext** ppDeviceContext = reinterpret_cast<ID3D11DeviceContext**>(gDie_DeviceContext.GetReference());
  IDXGISwapChain** ppSwapChain = reinterpret_cast<IDXGISwapChain**>(gDie_SwapChain.GetReference());

  for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
  {
    //creaamos device , swapchain y deviceContext
    g_driverType = driverTypes[driverTypeIndex];
    hr = D3D11CreateDeviceAndSwapChain(NULL, g_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
      D3D11_SDK_VERSION, &sd, ppSwapChain, ppDevice, &g_featureLevel, ppDeviceContext);
    if (SUCCEEDED(hr))
      break;
  }
  if (FAILED(hr))
    return hr;

  ID3D11Device* pDevice = reinterpret_cast<ID3D11Device*>(gDie_Device.GetDevice());
  ID3D11DeviceContext* pDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(gDie_DeviceContext.GetDeviceContext());
  IDXGISwapChain* pSwapChain = reinterpret_cast<IDXGISwapChain*>(gDie_SwapChain.GetObject());

  // Create a render target view
  ID3D11Texture2D* pBackBuffer = nullptr;
  hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
  if (FAILED(hr))
    return hr;

  ID3D11RenderTargetView** pRenderTargetView = reinterpret_cast<ID3D11RenderTargetView**> (gDie_RenderTargetView.GetReference());
  SetInfoToRender();

  hr = pDevice->CreateRenderTargetView(pBackBuffer, NULL, pRenderTargetView);
  pBackBuffer->Release();
  if (FAILED(hr))
    return hr;

  //TODO Cambiar de nombre a esta funcion y organizar todo. en funciones.
  createVertexShader();


  D3D11_INPUT_ELEMENT_DESC layout[] =
  {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    //vector3 Normal  12 16-28
    //vector2 texcord 8 
  };

  ID3DBlob* pErrorBlob;
  pDevice->CreateInputLayout(layout, 1, g_VS.m_pBlob->GetBufferPointer(), g_VS.m_pBlob->GetBufferSize(), &g_ILayOut);

  pDeviceContext->OMSetRenderTargets(1, pRenderTargetView, NULL);
  // Setup the viewport
  D3D11_VIEWPORT vp;
  vp.Width = (FLOAT)width;
  vp.Height = (FLOAT)height;
  vp.MinDepth = 0.0f;
  vp.MaxDepth = 1.0f;
  vp.TopLeftX = 0;
  vp.TopLeftY = 0;
  pDeviceContext->RSSetViewports(1, &vp);
  return S_OK;
}

void SetInfoToRender()
{
  std::vector<VERTEX> VectorVertex;
   VERTEX VertexA;
   VertexA.m_Pos.x = 0.0f;
   VertexA.m_Pos.y = 0.5f;
   VertexA.m_Pos.z = 0.5f;
   VertexA.m_Pos.w = 1.0f;
   VectorVertex.push_back(VertexA);
   VERTEX VertexB;
   VertexB.m_Pos.x = 0.5f;
   VertexB.m_Pos.y = -0.5f;
   VertexB.m_Pos.z = 0.5f;
   VertexB.m_Pos.w = 1.0f;
   VectorVertex.push_back(VertexB);
   VERTEX VertexC;
   VertexC.m_Pos.x = -0.5f;
   VertexC.m_Pos.y = -0.5f;
   VertexC.m_Pos.z = 0.5f;
   VertexC.m_Pos.w = 1.0f;
   VectorVertex.push_back(VertexC);
   g_VertexBuffer.CreateHardwareBuffer(&gDie_Device,VectorVertex);

   std::vector<unsigned int> VectorIndices;
    VectorIndices.push_back(0);
    VectorIndices.push_back(1);
    VectorIndices.push_back(2);
    g_IndexBuffer.CreateHardwareBuffer(&gDie_Device, VectorIndices);
}

void createVertexShader()
{
  g_VS.Create(&gDie_Device, "Resource\\Shaders\\ShaderTest.hlsl", "main_VS");
  g_PS.Create(&gDie_Device, "Resource\\Shaders\\ShaderTest.hlsl", "main_PS");
  g_Model.loadModel("Resource\\Models\\Cube.3ds");
 
}

//--------------------------------------------------------------------------------------
// Render the frame
//--------------------------------------------------------------------------------------
void Render()
{
  // Just clear the backbuffer
  float ClearColor[4] = { 0.0f, 1.0f, 1.0f, 1.0f }; //red,green,blue,alpha

  ID3D11RenderTargetView* pRenderTargetView = reinterpret_cast<ID3D11RenderTargetView*> (gDie_RenderTargetView.GetObject());
  ID3D11DeviceContext* pDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(gDie_DeviceContext.GetDeviceContext());
  IDXGISwapChain* pSwapChain = reinterpret_cast<IDXGISwapChain*>(gDie_SwapChain.GetObject());

  pDeviceContext->ClearRenderTargetView(pRenderTargetView, ClearColor);
  
  g_IndexBuffer.SetHardwareBuffer(&gDie_DeviceContext);
  g_VertexBuffer.SetHardwareBuffer(&gDie_DeviceContext);

  pDeviceContext->IASetInputLayout(g_ILayOut);
  pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  pDeviceContext->VSSetShader(g_VS.m_pIVertexShader, NULL, NULL);
  pDeviceContext->PSSetShader(g_PS.m_pIPixelShader, NULL, NULL);
  /**/
  g_Model.CreateIndexBuffer(&gDie_Device);
  g_Model.CreateVertexBuffer(&gDie_Device);
  /**/
  pDeviceContext->DrawIndexed(3, 0, 0);
  pSwapChain->Present(1, 0);
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void CleanupDevice()
{
  //if (g_pImmediateContext) g_pImmediateContext->ClearState();

  //if (pRenderTargetView) pRenderTargetView
  //if (g_pSwapChain) g_pSwapChain->Release();
  //if (g_pImmediateContext) g_pImmediateContext->Release();
  //if (g_pd3dDevice) g_pd3dDevice->Release();
}