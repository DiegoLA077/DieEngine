#include "DieMesh.h"

namespace dieEngineSDK
{
  DieMesh::DieMesh()
  {
    m_IndexList.clear();
    m_VertexList.clear();
  }

  DieMesh:: ~DieMesh()
  {
    if (m_VertexList.size() != 0)
    {
      m_VertexList.clear();
    }
    m_IndexList.clear();
  }
}
