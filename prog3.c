#include<stdio.h>
#include<math.h>
#include<omp.h>


int main()
{
	int p,i,t;
	double t1,t2;
	int count=0,num=2,flag=1,k=0;
	printf("\nEnter the number of primes and sines : ");
	scanf("%d",&p);
	printf("Enter thread number: ");
	scanf("%d",&t);
	int a[p];
	float s[p];
	
omp_set_nested(1);
	t1=omp_get_wtime();
	#pragma omp parallel sections num_threads(t) firstprivate(num)
	{
		#pragma omp section
		{
		count=0;
		k=0;
		while(count<=p)
		{
		flag=1;
			for(i=2;i<=num/2;i++)
			{
				if(num%i==0)
				{
					flag=0;
					break;
				}
			}
			if(flag==1)
			{
				a[k++]=num;
				count++;
			}
			num++;
		}
		}
		
		#pragma omp section
		{
			for(i=0;i<p;i++)
			{
				s[i]=sin(i);
			}
		}
	}
	t2=omp_get_wtime();
	
	printf("Prime table: ");
	for(i=0;i<p;i++)
	printf("%d ",a[i]);
	
	printf("\nSine table: ");
	for(i=0;i<p;i++)
	printf("%f ",s[i]);
	
	printf("\nthe time taken is %lf",t2-t1);
	
return 0;
}
