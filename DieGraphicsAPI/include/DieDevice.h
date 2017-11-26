#pragma once

#include "DiePrerequisitesGraphics.h"

namespace dieEngineSDK {

  struct DeviceDX;
  class DIE_GRAPHICS_EXPORT DieDevice
  {

  public:

    /**
    *	@brief Constructor DieDevice.
    */
    DieDevice();

    /**
    * @brief Destructor DieDevice.
    */
    ~DieDevice();

    /**
    * @brief Variable m_pDevice : Contiene el device de Directx.
    */
    DeviceDX* m_pDevice;

    /**
    * @brief Funcion Create : Crea un device.
    * @return void.
    */
    void Create();

    /**
    * @brief Funcion Destroy : Destruye el device.
    * @return void.
    */
    void Destroy();

    /**
    * @brief Funcion GetDevice : 
    * @return void puntero.
    */
    void* GetDevice();

    /**
    * @brief Funcion GetReference : 
    * @return void puntero puntero.
    */
    void** GetReference();
  };
}
