#include "pmsis.h"
#include "perf.h"
#include "math.h"
#include "omp.h"

// SOLUTION 1
/*
void compute_functions(float x, float *res1, float *res2, float *res3, float *res4) {
  int i;
  float r1 = 0.0f, r2 = 0.0f, r3 = 0.0f, r4 = 0.0f;;
 
  #pragma omp parallel num_threads(NUM_CORES)
  {
    if(omp_get_thread_num() == 0) 
    for(i=1; i<60; i++)
      r1 += i*sinf(((float)i/2)*x);

    if(omp_get_thread_num() == 1)
    for(i=1; i<60; i++)
      r2 += i*cosf(((float)i/2)*x);		    

    if(omp_get_thread_num() == 2)
    for(i=1; i<60; i++)
      r3 += (float)(i/2)*sinf(((float)i/4)*x);

    if(omp_get_thread_num() == 3)
    for(i=1; i<60; i++)
      r4 += (float)(i/2)*cosf(((float)i/4)*x);	    
  }
  *res1 = r1;
  *res2 = r2;
  *res3 = r3;
  *res4 = r4;
}
*/

// SOLUTION 2
void compute_functions(float x, float *res1, float *res2, float *res3, float *res4) {
  int i;
  float r1 = 0.0f, r2 = 0.0f, r3 = 0.0f, r4 = 0.0f;;

  #pragma omp parallel sections num_threads(NUM_CORES)
  {
    #pragma omp section
    for(i=1; i<60; i++)
      r1 += i*sinf(((float)i/2)*x);

    #pragma omp section
    for(i=1; i<60; i++)
      r2 += i*cosf(((float)i/2)*x);

    #pragma omp section
    for(i=1; i<60; i++)
      r3 += (float)(i/2)*sinf(((float)i/4)*x);

    #pragma omp section
    for(i=1; i<60; i++)
      r4 += (float)(i/2)*cosf(((float)i/4)*x);
  }
  *res1 = r1;
  *res2 = r2;
  *res3 = r3;
  *res4 = r4;
}

// OPTIONAL EXERCISE: Try this one!
void compute_functions_datapar(float x, float *res1, float *res2, float *res3, float *res4) {
  int i;
  float r1 = 0.0f, r2 = 0.0f, r3 = 0.0f, r4 = 0.0f;;

  #pragma omp parallel num_threads(NUM_CORES)
  {
    #pragma omp for reduction(+:r1) nowait
    for(i=1; i<60; i++)
      r1 += i*sinf(((float)i/2)*x);

    #pragma omp for reduction(+:r2) nowait
    for(i=1; i<60; i++)
      r2 += i*cosf(((float)i/2)*x);

    #pragma omp for reduction(+:r3) nowait
    for(i=1; i<60; i++)
      r3 += (float)(i/2)*sinf(((float)i/4)*x);

    #pragma omp for reduction(+:r4)
    for(i=1; i<60; i++)
      r4 += (float)(i/2)*cosf(((float)i/4)*x);
  }
  *res1 = r1;
  *res2 = r2;
  *res3 = r3;
  *res4 = r4;
}


void cluster_fn() {

  float f1, f2, f3, f4;

  // init performance counters
  INIT_STATS();

  // executing the code multiple times to perform average statistics
  ENTER_STATS_LOOP();
  
  // start measuring
  START_STATS();

  compute_functions(1.28f, &f1, &f2, &f3, &f4);
  // To progile the optional exercise:
  //compute_functions2(1.28f, &f1, &f2, &f3, &f4);

  // stop measuring
  STOP_STATS();

  // end of the performance statistics loop
  EXIT_STATS_LOOP();

  printf("Output = %f, %f, %f, %f\n", f1, f2, f3, f4);
}
