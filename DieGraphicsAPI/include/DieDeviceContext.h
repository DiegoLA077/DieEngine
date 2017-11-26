#pragma once

#include "DiePrerequisitesGraphics.h"

namespace dieEngineSDK {

  struct DeviceContextDX;
  class DIE_GRAPHICS_EXPORT DieDeviceContext
  {
 
  public:
    /**
    * @brief Constructor del device context 
    */
    DieDeviceContext();

    /**
    * @brief Destructor del device context
    */
    ~DieDeviceContext();

  public:
    /**
    * @brief Variable m_DeviceContext : Contiene el device context de directx.
    */
    DeviceContextDX* m_DeviceContext;

  public:
    /**
    * @brief Funcion Create : Crea un device context.
    * @return void.
    */
    void Create();

    /**
    * @brief Funcion Destroy : Destruye el device context.
    * @return void.
    */
    void Destroy();

    /**
    * @brief Funcion GetDeviceContext :
    * @return void puntero.
    */
    void* GetDeviceContext();

    /**
    * @brief Funcion GetReference :
    * @return void puntero puntero.
    */
    void** GetReference();
    
  };
}