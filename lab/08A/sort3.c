#include <stdio.h>

void sort3(double *x, double *y, double *z);

int main(int argc, char *argv[]) {
  double x, y, z;
  
  scanf("%lf %lf %lf", &x, &y, &z);
  sort3(&x, &y, &z);
  printf("%lf %lf %lf\n", x, y, z);
  
  return 0;
}

void sort3(double *x, double *y, double *z){
	int trans;
	for(int i=0; i<3; i++){
		if(*x > *y){
			trans = *x;
			*x = *y;
			*y = trans;
		}
		if(*y > *z){
			trans = *y;
			*y = *z;
			*z = trans;
		}
	}
}
