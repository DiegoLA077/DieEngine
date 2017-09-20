#include "DieVertexShader.h"
namespace dieEngineSDK
{
  
  void DieVertexShader::Create(DieDevice* Device, const String& fileName, const String& entryPoint)
  {
    ID3D11Device* pDevice = reinterpret_cast<ID3D11Device*>(Device->GetDevice());
    Compile(fileName, entryPoint, "vs_5_0");
    //Create the vertex shader
    HRESULT hr = pDevice->CreateVertexShader(m_pBlob->GetBufferPointer(),
                                                          m_pBlob->GetBufferSize(),
                                                          NULL,
                                                          &m_pIVertexShader);
  }
}