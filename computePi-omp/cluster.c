#include "pmsis.h"
#include "perf.h"


float iterative_pi(int n) {
        float x, area = 0;
        int i;
        
	// SOLUTION 1: 
        // #pragma omp parallel for num_threads(NUM_CORES)
        // SOLUTION 2:
        #pragma omp parallel for num_threads(NUM_CORES) reduction(+:area)
        for(i=0; i<n; i++) {
                x = (i + 0.5f)/n;
                float val = 4.0f/(1.0f + x*x);
		// SOLUTION 1:
                // #pragma omp critical
                area += val;
        }
        return area/n;
}


void cluster_fn() {

  float x;

  // init performance counters
  INIT_STATS();

  // executing the code multiple times to perform average statistics
  ENTER_STATS_LOOP();
  
  // start measuring
  START_STATS();

  x = iterative_pi(100);

  // stop measuring
  STOP_STATS();

  // end of the performance statistics loop
  EXIT_STATS_LOOP();

  printf("Value of PI = %f\n", x);
}
