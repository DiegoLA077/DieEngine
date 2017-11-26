#include "DieBufferIndex.h"
#include <d3d11.h>
namespace dieEngineSDK 
{
  struct BufferDX
  {
    ID3D11Buffer* m_IndexBuffer;
    void Destroy() { if (m_IndexBuffer != nullptr)m_IndexBuffer->Release(); }
  };
  DieIndexBuffer::DieIndexBuffer()
  {
    m_pIndexBuffer = nullptr;
    m_pIndexBuffer = new BufferDX();
  }
  void DieIndexBuffer::Destroy()
  {
    if (m_pIndexBuffer != nullptr)
    {
      m_pIndexBuffer->Destroy();
      delete m_pIndexBuffer;
      m_pIndexBuffer = nullptr;
    }
  }
  void DieIndexBuffer::CreateHardwareBuffer(DieDevice* pDevice, const std::vector<unsigned int>& Indexes)
  {
    ID3D11Device* pD = reinterpret_cast<ID3D11Device*>(pDevice->GetDevice());

    D3D11_BUFFER_DESC indexBufferDesc;
    memset(&indexBufferDesc, 0, sizeof(D3D11_BUFFER_DESC));
    indexBufferDesc.ByteWidth = sizeof(unsigned int) * Indexes.size();
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
    indexBufferDesc.StructureByteStride = 0;
    /************************************************************************/
    D3D11_SUBRESOURCE_DATA scrData;
    scrData.pSysMem = &Indexes[0];
    scrData.SysMemPitch = 0;
    scrData.SysMemSlicePitch = 0;
    HRESULT result = pD->CreateBuffer(&indexBufferDesc, &scrData, &m_pIndexBuffer->m_IndexBuffer);
    if (FAILED(result))
    {
      return;
    }
  }
  
  void DieIndexBuffer::SetHardwareBuffer(DieDeviceContext* pDeviceContext)
  {
    ID3D11DeviceContext* pDC = reinterpret_cast<ID3D11DeviceContext*>(pDeviceContext->GetDeviceContext());
    /// Seteamos el buffer de indices.
    pDC->IASetIndexBuffer(
      m_pIndexBuffer->m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
  }
}