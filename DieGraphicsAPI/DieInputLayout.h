#pragma once
#include <d3d11.h>
#include <vector>
#include <DiePrerequisitesGraphics.h>

using std::vector;

class DieInputLayout
{
public:
  DieInputLayout();
  ~DieInputLayout();

  //void addInputElement( String semanticName,
  //                       unsigned int semanticIndex,
  //                       DXGI_FORMAT format,
  //                       unsigned int inputSlot,
  //                       unsigned int alignedByteOffset,
  //                       D3D11_INPUT_CLASSIFICATION inputSlotClass,
  //                       unsigned int instanceDataStepRate);

  bool CreatHardwareLayout(ID3D11Device* pDevice, ID3DBlob* pVSBlob);
  void SetHardwareLayout(ID3D11DeviceContext*  pDeviceContext);

  vector<D3D11_INPUT_ELEMENT_DESC> m_Layout;
  ID3D11InputLayout* m_d3dInputLayout;
};