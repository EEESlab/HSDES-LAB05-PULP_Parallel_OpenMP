#include "omp.h"
#include "math.h"

float a = 0.5f;
int b = 1, c = 2;

void cluster_fn() {

  // STEP 1: I use a parallel directive, but all Variables are shared (default)
  // #pragma omp parallel num_threads(NUM_CORES)
  // STEP 2: Variable a is used by each thread, it must be private
  // #pragma omp parallel num_threads(NUM_CORES) private(a)
  // STEP 3: Since the initial value is significative, we need firstprivate to copy the initial value in the context
  #pragma omp parallel num_threads(NUM_CORES) firstprivate(a)
  {
    a = cosf(omp_get_thread_num()*a);
    printf("Core %d, var a (before) =  %f\n", omp_get_thread_num(), a);
    printf("Core %d, var b =  %d\n", omp_get_thread_num(), b);
    printf("Core %d, var c =  %d\n", omp_get_thread_num(), c);
    printf("Core %d, var a (after) =  %f\n", omp_get_thread_num(), a);
  }
}

