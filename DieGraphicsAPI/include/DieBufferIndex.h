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
    DieIndexBuffer();
    ~DieIndexBuffer() { Destroy(); };

    BufferDX* m_pIndexBuffer;

    /*void Add( nIndex) { m_indexArray.push_back(nIndex); }
    void Add(const std::vector<T>& nIndexArray) { Add(&nIndexArray[0], nIndexArray.size()); }
    void Add(T* pArray, unsigned int nNumObjects) {
      for (unsigned int i = 0; i < nNumObjects; ++i) {
        m_indexArray.push_back(pArray[i]);
      }
    }*/
    //
    //void Remove(unsigned int nIndex, unsigned int count = 1) {
    //  m_indexArray.erase(m_indexArray.begin() + nIndex,
    //    (m_indexArray.begin() + nIndex) + (count - 1));
    //}
    //
    //void Clear() { m_indexArray.clear(); }
    
    void Destroy();
    /**
     *	@brief Funcion para crear un buffer.
     *	@param DieDevice Device: Dispositivo de hardware a utilizar.
     *  @param std::vector<unsigned int>& Index: Indices.
     */
    void CreateHardwareBuffer(DieDevice* pDevice, unsigned int* Index);
    /**
     *	@brief Funcion para setear un buffer.
     *	@param void* pDeviceContext: DeviceContext para setear el buffer constante.
     */
    void SetHardwareBuffer(DieDeviceContext* pDeviceContext);

  };
}