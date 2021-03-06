#define MAXVSIZE 1000
#include <stdio.h>
#include <stdlib.h>
#include <papi.h>
#include <math.h>

void loop(double c[], double a[], double b[], int n) 
{
     int i;

     for (i=0;i<n;i++)
       c[i] = a[i] + b[i];
}

void ehandler(char *s)
{
     fprintf(stderr, "%s\n", s);
     exit(1);
}


int main(int argc, char *argv[]) {

     double a[MAXVSIZE], b[MAXVSIZE], c[MAXVSIZE];
     int i,n;
     long long before, after;


     if (PAPI_VER_CURRENT != 
		PAPI_library_init(PAPI_VER_CURRENT))
	ehandler("PAPI_library_init error.");

     printf("Enter vector size:  ");
     scanf("%d",&n);

     for (i=0;i<n;i++) {
       a[i] = i;
       b[i] = n-i;
     }

     loop(c,a,b,n);
     before = PAPI_get_real_cyc();
     loop(c,a,b,n);
     after = PAPI_get_real_cyc();
     printf("Number of cycles = %lld\n",after-before);
     return 0;

}
