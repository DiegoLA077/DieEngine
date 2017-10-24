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
    *  @brief Funcion constructor buffer.
    */
    DieVertexBuffer();

    /**
    *  @brief Funcion destructor buffer manda llamar funcion destroy.
    */
    ~DieVertexBuffer() { Destroy(); };

    /**
    *  @brief variable miembro contiene el buffer.
    */
    BufferDX* m_pBuffer;

    /**
    *  @brief Funcion crear el buffer.
    *  @param DieDevice pDevice: El dispositivo a utilizar.
    *  @param std::vector<VERTEX> Vertex: Vertices.
    *  @return void
    */
    void CreateHardwareBuffer(DieDevice* pDevice, std::vector<VERTEX>& Vertex);
    
    /**
    *  @brief Funcion set el buffer.
    *  @param DieDeviceContext pDeviceContext: El dispositivo a utilizar.
    *  @return void
    */
    void SetHardwareBuffer(DieDeviceContext* pDeviceContext);
    
    /**
    *  @brief Funcion destruye el buffer.
    *  @return void
    */
    void Destroy();
  };
}
