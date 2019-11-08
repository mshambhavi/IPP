#include<stdio.h>
#include<omp.h>
#include<math.h>
#include<stdlib.h>


void merge(int* L,int n1,int* R,int n2,int* a,int n)
{
	int i=0,j=0,k=0;
	
	while(i<n1 && j<n2)
	{
		if(L[i]<=R[j])
		{
			a[k]=L[i];
			i++;
		}
		else
		{
			a[k]=R[j];
			j++;
		}
		k++;
	}
	
	while(i<n1)
	{
		a[k]=L[i];
		i++;
		k++;
	}
	
	while(j<n2)
	{
		a[k]=R[j];
		k++;
		j++;
	}	

}

void mergesort(int* a,int n,int num)
{
	int n1,n2,i,j;
	if(n==1)
	return ;
	
	
	n1=n/2;
	n2=n-n1;
	int L[n1],R[n2];
	
	for(i=0;i<n1;i++)
	L[i]=a[i];
	
	j=i;
	for(i=0;i<n2;i++)
	R[i]=a[j++];
	
	#pragma omp parallel sections num_threads(num)
	{
		#pragma omp section
		mergesort(L,n1,num);
		#pragma omp section 
		mergesort(R,n2,numclear
		);
	}
	merge(L,n1,R,n2,a,n);	
}


int main()
{
	int n,i,k=0;
	double t1,t2;
	printf("Enter the size of the array: ");
	scanf("%d",&n);
	
	int a[n];
	for(i=0;i<n;i++)
	a[i]=(int)random()%100;
	
	
	
	
	for(i=1;i<=8;i=pow(2,k))
	{
		t1=omp_get_wtime();
		
		mergesort(a,n,i);
		
		t2=omp_get_wtime();
		k++;
		
		printf("time taken for %d threads is %lf\n",i,t2-t1);
	
	}
	
	for(i=0;i<n;i++)
	printf("%d ",a[i]);

return 0;
}
