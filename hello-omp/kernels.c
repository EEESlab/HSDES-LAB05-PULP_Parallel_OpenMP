#include "pmsis.h"

void matMul(int * pSrcA, int  * pSrcB, int * pDstC, int m, int n, int o) {
    uint32_t i, j, k;

    for (k = 0; k < o; k++) {
        for (i = 0; i < m; i++) {
            int32_t sum = 0;
            for (j = 0; j < n; j++) {
                int32_t a = pSrcA[i * n + j];
                int32_t b = pSrcB[j * o + k];
                sum += a * b;
            }
            pDstC[i * o + k] = sum;
        }
    }
}

PI_L1 float area_sh = 0.0f;
float iterative_pi(int n) { 
	float x, area = 0; 
	int i; 
#if NUM_CORES > 1
	if(pi_core_id() == 0) area_sh = 0;
	pi_cl_team_barrier();
#endif	
	for(i=pi_core_id(); i<n; i+=NUM_CORES) {   
		x = (i + 0.5f)/n; 
	        float val = 4.0f/(1.0f + x*x);	
		area += val;
	}
#if NUM_CORES > 1	
        pi_cl_team_barrier();
	pi_cl_team_critical_enter();
	area_sh += area;
	pi_cl_team_critical_exit();
	pi_cl_team_barrier();
	return area_sh/n;
#else
	return area/n;
#endif	
}

