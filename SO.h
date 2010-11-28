#ifndef LIB_SO
#define LIB_SO

#ifdef _WIN32
  #if BUILDING_DLL
    #define DLLIMPORT __declspec (dllexport)
  #else
    #define DLLIMPORT __declspec (dllimport)
  #endif
  #include <windows.h>
#else
  #define DLLIMPORT  //Un define vacío para no tener problemas
  #include <unistd.h>
#endif

#ifdef __cplusplus
    extern "C" {
#endif

namespace SO{
    /**
     * Retorna un arreglo con los pid de los procesos
     * que corren actualmente en el SO.
     * nroProcesos es la cantidad de elementos en ese arreglo.
     */
    DLLIMPORT int *GetProcessList(int *nroProcesos);

    /**
     * Retorna la fraccion de utilización de la cpu
     * desde la última llamada a esta función.
     * Si es la primera vez que se llama entonces retorna
     * la utilización desde que inicio el computador.
     */
    DLLIMPORT float CpuUsage();
}

#ifdef __cplusplus
    }
#endif

#if BUILDING_DLL
    #ifdef __cplusplus
        }
    #endif
#endif

#endif      //LIB_SO  
