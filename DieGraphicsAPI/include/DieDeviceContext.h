#pragma once

#include "DiePrerequisitesGraphics.h"

namespace dieEngineSDK {

  struct DeviceContextDX;
  class DIE_GRAPHICS_EXPORT DieDeviceContext
  {
  public:
    /**
    * @brief Variable miebro DeviceContextDX m_DeviceContext: Contiene el device context
    */
    DeviceContextDX* m_DeviceContext;
    
  public:
    /**
    * @brief Constructor del device context 
    */
    DieDeviceContext();

    /**
    * @brief Destructor del device context
    */
    ~DieDeviceContext();

    /**
    * @brief Funcion Create: crea el device context.
    * @return void.
    */
    void Create();

    /**
    * @brief Funcion Destroy: destruye el device context.
    * @return void.
    */
    void Destroy();

    /**
    * @brief Funcion GetDeviceContext:
    * @return void puntero.
    */
    void* GetDeviceContext();

    /**
    * @brief Funcion GetReference:
    * @return void puntero puntero.
    */
    void** GetReference();
    
  };
}