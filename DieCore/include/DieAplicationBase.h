#pragma once

#include "DiePrerequisitesCore.h"
#include "DiePlatformTypes.h"
#include <DieAplicationBase.h>

namespace dieEngineSDK {
    class DIE_CORE_EXPORT DieAplicationBase {
      //constructor / destructor
     public:
      DieAplicationBase();
      virtual ~DieAplicationBase();

      //Funciones
     public:
      int run();

      //Accesores
      int gerScreenHandle() { return m_screenHadle; }

      //Variables
     protected:
      int m_iScrWidth;
      int m_iScrHeight;

      String m_szTitle; //Titulo de la ventana

     protected:
       int m_screenHadle;
    };
}