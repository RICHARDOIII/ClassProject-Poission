
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <vector>

void norm (float &error, float *r,int max)
{
	for(int i=1;i<max;i++)
	{
		for(int j=1; j<max; j++)
		{
			float e = r[i*max+j];
			error+=pow(e,2);
		}
	}
}

void f(float &thing,int i,int j,int size)
{
	i=i/size;j=j/size;
	 thing = -5.0*exp(i)*exp(-2.0*j);
}
 void phi(float &th,int i, int j,int size)
{
//	printf("t\n");
	i=i/size;j=j/size;
	th = exp(i)*exp(-2.0*j);
}
void init( float *x,float *y,int  size)
{
	for (int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
			{
				float t=0;
				f(t,i+1,j+1,size);
	//			printf("%f\n%",t);
				x[i*size+j]=t;
			}
	}
	for (int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
			{	float th=0;
				phi(th,i+1,j+1,size);
//				printf("%f\n%",th);			
				y[i*size+j]=th;
			}
	}

}

void gs(float *F,float *p,int l ,int max) 
{	
	int  dis=pow(2,l);
	for(int i=dis;i<max-dis;i=i+dis)
                	{
                		for (int j=0;j<max;j=j+dis)
                		{
					p[i*max+j] = .25*(p[(i+dis)*max+j]
							+p[(i-dis)*max+j]
							+p[i*max+(j+dis)]
							+p[i*max+(j-dis)]
							+(1/pow(dis,2))*F[i*max +j]);
                		}

			}
}

void resid(float *r,float *F,float *p,int l ,int max) 
{	int dis = pow(2,l);	
	for(int i=dis;i<max-dis;i=i+dis)
			{
				for (int j=dis;j<max;j=j+dis)
				{
				int	resid = 	(p[(i+dis)*max+j]
							+p[(i-dis)*max+j]
							+p[i*max+(j+dis)]
							+p[i*max+(j-dis)]
							+(1/pow(dis,2))*F[i*max +j]
							-(4*(p[i*max+j])));
				r[i*max+j]+=resid;
	//	printf("%d\n",i);		
		}

			}
}
void Rest (float *r,float *t,int l, int max)
{	
	int dis = pow(2,max-l-1);
	for(int i=0;i<dis;i++)
                	{
                		for (int j=0;j<dis;j++)
                		{
				
 				t[i*max+j] = ((4*(r[i*max+j]))+
					+
					(2*(r[(i+1)*max+j]+r[(i-1)*max+j]
					+r[i*max+(j+1)]+r[i*max+(j-1)]))
					+
					(r[(i+1)*max+(j+1)]+r[(i-1)*max+(j-1)]
					+r[(i-1)*max+(j+1)]+r[(i+1)*max+(j-1)])/16);             		
//				printf("%d",i);
				}

			}
}

void prolong(float  *e,float *r,int l, int max)
{	
	int dis = pow(2,l+1);
	for(int i=dis;i<max-dis;i=i+dis)
                	{
                		for (int j=0;j<max;j=j+dis)
                		{
				
 				int R = r[i*max+j];
				int q = .5*R;
				e[(i+1)*max+j] =q; 
				e[(i-1)*max+j] =q;
				e[i*max+(j+1)] =q;
				e[i*max+(j-1)] =q;
				int t= .25*R;
				e[(i+1)*max+(j+1)]=t;
				e[(i-1)*max+(j-1)]=t;
				e[(i-1)*max+(j+1)]=t;
				e[(i+1)*max+(j-1)]=t;           		
				printf("hi");
				}

			}
}
int MULTIGRID_CYCLE(int &l,int N,float *F, float *P,float *R,float &e)
{
//	if(l==0)
//	{==0;}
	int max=1+pow(2,N);
	gs(F,P,l,N);
//	printf("%d yep \n",l);
	resid(R, F, P, l, max);
//	printf("%d yeah \n",l);
	float *temp=(float *)malloc((pow(2,N-l-1)+1)*(pow(2,N-l-1)+1)*sizeof(int));
	Rest(R,temp,l,N);
//	printf("%d tengo\n",l);
	l+=1;
	if(l!=N-1){
	printf("t");
	MULTIGRID_CYCLE(l, N, F, P, R,e);}
	else if(l==N-1){return 0;}
//	printf("%d",l);
	prolong(R,temp,l,max);
	gs(F,P,l,N);
	resid(R,F,P,l,max);
	if(l==0)
	{norm(e,R,max);}	
	return 0;
}
int main()
{
int n =16385 ; //Undetermined amount
float *F=(float *)malloc( n* n * sizeof(int));
float *P=(float *)malloc( n* n * sizeof(int));
//printf("4\n");
//float *R;
int ngs=0;
//printf("hih");
for (int i=0;i<n;i++)
{
	ngs+=1;
	if (pow(2,ngs)>n)
	{
		break;
	}
}

	float*	R=(float *)malloc(n*n* sizeof(int));
	int level=0;
//	printf("%d\n",ngs);
	init(F,P,n);	
	
//	printf("hi");
	float error=1.0;
//	while( error>.01)
//	{
	MULTIGRID_CYCLE(level,ngs-1,F,P,R,error);	
//	}
//	printf("%f\n",error);
} 			
