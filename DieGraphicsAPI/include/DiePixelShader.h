#pragma once
#include "DieShader.h"

namespace dieEngineSDK
{
  class DIE_GRAPHICS_EXPORT DiePixelShader : public DieShader
  {
  public:
    /**
    *
    */
    DiePixelShader() : DieShader(), m_pIPixelShader(nullptr) {}

    /**
    *
    */
    virtual~DiePixelShader() {}

    /**
    * @brief Funcion Create : Crea el pixel shader 
    * @param DieDevice : Puntero Device
    * @param String : Cadena constante del archivo
    * @param String : Cadena constante del entrypoint
    * @return void
    */
    void Create(DieDevice* Device, const String& fileName, const String& entryPoint);

    /**
    *
    */
    ID3D11PixelShader* m_pIPixelShader;
  };
}
