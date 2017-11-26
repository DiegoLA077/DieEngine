#include "DieModel.h"

namespace dieEngineSDK
{
  DieModel::DieModel()
  {

  }
  DieModel::~DieModel()
  {

  }

  void DieModel::loadModel(const String& fileName)
  {
    //Create an instance of the Importer class
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(fileName,
      aiProcess_CalcTangentSpace |
      aiProcess_Triangulate |
      aiProcess_JoinIdenticalVertices |
      aiProcess_SortByPType);

    // If the import failed, report it
    if (!scene)
    {
      String error(importer.GetErrorString());
      return;
    }

    DieMesh* tempMesh = nullptr;
    VERTEX pTempVector;

    if (scene->HasMeshes())
    {
      for (int i = 0; i < scene->mNumMeshes; ++i)
      {
        tempMesh = new DieMesh();
        m_MeshList.push_back(tempMesh);
        aiMesh* pMesh = scene->mMeshes[i];

        for (int j = 0; j < pMesh->mNumVertices; ++j)
        {
          if (pMesh->HasPositions())
          {
            pTempVector.m_Pos.x = pMesh->mVertices[j].x;
            pTempVector.m_Pos.y = pMesh->mVertices[j].y;
            pTempVector.m_Pos.z = pMesh->mVertices[j].z;

            m_MeshList[i]->m_VertexList.push_back(pTempVector);

          }
          if (pMesh->HasFaces())
          {
            for (int k = 0; k < pMesh->mNumFaces; ++k)
            {
              aiFace& face = pMesh->mFaces[k];
              for (int kk = 0; kk < face.mNumIndices; ++kk)
              {
                m_MeshList[i]->m_IndexList.push_back(face.mIndices[kk]);
              }
            }
          }

        }

      }

    }

  }
  void DieModel::CreateVertexBuffer(DieDevice* device)
  {
    for (int i = 0; i < m_MeshList.size(); ++i)
    {
      m_MeshList[i]->m_Vertex.CreateHardwareBuffer(device, m_MeshList[i]->m_VertexList);
    }
  }
  void DieModel::CreateIndexBuffer(DieDevice* device)
  {
    for (int i = 0; i < m_MeshList.size(); ++i)
    {
      m_MeshList[i]->m_Index.CreateHardwareBuffer(device, m_MeshList[i]->m_IndexList);
    }
  }

  
}
