#pragma once
#include "DieDevice.h"
#include "DieDeviceContext.h"
#include <vector>
namespace dieEngineSDK
{
  struct BufferDX;
  class DIE_GRAPHICS_EXPORT DieIndexBuffer
  {
  public:

    /**
    *	@brief Constructor IndexBuffer.
    */
    DieIndexBuffer();

    /**
    *	@brief Destructor IndexBuffer destruye el buffer.
    */
    ~DieIndexBuffer() { Destroy(); };

  public:
    /**
    *	@brief Variable contiene buffer de indices.
    */
    BufferDX* m_pIndexBuffer;

  public:
    /**
    *	@brief Funcion para destruir el buffer.
    *	@return void.
    */    
    void Destroy();

    /**
     *	@brief Funcion CreateBuffer: crea un buffer de indices.
     *	@param DieDevice Device: Dispositivo de hardware a utilizar.
     *  @param std::vector<unsigned int>& Index: Indices.
     *  @return void.
     */
    void CreateHardwareBuffer(DieDevice* pDevice, unsigned int* Index);
    
    /**
     *	@brief Funcion SetBuffer: setea un buffer de indices.
     *	@param void* pDeviceContext: DeviceContext para setear el buffer constante.
     *  @return void.
     */
    void SetHardwareBuffer(DieDeviceContext* pDeviceContext);

  };
}