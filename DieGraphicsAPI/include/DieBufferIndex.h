/**
* @file DieBufferIndex.h
* @version 1.0v
* @date 11/9/17
* @author Diego Larios Arellano
*/
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
    *	@brief Constructor DieIndexBuffer : Buffer de indices.
    */
    DieIndexBuffer();

    /**
    *	@brief Destructor DieIndexBuffer : Llama Destroy.
    */
    ~DieIndexBuffer() { Destroy(); };

  public:
    /**
    *	@brief Variable m_pIndexBuffer : Contiene buffer de indices.
    */
    BufferDX* m_pIndexBuffer;

  public:
    /**
    *	@brief Funcion Destroy :  Destruye el buffer.
    *	@return void.
    */    
    void Destroy();

    /**
     *	@brief Funcion CreateHardwareBuffer : Crea un buffer de indices.
     *	@param DieDevice Device : Dispositivo de hardware a utilizar.
     *  @param std::vector<unsigned int>& Index : Indices.
     *  @return void.
     */
    void CreateHardwareBuffer(DieDevice* pDevice, const std::vector<unsigned int>& Indexes);
    
    /**
     *	@brief Funcion SetHardwareBuffer : Prepara el buffer de indices.
     *	@param void* pDeviceContext : DeviceContext para setear el buffer constante.
     *  @return void.
     */
    void SetHardwareBuffer(DieDeviceContext* pDeviceContext);

  };
}