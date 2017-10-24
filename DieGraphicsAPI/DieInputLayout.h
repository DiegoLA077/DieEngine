#pragma once
#include <d3d11.h>
#include <vector>
#include <DiePrerequisitesGraphics.h>

using std::vector;

class DieInputLayout
{
public:
  /**
  * @brief Constructor de DieInputLayout
  */
  DieInputLayout();

  /**
  * @brief Destructor de DieInputLayout
  */
  ~DieInputLayout();

  /**
  * @brief Funcion addInputElement : Agrega un elemento que sea al input layout
  * @param String semanticName : Nombre del elemento agregado
  * @param Unsigned int semanticIndex : 
  * @param DXGI_FORMAT format :
  * @param Unsigned int inputSlot : 
  * @param Unsigned int alingnesByteOffset :
  * @param D3D11_INPUT_CLASSIFICATION inputSlotClass :
  * @param unsigned int instanceDataStepRate :
  */

  //void addInputElement( String semanticName,
  //                       unsigned int semanticIndex,
  //                       DXGI_FORMAT format,
  //                       unsigned int inputSlot,
  //                       unsigned int alignedByteOffset,
  //                       D3D11_INPUT_CLASSIFICATION inputSlotClass,
  //                       unsigned int instanceDataStepRate);

  /**
  * @brief Funcion CreatHardwareLayout : Crea el layout en hardware
  * @param ID3D11Device : Puntero Device 
  * @param ID3DBlob : Puntero Vertex Shader Blob
  * @return bool : 
  */
  bool CreatHardwareLayout(ID3D11Device* pDevice, ID3DBlob* pVSBlob);

  /**
  * @brief Funcion SetHardwareLayout : Setea el layout
  * @param ID3D11DeviceContext : Puntero Device Context
  * @return void
  */
  void SetHardwareLayout(ID3D11DeviceContext*  pDeviceContext);

  vector<D3D11_INPUT_ELEMENT_DESC> m_Layout;
  ID3D11InputLayout* m_d3dInputLayout;
};