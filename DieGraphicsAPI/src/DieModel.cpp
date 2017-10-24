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

    std::vector<float> listaVertices;
    if (scene->HasMeshes())
    {
      for (int i = 0; i < scene->mNumMeshes; ++i)
      {
        aiMesh* pMesh = scene->mMeshes[i];

        listaVertices.resize(pMesh->mNumVertices * 3);
        for (int j = 0; j < pMesh->mNumVertices; ++j)
        {
          if (pMesh->HasPositions())
          {
            listaVertices[j * 3 + 0] = pMesh->mVertices[j].x;
            listaVertices[j * 3 + 1] = pMesh->mVertices[j].y;
            listaVertices[j * 3 + 2] = pMesh->mVertices[j].z;
          }
          if (pMesh->HasNormals())
          {

          }
          if (pMesh->GetNumUVChannels())
          {
            if (pMesh->HasTextureCoords(0))
            {
              //u = pMesh->mTextureCoords[0][j].x;
              //v = pMesh->mTextureCoords[0][j].y;
            }
          }
        }

        if (pMesh->HasFaces())
        {
          std::vector<int> indicesArray;
          for (int k = 0; k < pMesh->mNumFaces; ++k)
          {
            aiFace& face = pMesh->mFaces[k];
            for (int kk = 0; kk < face.mNumIndices; ++kk)
            {
              indicesArray.push_back(face.mIndices[kk]);
            }
          }
        }

        int kkk = 0;
      }
    }
    
  }
}
