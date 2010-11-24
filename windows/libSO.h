#ifndef LIBSO_DLL_H_
#define LIBSO_DLL_H_

#if BUILDING_DLL
# define DLLIMPORT __declspec (dllexport)
#else
# define DLLIMPORT __declspec (dllimport)
#endif

namespace SO{
    DLLIMPORT int *GetProcessList(int *nroProcesos);
    DLLIMPORT float GetCpuUsage();
}

#endif /* LIBSO_DLL_H_ */
