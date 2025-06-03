#include <math.h>

void all(float direction, float elevation, double coordinates[], int order)
{
	int numStream = pow((order + 1), 2);
	if (numStream >= sizeof(coordinates / (sizeof(coordinates))))
	{
		for (int i = 0; i < numStream; i++)
		{
			coordinates[i] = polarFunctions(direction, elevation)[i];
		}
	}
}