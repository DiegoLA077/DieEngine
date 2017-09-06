#include "DieShader.h"

#include <fstream>

#include <d3d11.h>
#include <d3dcompiler.h>

namespace dieEngineSDK {
  using std::ifstream; 
  using std::ios;

  void DieShader::Compile(const String& fileName, const String& entryPoint, const String& targetStr)
  {
    ID3DBlob* pErrorBlob = nullptr;

    unsigned int compileFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if DEBUG_MODE == 1
    compileFlags |= D3DCOMPILE_DEBUG;
#endif

    //Carga el código del archivo especificado
    ifstream myFileShaderStream;
    myFileShaderStream.open(fileName, ios::in | ios::ate);
    if (!myFileShaderStream.is_open())
    {
      //Manda el error, el archivo no se abrió
      return;
    }
    size_t fileLeghtShader = myFileShaderStream.tellg();
    myFileShaderStream.seekg(0, ios::beg);
    String pFileData(fileLeghtShader+1, '\0');
    myFileShaderStream.read(&pFileData[0], fileLeghtShader);
    myFileShaderStream.close();

    HRESULT hr = D3DCompile(pFileData.c_str(),  //Source code
      pFileData.size(),                         //Size of source code
      fileName.c_str(),                         //Source Name
      NULL,                                     //Defines
      NULL,                                     //Includes
      entryPoint.c_str(),                       //Entry point
      targetStr.c_str(),                        //Target String
      compileFlags,                             //Compile flags
      0,                                        //More flags
      &m_pBlob,                                 //Out shader Blob
      &pErrorBlob);                             //Out Error Blob

    if (FAILED(hr))
    {
      if (pErrorBlob != NULL)
      {
        OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
        pErrorBlob->Release();
        return; //No continuamos con la ejecución de esta función
      }
    }
    
    if (pErrorBlob != NULL)
    {
      pErrorBlob->Release();
    }



  }
}
