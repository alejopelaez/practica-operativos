#include <cstdio>
#include "SO.h"

int main(){    
    int* processes = NULL;
    int numP = 0;
    processes = GetProcessList(&numP);
    printf("Procesos:\n");
    for(int i = 0; i < numP; ++i)
        printf("Proceso %d: %d\n",i+1,processes[i]);
        
    printf("%f\n",CpuUsage());

    return 0;
}
