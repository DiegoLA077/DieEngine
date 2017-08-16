#include <Win32/DieMinWindows.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

#include <DieVector4D.h>
#include <DieDevice.h>
#include <DieDeviceContext.h>
#include <DieSwapChain.h>
#include <DieRenderTargetView.h>

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

ID3DBlob* pVertexShader = nullptr;
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


ID3D11Device** pDevice = reinterpret_cast<ID3D11Device**> (gDie_Device.GetReference());
ID3D11DeviceContext** pDeviceContext = reinterpret_cast<ID3D11DeviceContext**> (gDie_DeviceContext.GetReference());
IDXGISwapChain** pSwapChain = reinterpret_cast<IDXGISwapChain**> (gDie_SwapChain.GetReference());
ID3D11RenderTargetView** pRenderTargetView = reinterpret_cast<ID3D11RenderTargetView**> (gDie_RenderTargetView.GetReference());
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



  for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
  {
    g_driverType = driverTypes[driverTypeIndex];
    hr = D3D11CreateDeviceAndSwapChain(NULL, g_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
      D3D11_SDK_VERSION, &sd, pSwapChain, pDevice, &g_featureLevel, pDeviceContext);
    if (SUCCEEDED(hr))
      break;
  }
  if (FAILED(hr))
    return hr;

  // Create a render target view
  ID3D11Texture2D* pBackBuffer = NULL;
  hr = (*pSwapChain)->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
  if (FAILED(hr))
    return hr;

  ID3D11RenderTargetView** pRenderTargetView = reinterpret_cast<ID3D11RenderTargetView**> (gDie_RenderTargetView.GetReference());

  hr = (*pDevice)->CreateRenderTargetView(pBackBuffer, NULL, pRenderTargetView);
  pBackBuffer->Release();
  if (FAILED(hr))
    return hr;

  (*pDeviceContext)->OMSetRenderTargets(1, pRenderTargetView, NULL);

  // Setup the viewport
  D3D11_VIEWPORT vp;
  vp.Width = (FLOAT)width;
  vp.Height = (FLOAT)height;
  vp.MinDepth = 0.0f;
  vp.MaxDepth = 1.0f;
  vp.TopLeftX = 0;
  vp.TopLeftY = 0;
  (*pDeviceContext)->RSSetViewports(1, &vp);

  createVertexShader();

  return S_OK;
}


ID3D11Buffer* pVertexB;
ID3D11Buffer* pIndexB;

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


  (*pDevice)->CreateInputLayout(layout, 0, pVertexShader->GetBufferPointer(), pVertexShader->GetBufferSize(), &ILayOut);

  (*pDeviceContext)->IASetInputLayout(ILayOut);
    
  //Create VertexBuffer

  struct Vertex
  {
    DieVector4D m_Pos;
  };
  Vertex VerToRender[3]
  {
    DieVector4D(0.0f, 0.5f, 0.5f, 0.f),
    DieVector4D(0.5f, -0.5f,   0.5f, 0.f),
    DieVector4D(-0.5f, -0.5f,  0.5f, 0.f)
  };


  D3D11_BUFFER_DESC DesVerBuffer;
  DesVerBuffer.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  DesVerBuffer.ByteWidth = sizeof(Vertex) * 3; //Tamaño buffer  
  DesVerBuffer.CPUAccessFlags = 0;
  DesVerBuffer.MiscFlags = 0;
  DesVerBuffer.Usage = D3D11_USAGE_DEFAULT;

  D3D11_SUBRESOURCE_DATA InitData;
  ZeroMemory(&InitData, sizeof(InitData));
  InitData.pSysMem = VerToRender;

  (*pDevice)->CreateBuffer(&DesVerBuffer, &InitData, &pVertexB);


  //Index Buffer
  struct INDEX
  {
    UINT m_Pos;

  };

  INDEX IndexToRender[3]
  {
    1,2,3
  };


  D3D11_BUFFER_DESC DesIndBuffer;
  DesIndBuffer.BindFlags = D3D11_BIND_INDEX_BUFFER;
  DesIndBuffer.ByteWidth = sizeof(INDEX) * 3; //Tamaño buffer  
  DesIndBuffer.CPUAccessFlags = 0;
  DesIndBuffer.MiscFlags = 0;
  DesIndBuffer.Usage = D3D11_USAGE_DEFAULT;

  D3D11_SUBRESOURCE_DATA mInitData;
  ZeroMemory(&mInitData, sizeof(mInitData));
  mInitData.pSysMem = IndexToRender;

  (*pDevice)->CreateBuffer(&DesIndBuffer, &mInitData, &pIndexB);


  UINT stride = sizeof(Vertex);

}

void createVertexShader()
{
  std::string prmFileName;
  std::string prmEntryPoint;
  /************************************************************************/
  std::string fileName = "Resource\\Shaders\\ShaderTest.hlsl";
  std::fstream myFileStream;
  myFileStream.open(fileName, std::ios::in | std::ios::out | std::ios::ate);
  unsigned int fileLeght = myFileStream.tellg();
  myFileStream.seekg(0, std::ios::beg);

  std::string pBuffer;
  pBuffer.resize(fileLeght + 1, 0);
  myFileStream.read(&pBuffer[0], fileLeght);

  myFileStream.close();
  /************************************************************************/


  // Compile the vertex shader
  HRESULT hr = S_OK;

  DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
  // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
  // Setting this flag improves the shader debugging experience, but still allows 
  // the shaders to be optimized and to run exactly the way they will run in 
  // the release configuration of this program.
  dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

  ID3DBlob* pErrorBlob;
 
  ID3D11VertexShader* VertexShader = nullptr;
  hr = D3DCompile(pBuffer.c_str(), pBuffer.size(), fileName.c_str(), NULL, NULL,
    "VS", "vs_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_ENABLE_STRICTNESS, 0, &pVertexShader, &pErrorBlob);
  if (FAILED(hr))
  {
    if (pErrorBlob != NULL)
      OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
    if (pErrorBlob) pErrorBlob->Release();
  }
  if (pErrorBlob) pErrorBlob->Release();

  // Create the vertex shader
  hr = gDie_Device.pDie_Device->CreateVertexShader(pVertexShader->GetBufferPointer(), pVertexShader->GetBufferSize(), NULL, &VertexShader);
  if (FAILED(hr))
  {
    pVertexShader->Release();
  }
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
  float ClearColor[4] = { 0.0f, 255.0f, 255.0f, 1.0f }; //red,green,blue,alpha

  ID3D11RenderTargetView* pRenderTargetView = reinterpret_cast<ID3D11RenderTargetView*> (gDie_RenderTargetView.GetObject());

  (*pDeviceContext)->ClearRenderTargetView(pRenderTargetView, ClearColor);
  (*pDeviceContext)->IASetVertexBuffers(0, 1, &pVertexB, &stride, 0);
  (*pDeviceContext)->IASetIndexBuffer(pIndexB, DXGI_FORMAT_R32_UINT, 0);
  (*pDeviceContext)->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  (*pDeviceContext)->VSSetShader(pVertexShader, 0, 0);
 
  (*pSwapChain)->Present(0, 0);
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
