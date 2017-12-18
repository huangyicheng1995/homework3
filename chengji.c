#include <stdio.h>

#include <omp.h>

int main()

{

    int i, n,j;

    double a[100000], b[100000], result;

    n = 100000;

    result = 0.0;

    for (i = 0; i < n; i++)

    {
        a[i] = i * 1.0;

        b[i] = i * 2.0;
    }
    
    double start = omp_get_wtime( );
    #pragma omp parallel for private(i) reduction(+:result)

    for (i = 0; i < n; i++)

    {

        for (j=0;j<n;j++)
	{
		result = result + (a[i] * b[j]);
	}
    }
    double end = omp_get_wtime( );
    printf("OpenMP:\nstart = %.16g\nend = %.16g\ntime= %.16g seconds\n",start,end,end- start); 
    printf("a*b= %12.6lf\n", result); 


    start = omp_get_wtime( );
    #pragma acc kernels loop copyin(a[0:n],b[0:n]) copyout(result[0:n])
    for (i = 0; i < n; i++)

    {

        for (j=0;j<n;j++)
	{
		result = result + (a[i] * b[j]);
	}
    }
    end = omp_get_wtime( );
    printf("OpenACC:\nstart = %.16g\nend = %.16g\ntime= %.16g seconds\n",start,end,end- start); 
    printf("a*b= %12.6lf\n", result); 
    return 0;
}
