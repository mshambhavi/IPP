#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main()
{
	int m,n,i,p,q,sum,k,j;
	double t1,t2;
	printf("Enter the size of the matrix 1 : ");
	scanf("%d %d",&m,&n);
	
	printf("Enter the size of the matrix 2 : ");
	scanf("%d %d",&p,&q);

	if(n!=p)
	{
	printf("Multiplication not possible");
	return 0;
	}
	int *a[m];
	for(i=0;i<m;i++)
	a[i]=(int*)malloc(sizeof(int)*n);
	
	int *b[p];
	for(i=0;i<p;i++)
	b[i]=(int*)malloc(sizeof(int)*q);

	int *c[m];
	for(i=0;i<m;i++)
	c[i]=(int*)malloc(sizeof(int)*q);
	//printf("Enter matrix 1: \n");
t1=omp_get_wtime();
#pragma omp parallel num_threads(8)
{
#pragma omp for schedule(dynamic)
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			a[i][j]=i+j;		
	//printf("Enter matrix 2: \n");
#pragma omp  for schedule(dynamic)
	for(i=0;i<p;i++)
		for(j=0;j<q;j++)
			b[i][j]=i-j;
#pragma omp for schedule(dynamic)
	for(i=0;i<m;i++)
		for(j=0;j<q;j++)
			c[i][j]=0;
#pragma omp for schedule(dynamic,4)
	for(i=0;i<m;i++)
	{
		//printf("executed by thread %d\n",omp_get_thread_num());
		for(j=0;j<q;j++)
		{
			//printf("executed by thread %d\n",omp_get_thread_num());
			for(k=0;k<n;k++)
			{
				//printf("executed by thread %d\n",omp_get_thread_num());
				c[i][j]+=a[i][k]*b[k][j];
			}
		}

	}
}
t2=omp_get_wtime();
	

	
		
		for(i=0;i<m;i++)
		{
			for(j=0;j<q;j++)
			{ 
				printf("%d ",c[i][j]);
			}
			printf("\n");
		}
printf("Time: %.8lf\n",t2-t1);
	

return 0;
}
