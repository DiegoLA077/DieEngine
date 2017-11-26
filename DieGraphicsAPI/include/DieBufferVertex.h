/**
* @file DieBufferVertex.h
* @version 1.0v
* @date 11/9/17
* @author Diego Larios Arellano
*/
#pragma once
#include "DieDevice.h"
#include "DieDeviceContext.h"
#include <vector>
#include "VERTEX.h"
namespace dieEngineSDK
{
  struct BufferDX;
  class DIE_GRAPHICS_EXPORT DieVertexBuffer
  {
  public:

    /**
    *  @brief Funcion DieVertexBuffer : Constructor buffer de vertices.
    */
    DieVertexBuffer();

    /**
    *  @brief Destructor DieVertexBuffer : Llama Destroy.
    */
    ~DieVertexBuffer() { Destroy(); };

    /**
    *  @brief variable m_ pBuffer : Contiene el buffer.
    */
    BufferDX* m_pBuffer;

    /**
    *  @brief Funcion CreateHardwareBuffer : Crear un buffer de vertices.
    *  @param DieDevice pDevice : El dispositivo a utilizar.
    *  @param std::vector<VERTEX> Vertex: Vertices.
    *  @return void.
    */
    void CreateHardwareBuffer(DieDevice* pDevice, std::vector<VERTEX>& Vertex);
    
    /**
    *  @brief Funcion SetHardwareBuffer : Prepara el buffer.
    *  @param DieDeviceContext pDeviceContext : El dispositivo a utilizar.
    *  @return void.
    */
    void SetHardwareBuffer(DieDeviceContext* pDeviceContext);
    
    /**
    *  @brief Funcion Destroy : Destruye el buffer.
    *  @return void.
    */
    void Destroy();
  };
}
