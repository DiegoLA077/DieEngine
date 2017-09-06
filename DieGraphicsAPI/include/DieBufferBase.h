#pragma once
#include "DiePrerequisitesGraphics.h"
#include "DieGaphicsAPI.h"
#include "vector"

namespace dieEngineSDK {
  class DieDeviceContext;
  class DieDevice;
  namespace BUFFER_USAGE_FLAGS {
    enum E {
      kDEFAULT = 0x00,
      KDYNAMIC = 0x01
    };
  }

  class DieBufferBase
  {
  public:
    DieBufferBase() {};
    virtual ~DieBufferBase() {};

  protected:
    ID3D11Buffer* pDie_BufferBase;

    
  };

  template<typename T>
  class DieIndexBuffer : public DieBufferBase
  {
  public:
    DieIndexBuffer() {};
    ~DieIndexBuffer() {};

    void Add(T nIndex) { m_indexArray.push_back(nIndex); }
    void Add(const std::vector<T>& nIndexArray){ Add(&nIndexArray[0], nIndexArray.size()); }
    void Add(T* pArray, unsigned int nNumObjects) {
    for (unsigned int i = 0; i < nNumObjects; ++i) {
      m_indexArray.push_back(pArray[i]);
    }
  }

  void Remove(unsigned int nIndex, unsigned int count = 1) {
    m_indexArray.erase(m_indexArray.begin() + nIndex,
      (m_indexArray.begin() + nIndex) + (count - 1));
  }
  void Clear(){ m_indexArray.clear(); }

  void CreateHardwareBuffer(int usageFlags = BUFFER_USAGE_FLAGS::kDEFAULT) {
    if (!m_indexArray.size()) {
      return;
    }
    D3D11_BUFFER_DESC indexBufferDesc;
    memset(&indexBufferDesc, 0, sizeof(D3D11_BUFFER_DESC));


    if (BUFFER_USAGE_FLAGS::kDEFAULT & usageFlags) {
      indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    }

    if (BUFFER_USAGE_FLAGS::KDYNAMIC & usageFlags) {
      indexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    }

    indexBufferDesc.ByteWidth = sizeof(T) * m_indexArray.size();
    indexBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
    indexBufferDesc.StructureByteStride = 0;
    /************************************************************************/
    DieGraphicsAPI* pGraphicsAPI = g_GraphicsAPI().instancePtr();
    ID3D11Device* pDevice = reinterpret_cast<ID3D11Device*>(pGraphicsAPI->m_Device.GetObject());
    D3D11_SUBRESOURCE_DATA scrData;
    scrData.pSysMem = &m_indexArray[0];
    scrData.SysMemPitch = 0;
    scrData.SysMemSlicePitch = 0;
    HRESULT result = pDevice->CreateBuffer(&indexBufferDesc, &scrData, &pDie_BufferBase);
    if (FAILED(result))
    {
      return; 
    }
    /************************************************************************/
  }
  void SetHardwareBuffer(DieDeviceContext* pDevice, unsigned int offset) {
    ID3D11DeviceContext* pRealDC = reinterpret_cast<ID3D11DeviceContext*>(pDevice->getObject());
    pRealDC->IASetIndexBuffer(pDie_BufferBase, DXGI_FORMAT_R32_UINT, offset);
  }

    private:
    std::vector<T> m_indexArray;


  };
  /************************************************************************/
  struct DIEVERTEX
  {
    DieVector4D position;
  };

  template<typename T>
  class DieVertexBuffer : public DieBufferBase
  {
  public:
    DieVertexBuffer();
    ~DieVertexBuffer();

    void Add(T nIndex);
    void Add(const std::vector<T>& nIndexArray);
    void Add(T* pArray, unsigned int nNumObjects);

    void Remove(unsigned int nIndex, unsigned int count = 1);
    void Clear();

    void CreateHardwareBuffer(int usageFlags = BUFFER_USAGE_FLAGS::kDEFAULT);
    void SetHardwareBuffer(int Slot = 0, int offset = 0);

  private:
    std::vector<T> m_vertexArray;
  };

  template<class T>
  DieVertexBuffer<T>::DieVertexBuffer() {

  }

  template<class T>
  DieVertexBuffer<T>::~DieVertexBuffer() {

  }

  template<typename T>
  void DieVertexBuffer<T>::Add(T nVertex)
  {
    m_vertexArray.push_back(nVertex);
  }

  template<typename T>
  void DieVertexBuffer<T>::Add(const std::vector<T>& nVertexArray)
  {
    Add(&nVertexArray[0], nVertexArray.size());
  }

  template<typename T>
  void DieVertexBuffer<T>::Add(T * pArray, unsigned int nNumObjects)
  {
    for (unsigned int i = 0; i < nNumObjects; ++i) {
      m_vertexArray.push_back(pArray[i]);
    }
  }

  template<typename T>
  void DieVertexBuffer<T>::Remove(unsigned int nvertex, unsigned int count)
  {
    m_vertexArray.erase(m_vertexArray.begin() + nvertex,
      (m_vertexArray.begin() + nvertex) + (count - 1));
  }

  template<typename T>
  void DieVertexBuffer<T>::Clear()
  {
    m_vertexArray.clear();
  }

  template<typename T>
  void DieVertexBuffer<T>::CreateHardwareBuffer(int usageFags)
  {
    if (!m_vertexArray.size()) {
      return;
    }
    D3D11_BUFFER_DESC vertexBufferDesc;
    memset(&vertexBufferDesc, 0, sizeof(D3D11_BUFFER_DESC));


    if (BUFFER_USAGE_FLAGS::kDEFAULT & usageFags) {
      vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    }

    if (BUFFER_USAGE_FLAGS::KDYNAMIC & usageFags) {
      vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    }

    vertexBufferDesc.ByteWidth = sizeof(T) * m_vertexArray.size();
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
    vertexBufferDesc.StructureByteStride = 0;

    DieGraphicsAPI* pGraphicsAPI = g_GraphicsAPI().instancePtr();
    ID3D11Device* pDevice = reinterpret_cast<ID3D11Device*>(pGraphicsAPI->m_Device.GetObject());

    D3D11_SUBRESOURCE_DATA srData;
    srData.pSysMem = &m_vertexArray[0];
    srData.SysMemPitch = 0;
    srData.SysMemSlicePitch = 0;

    HRESULT result = pDevice->CreateBuffer(&vertexBufferDesc, &srData, &pDie_BufferBase);
    if (FAILED(result))
    {
      return;
    }
  }

  template<typename T>
  void DieVertexBuffer<T>::SetHardwareBuffer(int Slot, int offset)
  {
    //DieGraphicsAPI* pGraphicsAPI = g_GraphicsAPI().instancePtr();
    ID3D11DeviceContext* pDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(Slot);

    // Set vertex buffer
    UINT stride = sizeof(T);
    UINT offsetcopy = offset;
    pDeviceContext->IASetVertexBuffers(Slot, 1, &pDie_BufferBase, &stride, &offsetcopy);
  }
  /************************************************************************/

  typedef DieIndexBuffer<unsigned short> DieIndexBuffer16;
  typedef DieIndexBuffer<unsigned int> DieIndexBuffer32;

}

