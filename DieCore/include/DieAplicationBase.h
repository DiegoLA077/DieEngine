#pragma once

#include "DiePrerequisitesCore.h"
#include "DiePlatformTypes.h"
#include <DieAplicationBase.h>

namespace dieEngineSDK {
    class DIE_CORE_EXPORT DieAplicationBase {
  
     public:
       /**
       * @brief Constructor DieAplicationBase :  Aplicacion Base.
       */
      DieAplicationBase();

      /**
      * @brief Destrctor DieAplicationBas : Aplicacion Base.
      */
      virtual ~DieAplicationBase();

     public:

       /**
       * @brief Funcion run: corre todo el programa.
       * @return entero : 
       */
      int run();

      /**
      * @brief Funcion getScreenHandle : 
      * @return entero : handle de la pantalla.
      */
      int gerScreenHandle() { return m_screenHadle; }

     protected:

       /**
       * @brief Variable m_iScrWid : Largo de la ventana 
       */
      int m_iScrWidth;

      /**
      * @brief Variable m_iScrHeight : Ancho de la ventana
      */
      int m_iScrHeight;

      /**
      * @brief Cadena m_szTitle : Titulo de la ventana
      */
      String m_szTitle; 

     protected:

       /**
       * @brief Variable m_screenHandle : Handle de la ventana
       */
       int m_screenHadle;
    };
}