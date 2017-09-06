#include "DieVertexShader.h"
#include "DieDevice.h"

#include <d3d11.h>

namespace dieEngineSDK
{
  
  void DieVertexShader::Create(DieDevice* pDevice, const String& fileName, const String& entryPoint)
  {
    Compile(fileName, entryPoint, "vs_5_0");

    //Create the vertex shader
    HRESULT hr = pDevice->pDie_Device->CreateVertexShader(m_pBlob->GetBufferPointer(),
                                                          m_pBlob->GetBufferSize(),
                                                          NULL,
                                                          &m_pIVertexShader);
  }
}