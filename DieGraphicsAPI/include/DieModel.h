#pragma once
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <vector>
#include <DiePrerequisitesGraphics.h>
#include "DiePrerequisites.h"

namespace dieEngineSDK
{
  class DIE_GRAPHICS_EXPORT DieModel
  {
  public:
    /**
    * @brief Constructor DieModel
    */
    DieModel();

    /**
    * @brief Destructor DieModel
    */
    ~DieModel();

  public:
    void loadModel(const String& fileName);

  };
}