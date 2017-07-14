#pragma once
#include "DiePrerequisitesGraphics.h"
#include "vector"

namespace dieEngineSDK {

  namespace BUFFER_USAGE_FLAGS {
    enum E {
      kDEFAULT = 0x00,
      KDYNAMIC = 0x01
    };
  }

  class DIE_GRAPHICS_EXPORT DieBufferBase
  {
  public:
    DieBufferBase();
    virtual ~DieBufferBase();

  protected:
    ID3D11Buffer* pDie_BufferBase;

    
  };

  template<typename T>
  class DIE_GRAPHICS_EXPORT DieIndexBuffer : public DieBufferBase
  {
  public:
    DieIndexBuffer();
    ~DieIndexBuffer();

  void Add(T nIndex);
  void Add(const std::vector<T>& nIndexArray);
  void Add(T* pArray, unsigned int nNumObjects);

  void Remove(unsigned int nIndex, unsigned int count = 1);
  void Clear();

  void CreateHardwareBuffer(int usageFlags = BUFFER_USAGE_FLAGS::kDEFAULT);

    private:
    std::vector<T> m_indexArray;
  };
}