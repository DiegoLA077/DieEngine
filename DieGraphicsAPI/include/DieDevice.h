#pragma once

#include "DiePrerequisitesGraphics.h"

namespace dieEngineSDK {

  struct DeviceDX;
  class DIE_GRAPHICS_EXPORT DieDevice
  {

  public:

    /**
    * @brief Constructor Device.
    */
    DieDevice();

    /**
    * @brief Destructor Device.
    */
    ~DieDevice();

    /**
    * @brief Variable contiene el device.
    */
    DeviceDX* m_pDevice;

    /**
    * @brief Funcion Create: crea un device.
    * @return void.
    */
    void Create();

    /**
    * @brief Funcion Destroy: destruye el device.
    * @return void.
    */
    void Destroy();

    /**
    * @brief Funcion GetDevice: 
    * @return void puntero.
    */
    void* GetDevice();

    /**
    * @brief Funcion GetReference: 
    * @return void puntero puntero.
    */
    void** GetReference();
  };
}
