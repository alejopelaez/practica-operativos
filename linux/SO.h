#ifndef LIB_SO
#define LIB_SO

namespace SO{
    /**
     * Retorna un arreglo con los pid de los procesos
     * que corren actualmente en el SO.
     * nroProcesos es la cantidad de elementos en ese arreglo.
     */
    int *GetProcessList(int *nroProcesos);

    /**
     * Retorna la fraccion de utilización de la cpu
     * desde la última llamada a esta función.
     * Si es la primera vez que se llama entonces retorna
     * la utilización desde que inicio el computador.
     */
    float CpuUsage();
}
#endif
