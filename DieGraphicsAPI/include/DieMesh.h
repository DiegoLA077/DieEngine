#pragma once
#include "DiePrerequisitesGraphics.h"
#include "DieBufferIndex.h"
#include "DieBufferVertex.h"
#include <VERTEX.h>

namespace dieEngineSDK
{

  class DIE_GRAPHICS_EXPORT DieMesh
  {
  public:
    DieMesh();
    ~DieMesh();
  public:
    DieIndexBuffer  m_Index;
    DieVertexBuffer m_Vertex;
  public:
    std::vector<VERTEX> m_VertexList;
    std::vector<unsigned int> m_IndexList;


  };
}