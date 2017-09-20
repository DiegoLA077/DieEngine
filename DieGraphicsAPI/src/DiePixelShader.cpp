#include "DiePixelShader.h"
#include <fstream>

namespace dieEngineSDK
{
  using std::ifstream;
  using std::ios;
  void DiePixelShader::Create(DieDevice* Device, const String& fileName, const String& entryPoint)
  {
    ID3D11Device* pDevice = reinterpret_cast<ID3D11Device*>(Device->GetDevice());
    Compile(fileName, entryPoint, "ps_5_0");
    //Create the vertex shader
    HRESULT hr = pDevice->CreatePixelShader(m_pBlob->GetBufferPointer(),
      m_pBlob->GetBufferSize(),
      NULL,
      &m_pIPixelShader);
    m_pBlob->Release();
  }

 
}