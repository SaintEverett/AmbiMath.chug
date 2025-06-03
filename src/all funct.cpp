#include <math.h>

void all(float direction, float elevation, double coordinates[], int order)
{
	if (pow((order + 1), 2) == sizeof(coordinates / (sizeof(coordinates))))
	{
		if (order == 1)
		{
			double x = (cosf(degreeRad(direction)) * cosf(degreeRad(elevation)));
			coordinates << x;
			double y = ((sinf(degreeRad(direction))) * (cosf(degreeRad(elevation))));
			coordinates << y;
			double z = (sinf(degreeRad(elevation)));
			coordinates << z;
			coordinates << w_constant;
		}
		else if (order == 2)
		{
			double x = (cosf(degreeRad(direction)) * cosf(degreeRad(elevation)));
			coordinates << x;
			double y = ((sinf(degreeRad(direction))) * (cosf(degreeRad(elevation))));
			coordinates << y;
			double z = (sinf(degreeRad(elevation)));
			coordinates << z;
			coordinates << w_constant;
			double r = (0.5 * (3 * (pow((sinf(degreeRad(elevation))), 2)) - 1));
			coordinates << r;
			double s = (0.8660254038 * (cosf(degreeRad(direction))) * (sinf((2 * degreeRad(elevation)))));
			coordinates << s; 
			double t = (0.8660254038 * (sinf(degreeRad(direction))) * (sinf((2 * degreeRad(elevation)))));
			coordinates << t;
			double u = (0.8660254038 * cosf(2 * degreeRad(direction)) * pow(cosf(degreeRad(elevation)), 2));
			coordinates << u;
			double v = (0.8660254038 * sinf(2 * degreeRad(direction)) * pow(cosf(degreeRad(elevation)), 2));
			coordinates << v;
		}
		else if (order == 3)
		{
			double x = (cosf(degreeRad(direction)) * cosf(degreeRad(elevation)));
			coordinates << x;
			double y = ((sinf(degreeRad(direction))) * (cosf(degreeRad(elevation))));
			coordinates << y;
			double z = (sinf(degreeRad(elevation)));
			coordinates << z;
			coordinates << w_constant;
			double r = (0.5 * (3 * (pow((sinf(degreeRad(elevation))), 2)) - 1));
			coordinates << r;
			double s = (0.8660254038 * (cosf(degreeRad(direction))) * (sinf((2 * degreeRad(elevation)))));
			coordinates << s;
			double t = (0.8660254038 * (sinf(degreeRad(direction))) * (sinf((2 * degreeRad(elevation)))));
			coordinates << t;
			double u = (0.8660254038 * cosf(2 * degreeRad(direction)) * pow(cosf(degreeRad(elevation)), 2));
			coordinates << u;
			double v = (0.8660254038 * sinf(2 * degreeRad(direction)) * pow(cosf(degreeRad(elevation)), 2));
			coordinates << v;
		}
	}
}