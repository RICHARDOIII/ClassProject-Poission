#include <stdlib>
#include <cmath>
#include <iostream>
void MULTIGRID_CYCLE(float &ERROR, int levels, float array)
{	levels=levels-1;
	float LError=0;
	GAUSS(LError,
	float pass
}
void GAUSS(float &LERROR,float *passarray)

void restriction(

int main()
{	

	// Size of the rows/columns array that will be pass through	
	int n = 9 //Undetermined amount
	int *array=(int *)malloc( n* n * sizeof(float));
	

//	start partioning the array in courser and courser grids
//	Operates on a (2^i+1)by(2^i+1)grid
//	With a (2^i-1) by (2^i-1) grid
//      EXAMPLE
//      /	/	/
//      /	U	/	The  Grid starts from the Center and Goes out so we want to 
//      /	/	/	make the thing recursive
		//	
	int numberofgrids=0;
	for (int i=0;i++)
	{
		numberofgrids+=1;
		if (n-(pow(2,i)+1)==0)
			{
			break;
			}
	}
	
	while error<.001
	{	int l=numberofgrids;
		for(int i=0;i<numberofgrids;
		{	
			int Lerror=0;
				for (int j=0;j<l;j++)
				{	
	// MULTIGRIDCYCLE
	// STEPS:1
	// SMOOTH
	// 2: RESTRICT
	// 3:GO DOWN A LEVEL 
	// 4:IF level is 0 then do things
	
// START WITH MAX ERROR
}






			
