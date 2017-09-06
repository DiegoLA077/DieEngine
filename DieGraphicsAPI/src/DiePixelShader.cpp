#include "DiePixelShader.h"
#include "DieDevice.h"

#include <d3d11.h>

namespace dieEngineSDK
{

  void DiePixelShader::Create(DieDevice* pDevice, const String& fileName, const String& entryPoint)
  {
    Compile(fileName, entryPoint, "ps_5_0");

    //Create the vertex shader
    HRESULT hr = pDevice->pDie_Device->CreatePixelShader(m_pBlob->GetBufferPointer(), 
                                                         m_pBlob->GetBufferSize(), 
                                                         NULL, 
                                                         &m_pIPixelShader);
  }
}