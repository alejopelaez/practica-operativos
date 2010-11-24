#include <cstdio>
#include <dirent.h>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>

using std::vector;

namespace SO{
    //Valores iniciales
    int lastu = 0,lastn = 0,lasts = 0,lasti = 0;

    int *GetProcessList(int *nroProcesos){
        vector<int> ans;
        DIR *dir = NULL;
        dir = opendir("/proc");
        struct dirent *pent = NULL;

        //Hubo un error abriendo el dierctorio
        if(dir == NULL){
            return NULL;
        }
        else{
            int tmp;
            while(pent = readdir(dir)){
                tmp = atoi(pent->d_name);
                if(tmp > 0)
                    ans.push_back(tmp);
            }
            *nroProcesos = (int)ans.size();
            int *ret = new int[*nroProcesos];
            memcpy(ret, &ans[0], sizeof(int)*(*nroProcesos));
            return ret;
        }
    }

    float CpuUsage(){
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

            //Esto solo pasa si se llama muy seguido, y por lo tanto no
            //se pudo captar utilización de cpu.
            if(dtotal == 0)
                return 0.0;

            int dusage = du+dn+ds;
            lastu = u, lasts = s, lastn = n, lasti = i;
            return ((float)dusage)/((float)dtotal);
        }        
    }
}
