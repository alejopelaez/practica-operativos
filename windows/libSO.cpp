#define _WIN32_WINNT 0x0501
#ifdef BUILDING_DLL
    #define DLLIMPORT __declspec (dllexport)
#else
    # define DLLIMPORT __declspec (dllimport)
#endif
#include <windows.h>
#include <winbase.h>
#include <psapi.h>

#ifdef __cplusplus
    extern "C" {
#endif

namespace SO{
    ULARGE_INTEGER lasti, lastk, lastu;
    
    DLLIMPORT int *GetProcessList(int *nroProcesos){
        DWORD *processes = new DWORD[1024];
        DWORD pBytesReturned;
        EnumProcesses(processes, DWORD(1024), &pBytesReturned);
        *nroProcesos = (int)(pBytesReturned/sizeof(DWORD));
        
        //Conversión from DWORD to int
        int *ans = new int[*nroProcesos];
        for(int i = 0; i < *nroProcesos; ++i)
            ans[i] = (int)processes[i];
            
        return ans;
    }
    
    DLLIMPORT float CpuUsage(){
        FILETIME i, k, u;
        GetSystemTimes(&i, &k, &u);

        //Que horrible esto :S, mas casteos pa donde
        ULARGE_INTEGER ut, kt, it;
        ULONGLONG du, dk, di;
        ut.LowPart = u.dwLowDateTime;
        ut.HighPart = u.dwHighDateTime;
        kt.LowPart = k.dwLowDateTime;
        kt.HighPart = k.dwHighDateTime;
        it.LowPart = i.dwLowDateTime;
        it.HighPart = i.dwHighDateTime;
        
        du = ut.QuadPart-lastu.QuadPart;
        dk = kt.QuadPart-lastk.QuadPart;
        di = it.QuadPart-lasti.QuadPart;
        
        lasti = it, lastu = ut, lastk = kt;

        return float((float)(du+dk)/(float)(du+dk+di));
    }
}


BOOL APIENTRY DllMain (HINSTANCE hInst     /* Library instance handle. */ ,
                       DWORD reason        /* Reason this function is being called. */ ,
                       LPVOID reserved     /* Not used. */ )
{
    switch (reason)
    {
      case DLL_PROCESS_ATTACH:
        break;

      case DLL_PROCESS_DETACH:
        break;

      case DLL_THREAD_ATTACH:
        break;

      case DLL_THREAD_DETACH:
        break;
    }

    /* Returns TRUE on success, FALSE on failure */
    return TRUE;
}

#ifdef __cplusplus
    }
#endif
