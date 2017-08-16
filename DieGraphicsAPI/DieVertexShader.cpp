#include "DieVertexShader.h"
#include <d3dcompiler.h>
#include "DieDevice.h"


namespace dieEngineSDK
{
DieVertextShader::DieVertextShader() : m_pVertecShader(nullptr)
  {

  }

DieVertextShader::~DieVertextShader()
  {

  }


  void DieVertextShader::create(std::string prmFileName, std::string prmEntryPoint)
  {

    /************************************************************************/
    std::string fileName = "ShaderTest.hlsl";
    std::ifstream myFileStream(fileName, std::ios::binary & std::ios::ate);

    unsigned int fileLeght = myFileStream.tellg();
    myFileStream.seekg(std::fstream::beg);

    std::vector<char> pBuffer(fileLeght);
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
    hr = D3DCompile(fileName.c_str(), fileName.size(), prmFileName.c_str(), NULL, NULL,
      prmEntryPoint.c_str(), 0, NULL, NULL, &pErrorBlob, NULL);
    if (FAILED(hr))
    {
      if (pErrorBlob != NULL)
        OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
      if (pErrorBlob) pErrorBlob->Release();
    }
    if (pErrorBlob) pErrorBlob->Release();

    // Create the vertex shader
    hr = pDie_Device->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_pVertexShader);
    if (FAILED(hr))
    {
      pVSBlob->Release();
    }
  }

  void DieVertextShader::destroy()
  {

  }
}
