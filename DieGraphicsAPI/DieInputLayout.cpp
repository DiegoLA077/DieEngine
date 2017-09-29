#include "DieInputLayout.h"

DieInputLayout::DieInputLayout()
{
  m_d3dInputLayout = nullptr;
}

DieInputLayout::~DieInputLayout()
{
  m_Layout.clear();
  if (nullptr != m_d3dInputLayout)
  {
    m_d3dInputLayout->Release();
    m_d3dInputLayout = nullptr;
  }
}

//void DieInputLayout::addInputElement(String semanticName,
//  unsigned int semanticIndex, DXGI_FORMAT format,
//  unsigned int inputSlot, unsigned int alignedByteOffset,
//  D3D11_INPUT_CLASSIFICATION inputSlotClass,
//  unsigned int instanceDataStepRate)
//{
//  D3D11_INPUT_ELEMENT_DESC desc;
//
//char* nSmName = new char[semanticName.size() + 1];
//srtcpy(nSmName, semanticName.c_srt());
//
//desc.SemanticName = semanticName.c_str();
//desc.SemanticIndex = semanticIndex;
//desc.Format = format;
//desc.InputSlot = inputSlot;
//desc.AlignedByteOffset = alignedByteOffset;
//desc.InputSlotClass = inputSlotClass;
//desc.InstanceDataStepRate = instanceDataStepRate;
//
//m_Layout.push_back(desc);
//}

bool DieInputLayout::CreatHardwareLayout(ID3D11Device* pDevice, ID3DBlob* pVSBlob)
{
  if (nullptr == pDevice || 0 == m_Layout.size())
  {
    return false;
  }

  HRESULT hr = pDevice->CreateInputLayout(&m_Layout[0], 
                                           m_Layout.size(), 
                                           pVSBlob->GetBufferPointer(), 
                                           pVSBlob->GetBufferSize(), 
                                          &m_d3dInputLayout);
  if (FAILED(hr))
  {
    return false;
  }

  return hr;
}

void DieInputLayout::SetHardwareLayout(ID3D11DeviceContext * pDeviceContext)
{
  if (nullptr == m_d3dInputLayout)
  {
    return;
  }
  pDeviceContext->IASetInputLayout(m_d3dInputLayout);
}
