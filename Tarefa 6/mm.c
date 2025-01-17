/**************************************************************
  Sepcs:                                                      *
    Processador: Intel(R) Core(TM) i3-2348M CPU @ 2.30GHz     *
    RAM: 6GB                                                  *
                                                              *
  Tempos:                                                     *
    Sequencial: 2m21.334s                                     *
    Paralelo: 1m23.440s                                       *
**************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void mm(double* a, double* b, double* c, int width) {
  #pragma omp parallel
  {
    for (int i = 0; i < width; i++) {
      #pragma omp for
      for (int j = 0; j < width; j++) {
        double sum = 0;
        for (int k = 0; k < width; k++) {
          double x = a[i * width + k];
          double y = b[k * width + j];
          sum += x * y;
        }
        c[i * width + j] = sum;
      }
    }
  }
}

int main(){
  int width = 2000;
  double *a = (double*) malloc (width * width * sizeof(double));
  double *b = (double*) malloc (width * width * sizeof(double));
  double *c = (double*) malloc (width * width * sizeof(double));

  for(int i = 0; i < width; i++) {
    for(int j = 0; j < width; j++) {
      a[i*width+j] = i;
      b[i*width+j] = j;
      c[i*width+j] = 0;
    }
  }

  mm(a,b,c,width);

   for(int i = 0; i < width; i++) {
   for(int j = 0; j < width; j++) {
     printf("\n c[%d][%d] = %f",i,j,c[i*width+j]);
   }
  }
}
