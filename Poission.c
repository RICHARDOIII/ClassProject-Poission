
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <stdio.h>
void gs(float &WE,float *array, int dis,int max,int st)
			{ float compare = array[st*max+st];
                	for(int i=st;i<max-st;i=i+dis)
                	{
                		for (int j=st;j<max-st;j=j+dis)
                		{
                			array[i*max+j] = .25(array[(i+dis)*max+j]
							+array[(i-dis)*max+j]
							+array[i*max+(j+dis)]
							+array[i*max+(j-dis)]);
                		}
                	}
                	WE=abs((compare-array[st*max+st])/compare);
			}

//void restriction(
////void prolong(
 void MULTIGRID_CYCLE(float &WE, int &level,int maxl, float *array)
//  	{
	int max = pow(2,maxl)+1;
	int dis = pow(2,level);
	int st=level*2;
	gs(WE,array,dis,max,st);
	RESTRICT()
	MULTIGRID_CYCLE(WE,level,maxl,array);
	}

int main()
{
 int n = 9; //Undetermined amount
float *array=(float *)malloc( n* n * sizeof(int));
int numberofgrids=0;
for (int i=0;i<n;i++)
{
	if (n-(pow(2,i)+1)==0)
	{
		break;
	}
	numberofgrids=numberofgrids+1;
}
	printf("%d\n",numberofgrids);
	float WE=1;
	int level=0;
	MULTIGRID_CYCLE(WE,level,numberofgrids-1,array);
} 

































































			
