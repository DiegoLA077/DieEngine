#include <Win32/DieMinWindows.h>

#include <iostream>
#include <vector>

#include <DieVector4D.h>
#include <DieDevice.h>
#include <DieDeviceContext.h>
#include <DieSwapChain.h>
#include <DieRenderTargetView.h>
#include <DiePixelShader.h>
#include <DieVertexShader.h>
#include <DieBufferBase.h>

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
DieRenderTargetView     gDie_RenderTargetView;

DieVertexBuffer<DIEVERTEX>         g_VertexBuffer;
DieIndexBuffer32        g_IndexBuffer;

DiePixelShader          g_PS;
DieVertexShader         g_VS;

//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
HRESULT InitDevice();
void CleanupDevice();
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
      //SetInfoToRender();
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
  // Register class
  WNDCLASSEX wcex;
  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = 0;
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = NULL;
  wcex.lpszClassName = "TutorialWindowClass";
  wcex.hIconSm = 0;
  if (!RegisterClassEx(&wcex))
    return E_FAIL;

  // Create window
  g_hInst = hInstance;
  RECT rc = { 0, 0, 1080, 720 };
  AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
  g_hWnd = CreateWindow("TutorialWindowClass", "DieEngine", WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
    NULL);
  if (!g_hWnd)
    return E_FAIL;

  ShowWindow(g_hWnd, nCmdShow);

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
  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);
    EndPaint(hWnd, &ps);
    break;

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
  sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  sd.OutputWindow = g_hWnd;
  sd.SampleDesc.Count = 1;
  sd.SampleDesc.Quality = 0;
  sd.Windowed = TRUE;

  ID3D11Device** ppDevice = reinterpret_cast<ID3D11Device**>(gDie_Device.GetReference());
  ID3D11DeviceContext** ppDeviceContext = reinterpret_cast<ID3D11DeviceContext**>(gDie_DeviceContext.GetReference());
  IDXGISwapChain** ppSwapChain = reinterpret_cast<IDXGISwapChain**>(gDie_SwapChain.GetReference());

  for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
  {
    g_driverType = driverTypes[driverTypeIndex];
    hr = D3D11CreateDeviceAndSwapChain(NULL, g_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
      D3D11_SDK_VERSION, &sd, ppSwapChain, ppDevice, &g_featureLevel, ppDeviceContext);
    if (SUCCEEDED(hr))
      break;
  }
  if (FAILED(hr))
    return hr;

  ID3D11Device* pDevice = reinterpret_cast<ID3D11Device*>(gDie_Device.GetObject());
  ID3D11DeviceContext* pDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(gDie_DeviceContext.getObject());
  IDXGISwapChain* pSwapChain = reinterpret_cast<IDXGISwapChain*>(gDie_SwapChain.GetObject());

  // Create a render target view
  ID3D11Texture2D* pBackBuffer = NULL;
  hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
  if (FAILED(hr))
    return hr;

  ID3D11RenderTargetView** pRenderTargetView = reinterpret_cast<ID3D11RenderTargetView**> (gDie_RenderTargetView.GetReference());

  hr = pDevice->CreateRenderTargetView(pBackBuffer, NULL, pRenderTargetView);
  pBackBuffer->Release();
  if (FAILED(hr))
    return hr;

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

  createVertexShader();

  return S_OK;
}

void SetInfoToRender()
{
  ID3DBlob* MyShaderCompileInfoCode;

  ID3D11InputLayout* ILayOut;

  D3D11_INPUT_ELEMENT_DESC layout[] =
  {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
  };


  ID3DBlob* pErrorBlob;
  HRESULT hr;

  ID3D11Device* pDevice = reinterpret_cast<ID3D11Device*>(gDie_Device.GetObject());
  ID3D11DeviceContext* pDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(gDie_DeviceContext.getObject());

  pDevice->CreateInputLayout(layout, 0, g_VS.m_pBlob->GetBufferPointer(), g_VS.m_pBlob->GetBufferSize(), &ILayOut);

  pDeviceContext->IASetInputLayout(ILayOut);

  //Create VertexBuffer
  g_VertexBuffer.Add({ DieVector4D(0.0f, 0.5f, 0.5f, 0.f) });
  g_VertexBuffer.Add({ DieVector4D(0.5f, -0.5f,   0.5f, 0.f) });
  g_VertexBuffer.Add({ DieVector4D(-0.5f, -0.5f,  0.5f, 0.f) });
  g_VertexBuffer.CreateHardwareBuffer();

  g_IndexBuffer.Add(1);
  g_IndexBuffer.Add(2);
  g_IndexBuffer.Add(3);
  g_IndexBuffer.CreateHardwareBuffer();

  pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
 
}

void createVertexShader()
{
  g_VS.Create(&gDie_Device, "Resource\\Shaders\\ShaderTest.hlsl", "main_VS");
  g_PS.Create(&gDie_Device, "Resource\\Shaders\\ShaderTest.hlsl", "main_PS");
}

//void cancer()
//{
//  std::string fileName = "ShaderTest.hlsl";
//  std::ifstream myFileStream(fileName, std::ios::binary & std::ios::ate);
//
//  if (!myFileStream.is_open())
//  {
//    std::cout << "Cancer";
//
//    return;
//  }
//
//  unsigned int fileLeght = myFileStream.tellg();
//  myFileStream.seekg(std::fstream::beg);
//
//  std::vector<char> pBuffer(fileLeght);
//  myFileStream.read(&pBuffer[0], fileLeght);
//
//  std::string myfileContent;
//  myfileContent.reserve(fileLeght);
//  myfileContent.insert(myfileContent.begin(), pBuffer.begin(), pBuffer.end());
//
//  std::cout << "El Archivo pesa: " << fileLeght << " bytes" << std::endl;
//  std::cout << "GG" << std::endl;
//
//  std::ofstream fileOut("exitFile.txt", std::ios::binary);
//  fileOut.write(reinterpret_cast<char*> (&myfileContent), sizeof(myfileContent));
//  fileOut.close();
//
//}

//--------------------------------------------------------------------------------------
// Render the frame
//--------------------------------------------------------------------------------------
void Render()
{
  // Just clear the backbuffer
  float ClearColor[4] = { 0.0f, 1.0f, 1.0f, 1.0f }; //red,green,blue,alpha

  ID3D11RenderTargetView* pRenderTargetView = reinterpret_cast<ID3D11RenderTargetView*> (gDie_RenderTargetView.GetObject());
  ID3D11Device* pDevice = reinterpret_cast<ID3D11Device*>(gDie_Device.GetObject());
  ID3D11DeviceContext* pDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(gDie_DeviceContext.getObject());
  IDXGISwapChain* pSwapChain = reinterpret_cast<IDXGISwapChain*>(gDie_SwapChain.GetObject());

  pDeviceContext->ClearRenderTargetView(pRenderTargetView, ClearColor);
  
  pDeviceContext->VSSetShader(g_VS.m_pIVertexShader, NULL, NULL);
  pDeviceContext->PSSetShader(g_PS.m_pIPixelShader, NULL, NULL);

  g_IndexBuffer.SetHardwareBuffer(&gDie_DeviceContext, 0);
  g_VertexBuffer.SetHardwareBuffer();
  pDeviceContext->Draw(3, 0);
  pSwapChain->Present(0, 0);
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
