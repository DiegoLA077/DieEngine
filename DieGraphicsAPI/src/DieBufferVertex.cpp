#include "DieBufferVertex.h"
#include <d3d11.h>
//#include <Windows.h>

namespace dieEngineSDK
{
  struct BufferDX
  {
    ID3D11Buffer* m_VertexBuffer;
    void Destroy() { if (m_VertexBuffer != nullptr)m_VertexBuffer->Release(); }
  };
  DieVertexBuffer::DieVertexBuffer()
  {
    m_pBuffer = nullptr;
    m_pBuffer = new BufferDX();
  }
  void DieVertexBuffer::Destroy()
  {
    if (m_pBuffer != nullptr)
    {
      m_pBuffer->Destroy();
      delete m_pBuffer;
      m_pBuffer = nullptr;
    }
  }
  void DieVertexBuffer::CreateHardwareBuffer(DieDevice* pDevice, std::vector<VERTEX>& Vertex)
  {

    ID3D11Device* pD = reinterpret_cast<ID3D11Device*>(pDevice->GetDevice());
    D3D11_BUFFER_DESC vertexBufferDesc;
    ZeroMemory(&vertexBufferDesc, sizeof(D3D11_BUFFER_DESC));
    vertexBufferDesc.ByteWidth = sizeof(VERTEX) * Vertex.size();
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
    vertexBufferDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA srData;
    srData.pSysMem = &Vertex[0];
    srData.SysMemPitch = 0;
    srData.SysMemSlicePitch = 0;

    HRESULT result = pD->CreateBuffer(&vertexBufferDesc, &srData, &m_pBuffer->m_VertexBuffer);

  }
  void DieVertexBuffer::SetHardwareBuffer(DieDeviceContext* DeviceContext)
  {
    ID3D11DeviceContext* pDC = reinterpret_cast<ID3D11DeviceContext*>(DeviceContext->GetDeviceContext());
    // Set vertex buffer
    UINT stride = sizeof(VERTEX);
    UINT offsetcopy = 0;
    pDC->IASetVertexBuffers(0, 1, &m_pBuffer->m_VertexBuffer, &stride, &offsetcopy);
  }
}