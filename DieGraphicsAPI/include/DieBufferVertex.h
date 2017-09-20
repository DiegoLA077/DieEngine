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
    DieVertexBuffer();
    ~DieVertexBuffer() { Destroy(); };
    BufferDX* m_pBuffer;
    /*void Add(T nIndex);
    void Add(const std::vector<T>& nIndexArray);
    void Add(T* pArray, unsigned int nNumObjects);

    void Remove(unsigned int nIndex, unsigned int count = 1);
    void Clear();*/

    void CreateHardwareBuffer(DieDevice* pDevice, std::vector<VERTEX>& Vertex);
    void SetHardwareBuffer(DieDeviceContext* pDeviceContext);
    void Destroy();
  };

  //template<typename T>
  //void DieVertexBuffer<T>::Add(T nVertex)
  //{
  //  m_vertexArray.push_back(nVertex);
  //}
  //
  //template<typename T>
  //void DieVertexBuffer<T>::Add(const std::vector<T>& nVertexArray)
  //{
  //  Add(&nVertexArray[0], nVertexArray.size());
  //}
  //
  //template<typename T>
  //void DieVertexBuffer<T>::Add(T * pArray, unsigned int nNumObjects)
  //{
  //  for (unsigned int i = 0; i < nNumObjects; ++i) {
  //    m_vertexArray.push_back(pArray[i]);
  //  }
  //}
  //
  //template<typename T>
  //void DieVertexBuffer<T>::Remove(unsigned int nvertex, unsigned int count)
  //{
  //  m_vertexArray.erase(m_vertexArray.begin() + nvertex,
  //    (m_vertexArray.begin() + nvertex) + (count - 1));
  //}
  //
  //template<typename T>
  //void DieVertexBuffer<T>::Clear()
  //{
  //  m_vertexArray.clear();
  //}

  /**
  *  @brief esta funcion crea el buffer.
  *  @param DieDevice Device: El dispositivo a utilizar.
  *  @param int usageFags: fsdfaasf.
  */
  

}
