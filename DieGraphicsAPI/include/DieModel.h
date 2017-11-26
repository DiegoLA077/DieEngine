#pragma once
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <vector>
#include <DiePrerequisitesGraphics.h>
#include "DiePrerequisites.h"
#include "DieMesh.h"
#include "DieDevice.h"
#include "DieBufferIndex.h"
#include "DieBufferVertex.h"
#include <d3d11.h>
namespace dieEngineSDK
{
  class DIE_GRAPHICS_EXPORT DieModel
  {
  public:
    std::vector<DieMesh*> m_MeshList;
  public:
    DieModel();
    ~DieModel();
  public:
    void loadModel(const String& fileName);
    void CreateIndexBuffer(DieDevice* device);
    void CreateVertexBuffer(DieDevice* device);
  };
}