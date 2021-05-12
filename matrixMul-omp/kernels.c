#include "pmsis.h"
#include "omp.h"

void matMul(int * pSrcA, int  * pSrcB, int * pDstC, int m, int n, int o) {
    int i, j, k;

    for (k = 0; k < o; k++) {
        for (i = 0; i < m; i++) {
            int32_t sum = 0;
            for (j = 0; j < n; j++) {
                int a = pSrcA[i * n + j];
                int b = pSrcB[j * o + k];
                sum += a * b;
            }
            pDstC[i * o + k] = sum;
        }
    }
}


