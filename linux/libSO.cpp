#ifndef _CSTDIO
#define _CSTDIO 1
#include <stdio.h>
#endif

#ifndef _DIRENT_
#define _DIRENT_ 1
#include <dirent.h>
#endif

/*#ifndef _VECTOR_
#define _VECTOR_ 1
#include <vector>
#endif

#ifndef _C_STRING_
#define _C_STRING_ 1
#include <string.h>
#endif*/

#ifndef _STD_LIB_
#define _STD_LIB_ 1
#include <stdlib.h>
#endif

#ifndef _UNISTD_
#define _UNISTD_ 1
#include <unistd.h>
#endif

#ifdef __cplusplus
    extern "C" {
#endif

        //using std::vector;


  int *GetProcessList(int *nroProcesos){
      //vector<int> ans;
      int all[2000];
    DIR *dir = NULL;
    dir = opendir("/proc");
    struct dirent *pent = NULL;

    //Hubo un error abriendo el dierctorio
    if(dir == NULL){
      return NULL;
    }
    else{
      int tmp;
      int count = 0;
      int j = 0;
      while(pent = readdir(dir)){
        tmp = atoi(pent->d_name);
        all[j] = tmp;
        j++;
        if(tmp > 0)count++;
        //          ans.push_back(tmp);
      }
      closedir(dir);      
      
      //      *nroProcesos = (int)ans.size();
      *nroProcesos = count;
      int c = 0;
      int *ret = new int[*nroProcesos];
      for(int i = 0; i <= j; ++i){
          if(all[i] > 0){
              ret[c] = all[i];
              c++;
          }
      }
      return ret;
    }
  }

  float CpuUsage(){
    //Valores iniciales
    static int lastu = 0,lastn = 0,lasts = 0,lasti = 0;
    FILE *file = NULL;
    file = fopen("/proc/stat","r");
    char buffer[100];

        //Hubo un error
    if(file == NULL){
      return -1.0;
    }
    else{
      int u,n,s,i;
      fgets (buffer, 100, file);         
      sscanf(buffer,"cpu  %d %d %d %d",&u,&n,&s,&i);
      fclose (file);
      int du = u-lastu;
      int dn = n-lastn;
      int ds = s-lasts;
      int di = i-lasti;
      int dtotal = du+dn+ds+di;

      // Esto solo pasa si se llama muy seguido, y por lo tanto no
      // se pudo captar utilización de cpu.
      if(dtotal == 0)
        return 0.0;

      int dusage = du+dn+ds;
      lastu = u, lasts = s, lastn = n, lasti = i;
      return ((float)dusage)/((float)dtotal);
    }        
  }


#ifdef __cplusplus
    }
#endif
