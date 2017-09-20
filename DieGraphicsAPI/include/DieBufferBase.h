#pragma once
#include "DiePrerequisitesGraphics.h"
#include "DieDevice.h"
#include "DieGaphicsAPI.h"
#include "vector"

namespace dieEngineSDK
{
  class DieDeviceContext;
  class DieDevice;
  namespace BUFFER_USAGE_FLAGS 
  {
    enum E
    {
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
}

