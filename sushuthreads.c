#include <stdio.h>
#include <omp.h>
int main()
{
	double start,end,time,startchuan,endchuan,timechuan;
	int i,j,flg,sum=0,a=0;
	FILE *fp;
	fp=fopen("result","w");
	startchuan=omp_get_wtime();
	for (i=2;i<=100000;i++)
	{
		flg=1;
		for(j=2;j<i;j++)
		{
			if(i%j==0)
			{
				flg=0;break;
			}
		}
		if(flg)
		{
			a=a+1;
			fprintf(fp,"%d\t",i);
		}
	}
	endchuan=omp_get_wtime();
	timechuan=endchuan-startchuan;

	printf("找到素数个数为%5d\n",a);
	printf("串行运行时间 = %13.5f seconds\n",timechuan);
	

	start=omp_get_wtime();
	a=0;
	#pragma omp parallel for private (i,j,flg,)
	for (i=2;i<=100000;i++)
	{

		flg=1;
		for(j=2;j<i;j++)
		{
			if(i%j==0)
			{
				a=a+1;
				flg=0;break;
			}
		}
	}
	end=omp_get_wtime();
	time=end-start;
	printf("OpenMP并行运行时间为 %13.5f seconds\n",time);

	
	start=omp_get_wtime();
	a=0;
	#pragma acc parallel  
	for (i=2;i<=100000;i++)
	{

		flg=1;
		for(j=2;j<i;j++)
		{
			if(i%j==0)
			{
				a=a+1;
				flg=0;break;
			}
		}
	}
	end=omp_get_wtime();
	time=end-start;
	printf("OpenACC并行运行时间为 %13.5f seconds\n",time);


	fclose(fp);
	return 0;
}

