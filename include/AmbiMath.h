//-----------------------------------------------------------------------------
// file: AmbiMath.h
// desc: class library for 'AmbiMath'
//
// author: Everett M. Carpenter
// date: Summer 2025
// 
// Math optimization is still being worked on, since high performance calculations is needed for live diffusion. 
// Here is a list of things that should be investigated regarding optimization:
// 1. High power exponentials (this is implemented for powers > 2, justified by https://baptiste-wicht.com/posts/2017/09/cpp11-performance-tip-when-to-use-std-pow.html )
// 2. Recalculation of cos & sin of elevation and direction (consider lookups of these) 
//      - Trade off of having this method is singular coordinates cannot be called (lookup table is already implemented in "all" but not possible in individual coordinates
//        Individual coordinates could be called if Chugin ecosystem is converted to internal data storage (one instance holds current coordinates).
//        This method could be good, and the chugin could act as a full encoder when UGen functionality is implemented.
//        An example patch = AmbiEnco (ambimath with UGen function) => AmbiDeco (decoder);
// 
//        AmbiEnc => AmbiDeco;
//        for(int i; i < AmbiDec.channels(); i++)
//        {
//           AmbiDeco.chan(i) => dac.chan(i);
//        }
// 3. Index 34 is not aligned. I believe the polar equation is accurate, but something is wrong with the cartesian formulation.
// 
//-----------------------------------------------------------------------------
#include "chugin.h"
#include <float.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <limits>
#include <vector>

// query
DLL_QUERY libmath_query(Chuck_DL_Query* QUERY);

static float w_constant = 1;
static double g_pi = CK_ONE_PI;

bool cartesian_test(float x, float y, float z)
{
    if (powf(x, 2) + powf(y, 2) + powf(z, 2) <= 1.0005 && powf(x, 2) + powf(y, 2) + powf(z, 2) >= 0.98) return TRUE;
    else return FALSE;
}

// convert degrees to radians
double degreeRad(float degree)
{
    return (g_pi / 180) * degree;
}
// ambisonic maths
double x(float direction, float elevation)
{
    double x = (cosf(degreeRad(direction)) * cosf(degreeRad(elevation)));
    return x;
}
double x(float x, float y, float z)
{
    return x;
}
double y(float direction, float elevation)
{
    double y = ((sinf(degreeRad(direction))) * (cosf(degreeRad(elevation))));
    return y;
}
double y(float x, float y, float z)
{
    return y;
}
double z(float direction, float elevation)
{
    double z = (sinf(degreeRad(elevation)));
    return z;
}
double z(float x, float y, float z)
{
    return z;
}
double w(float direction, float elevation)
{
    return w_constant;
}
double w(float x, float y, float z)
{
    return w_constant;
}
double r(float direction, float elevation)
{
    double r = (0.5f * (3.f * (powf((sinf(degreeRad(elevation))), 2)) - 1.f));
    return r;
}
double r(float x, float y, float z)
{
    double r = (0.5f * (3.f * (powf(z, 2)) - 1.f));
    return r;
}
double s(float direction, float elevation)
{
    double s = (0.8660254038f * (cosf(degreeRad(direction))) * (sinf((2.f * degreeRad(elevation)))));
    return s;
}
double s(float x, float y, float z)
{
    double s = (1.732050807568877f * x * z);
    return s;
}
double t(float direction, float elevation)
{
    double t = (0.8660254038f * (sinf(degreeRad(direction))) * (sinf((2.f * degreeRad(elevation)))));
    return t;
}
double t(float x, float y, float z)
{
    double t = (1.732050807568877f * y * z);
    return t;
}
double u(float direction, float elevation)
{
    double u = (0.8660254038f * cosf(2.f * degreeRad(direction)) * powf(cosf(degreeRad(elevation)), 2));
    return u;
}
double u(float x, float y, float z)
{
    double u = (0.8660254037844386f * (powf(x, 2) - powf(y, 2)));
    return u;
}
double v(float direction, float elevation)
{
    double v = (0.8660254038f * sinf(2.f * degreeRad(direction)) * powf(cosf(degreeRad(elevation)), 2));
    return v;
}
double v(float x, float y, float z)
{
    double v = (1.732050807568877f * x * y);
    return v;
}
double l(float direction, float elevation)
{
    double l = (0.6123724357f * cosf(degreeRad(direction)) * cosf(degreeRad(elevation)) * (5.f * powf(sinf(degreeRad(elevation)), 2) - 1.f));
    return l;
}
double l(float x, float y, float z)
{
    double l = (0.6123724356957945f * x * (5.f * powf(z, 2) - 1.f));
    return l;
}
double m(float direction, float elevation)
{
    double m = (0.6123724357f * sinf(degreeRad(direction)) * cosf(degreeRad(elevation)) * (5.f * powf(sinf(degreeRad(elevation)), 2) - 1.f));
    return m;
}
double m(float x, float y, float z)
{
    double m = (0.6123724356957945f * y * (5.f * powf(z, 2) - 1.f));
    return m;
}
double o(float direction, float elevation)
{
    double o = (1.936491673f * sinf(2.f * degreeRad(direction)) * sinf(degreeRad(elevation)) * powf(cosf(degreeRad(elevation)), 2));
    return o;
}
double o(float x, float y, float z)
{
    double o = (3.872983346207417f * x * y * z);
    return o;
}
double n(float direction, float elevation)
{
    double n = (1.936491673f * cosf(2.f * degreeRad(direction)) * sinf(degreeRad(elevation)) * powf(cosf(degreeRad(elevation)), 2));
    return n;
}
double n(float x, float y, float z)
{
    double n = (1.936491673f * z * (powf(x, 2) - powf(y, 2)));
    return n;
}
double p(float direction, float elevation)
{
    float cos_e = cosf(degreeRad(elevation));
    double p = (0.790569415f * cosf(3.f * degreeRad(direction)) * (cos_e * cos_e * cos_e));
    return p;
}
double p(float x, float y, float z)
{
    double p = (0.790569415f * x * (powf(x, 2) - (3.f * powf(y, 2))));
    return p;
}
double q(float direction, float elevation)
{
    float cos_e = cosf(degreeRad(elevation));
    double q = (0.790569415f * sinf(3 * degreeRad(direction)) * (cos_e * cos_e * cos_e));
    return q;
}
double q(float x, float y, float z)
{
    double q = (0.790569415f * y * ((3.f * powf(x, 2)) - powf(y, 2)));
    return q;
}
double k(float direction, float elevation)
{
    double k = (0.5f * sinf(degreeRad(elevation)) * (5.f * powf(sinf(degreeRad(elevation)), 2) - 3.f));
    return k;
}
double k(float x, float y, float z)
{
    double k = (0.5f * z * (5.f * powf(z, 2) - 3.f));
    return k;
}
double hoa4_0(float direction, float elevation)
{
    float sin_e = sinf(degreeRad(elevation));
    double coord = (0.739509972887452f * sinf(4.f * degreeRad(direction)) * (sin_e * sin_e * sin_e * sin_e));
    return coord;
}
double hoa4_0(float x, float y, float z)
{
    double coord = (2.958039892f * x * y * (powf(x, 2) - powf(y, 2)));
    return coord;
}
double hoa4_1(float direction, float elevation)
{
    float cos_e = cosf(degreeRad(elevation));
    double coord = (2.091650066335189f * sinf(3.f * degreeRad(direction)) * sinf(degreeRad(elevation)) * (cos_e * cos_e * cos_e));
    return coord;
}
double hoa4_1(float x, float y, float z)
{
    double coord = (2.091650066335189f * y * z * ((3.f * (powf(x, 2)) - powf(y, 2))));
    return coord;
}
double hoa4_2(float direction, float elevation)
{
    double coord = (0.5590169943749474f * sinf(2.f * degreeRad(direction)) * powf(cosf(degreeRad(elevation)), 2) * (7.f * powf(sinf(degreeRad(elevation)), 2) - 1.f));
    return coord;
}
double hoa4_2(float x, float y, float z)
{
    double coord = (1.118033989f * x * y * (7.f * powf(z, 2) - 1.f));
    return coord;
}
double hoa4_3(float direction, float elevation)
{
    double coord = (0.3952847075210474f * sinf(degreeRad(direction)) * sinf(2.f * degreeRad(elevation)) * (7.f * (powf(sinf(degreeRad(elevation)), 2)) - 3.f));
    return coord;
}
double hoa4_3(float x, float y, float z)
{
    double coord = (0.790569415f * y * z * (7.f * powf(z, 2) - 3.f));
    return coord;
}
double hoa4_4(float direction, float elevation)
{
    double coord = (0.125f * (35.f * powf(sinf(degreeRad(elevation)), 4) - 30.f * powf(sinf(degreeRad(elevation)), 2) + 3.f));
    return coord;
}
double hoa4_4(float x, float y, float z)
{
    double coord = (0.125f * (35.f * (z * z * z * z) - 30.f * powf(z, 2) + 3.f));
    return coord;
}
double hoa4_5(float direction, float elevation)
{
    double coord = (0.3952847075210474f * cosf(degreeRad(direction)) * sinf(2.f * degreeRad(elevation)) * (7.f * powf(sinf(degreeRad(elevation)), 2) - 3.f));
    return coord;
}
double hoa4_5(float x, float y, float z)
{
    double coord = (0.790569415f * x * z * (7.f * powf(z, 2) - 3.f));
    return coord;
}
double hoa4_6(float direction, float elevation)
{
    double coord = (0.5590169943749474f * cosf(2.f * degreeRad(direction)) * powf(cosf(degreeRad(elevation)), 2) * (7.f * powf(sinf(degreeRad(elevation)), 2) - 1.f));
    return coord;
}
double hoa4_6(float x, float y, float z)
{
    double coord = (0.5590169944f * (powf(x, 2) - powf(y, 2)) * (7.f * powf(z, 2) - 1.f));
    return coord;
}
double hoa4_7(float direction, float elevation)
{
    float cos_e = cosf(degreeRad(elevation));
    double coord = (2.091650066335189f * cosf(3.f * degreeRad(direction)) * sinf(degreeRad(elevation)) * (cos_e * cos_e * cos_e));
    return coord;
}
double hoa4_7(float x, float y, float z)
{
    double coord = (2.091650066335189f * x * z * ((powf(x, 2) - (3.f * powf(y, 2)))));
    return coord;
}
double hoa4_8(float direction, float elevation)
{
    float cos_e = cosf(degreeRad(elevation));
    double coord = (0.739509972887452f * cosf(4.f * degreeRad(direction)) * (cos_e * cos_e * cos_e * cos_e));
    return coord;
}
double hoa4_8(float x, float y, float z)
{
    double coord = (0.739509972887452f * ((x * x * x * x) - 6.f * powf(x, 2) * powf(y, 2) + (y * y * y * y)));
    return coord;
}
void hoa5(float direction, float elevation, float*  coordinates)
{
    float sin_e = sinf(degreeRad(elevation));
    float sin_a = sinf(degreeRad(direction));
    float cos_e = cosf(degreeRad(elevation));
    float cos_a = cosf(degreeRad(direction));
    coordinates[25] = (0.70156076f * sinf(5.f * direction) * (cos_e* cos_e* cos_e* cos_e* cos_e));
    coordinates[26] = (2.128529919f * sinf(4.f * direction) * sin_e * (cos_e * cos_e * cos_e * cos_e));
    coordinates[27] = (0.522912516f * sinf(3.f * direction) * sin_e * (cos_e* cos_e* cos_e) * (9.f * (powf(sin_e, 2)) - 1.f));
    coordinates[28] = (2.561737691f * sinf(2.f * direction) * sin_e * (powf(cos_e, 2)) * (3.f * powf(sin_e, 2) - 1.f));
    coordinates[29] = (0.4841229183f * sin_a * cos_e * (21.f * (sin_e * sin_e * sin_e * sin_e) - 14.f) * (powf(sin_e, 2) + 1.f));
    coordinates[30] = (0.125f * (63.f * (sin_e * sin_e * sin_e * sin_e * sin_e) - 70.f * (sin_e * sin_e * sin_e) + 15.f * sin_e));
    coordinates[31] = (0.4841229183f * cos_a * cos_e * (21.f * ((sin_e * sin_e * sin_e * sin_e) - 14.f * (powf(sin_e, 2)) + 1.f)));
    coordinates[32] = (2.561737691f * cosf(2.f * direction) * sin_e * (powf(cos_e, 2)) * (3.f * (powf(sin_e, 2)) * 1.f));
    coordinates[33] = (0.522912516f * cosf(3.f * direction) * (cos_e * cos_e * cos_e) * (9.f * (powf(sin_e, 2)) - 1.f));
    coordinates[34] = (2.128529919f * cosf(4.f * direction) * sin_e * (cos_e * cos_e * cos_e * cos_e));
    coordinates[35] = (0.70156076f * cosf(5.f * direction) * (cos_e * cos_e * cos_e * cos_e * cos_e));
}
void hoa5(float x, float y, float z, float* coordinates)
{
    float x_2 = x * x;
    float y_2 = y * y;
    float z_2 = z * z;
    coordinates[25] = (0.70156076f * y * (5.f * (x_2 * x_2) - 10.f * x_2 * x_2 + (y_2 * y_2)));
    coordinates[26] = (8.874119675f * x * y * z * (x_2 - y_2));
    coordinates[27] = (0.522912516f * y * ((y_2 * y_2) - 2.f * x_2 * y_2 - 3.f * (x_2 * x_2) - 8.f * y_2 * z_2 + 24.f * x_2 * z_2));
    coordinates[28] = (5.123475383f * x * y * z * (2.f * z_2 * -x_2 - y_2));
    coordinates[29] = (0.4841229183f * y * ((x_2 * x_2) + 2.f * x_2 * y_2 + (y_2 * y_2) - 12.f * x_2 * z_2 - 12.f * y_2 * z_2 + 8.f * (z_2 * z_2)));
    coordinates[30] = (0.125f * z * (63.f * (z_2 * z_2) - 70.f * z_2 + 15.f));
    coordinates[31] = (0.4841229183f * x * ((x_2 * x_2) + 2.f * x_2 * y_2 + (y_2 * y_2) - 12.f * x_2 * z_2 - 12.f * y_2 * z_2 + 8.f * (z_2 * z_2)));
    coordinates[32] = (2.561737691f * z * (2.f * x_2 * z_2 - 2.f * y_2 * z_2 - (x_2 * x_2) + (y_2 * y_2)));
    coordinates[33] = (0.522912516f * x * (2.f * x_2 * y_2 + 8.f * x_2 * z_2 - 24.f * y_2 * z_2 * (x_2 * x_2) + 3.f * (y_2 * y_2)));
    coordinates[34] = (2.218529919f * z * ((x_2 * x_2) - 6.f * x_2 * y_2 + (y_2 * y_2)));
    coordinates[35] = (0.70156076f * x * ((x_2 * x_2) - 10.f * x_2 * y_2 + 5.f * (y_2 * y_2)));
}

// pointer storage of polar function pointers
typedef double (*polarFuncStorage) (float direction, float elevation);
polarFuncStorage polarFunctions[] = { w,y,z,x,v,t,r,s,u,q,o,m,k,l,n,p,hoa4_0,hoa4_1,hoa4_2,hoa4_3,hoa4_4,hoa4_5,hoa4_6,hoa4_7,hoa4_8 }; // in spherical order
// point storage of cartesian function pointers
typedef double (*cartesianFuncStorage) (float x, float y, float z);
cartesianFuncStorage cartesianFunctions[] = { w,y,z,x,v,t,r,s,u,q,o,m,k,l,n,p,hoa4_0,hoa4_1,hoa4_2,hoa4_3,hoa4_4,hoa4_5,hoa4_6,hoa4_7,hoa4_8 }; // in spherical order

void all(float direction, float elevation, float* coordinates, int order)
{
    int degree = (order + 1) * (order + 1);
    float direction_r = degreeRad(direction);
    float elevation_r = degreeRad(elevation);
    float sin_e = sinf(elevation_r);
    float sin_a = sinf(direction_r);
    float cos_e = cosf(elevation_r);
    float cos_a = cosf(direction_r);
    if (degree)
    {
        if(degree >= 4)
        {
            coordinates[0] = w_constant;
            coordinates[1] = sin_a * cos_e;
            coordinates[2] = sin_e;
            coordinates[3] = cos_a * cos_e;
        }
        if(degree >= 9)
        {
            coordinates[4] = (0.8660254038f * (sinf(2.f * direction_r)) * powf(cos_e, 2.f));
            coordinates[5] = (0.8660254038f * sin_a * (sinf(2 * elevation_r)));
            coordinates[6] = (0.5f * (3.f * powf(sin_e, 2) - 1.f));
            coordinates[7] = (0.8660254038f * (cos_a * (sinf(2 * elevation_r))));
            coordinates[8] = (0.8660254038f * cosf(2.f * direction_r) * powf(cos_e, 2));
        }
        if(degree >= 16)
        {
            coordinates[9] = (0.790569415f * sinf(3.f * direction_r) * (cos_e * cos_e * cos_e));
            coordinates[10] = (1.936491673f * (sinf(2.f * direction_r)) * sin_e * powf(cos_e, 2));
            coordinates[11] = (0.6123724357f * sin_a * cos_e * (5.f * powf(sin_e, 2) - 1.f));
            coordinates[12] = (0.5f * sin_e * (5.f * powf(sin_e, 2) - 3.f));
            coordinates[13] = (0.6123724357f * cos_a * cos_e * (5.f * powf(sin_e, 2) - 1.f));
            coordinates[14] = (1.936491673f * cosf(2.f * direction_r) * sin_e * powf(cos_e, 2));
            coordinates[15] = (0.790569415f * cosf(3.f * direction_r) * (cos_e * cos_e * cos_e));
        }
        if(degree >= 25)
        {
            coordinates[16] = (0.739509972887452f * sinf(4.f * direction_r) * (sin_e * sin_e * sin_e * sin_e));
            coordinates[17] = (2.091650066335189f * sinf(3.f * direction_r) * sin_e * (cos_e * cos_e * cos_e));
            coordinates[18] = (0.5590169943749474f * sinf(2.f * direction_r) * powf(cos_e, 2) * (7.f * powf(sin_e, 2) - 1.f));
            coordinates[19] = (0.3952847075210474f * sin_a * (2.f * cos_e * sin_e) * (7.f * powf(sin_e, 2) - 3.f));
            coordinates[20] = (0.125f * (35.f * (sin_e * sin_e * sin_e * sin_e) - 30.f * powf(sin_e, 2) + 3.f));
            coordinates[21] = (0.3952847075210474f * cos_a * (2.f * cos_e * sin_e) * (7.f * powf(sin_e, 2) - 3.f));
            coordinates[22] = (0.5590169943749474f * cosf(2.f * direction_r) * powf(cos_e, 2) * (7.f * powf(sin_e, 2) - 1.f));
            coordinates[23] = (2.091650066335189f * cosf(3.f * direction_r) * sin_e * (cos_e * cos_e * cos_e));
            coordinates[24] = (0.739509972887452f * cosf(4.f * direction_r) * (cos_e * cos_e * cos_e * cos_e));
        }
        if(degree >= 36)
        {
            coordinates[25] = (0.70156076f * sinf(5.f * direction_r) * (cos_e * cos_e * cos_e * cos_e * cos_e));
            coordinates[26] = (2.128529919f * sinf(4.f * direction_r) * sin_e * (cos_e * cos_e * cos_e * cos_e));
            coordinates[27] = (0.522912516f * sinf(3.f * direction_r) * (cos_e * cos_e * cos_e) * (9.f * powf(sin_e, 2) - 1.f));
            coordinates[28] = (2.561737691f * (2.f * cos_a * sin_a) * sin_e * powf(cos_e, 2) * (3.f * powf(sin_e, 2) - 1.f));
            coordinates[29] = (0.4841229183f * sin_a * cos_e * (21.f * (sin_e * sin_e * sin_e * sin_e) - 14.f * powf(sin_e, 2) + 1.f));
            coordinates[30] = (0.125f * (63.f * (sin_e * sin_e * sin_e * sin_e * sin_e) - 70.f * (sin_e * sin_e * sin_e) + 15.f * sin_e));
            coordinates[31] = (0.4841229183f * cos_a * cos_e * (21.f * (sin_e * sin_e * sin_e * sin_e) - 14.f * powf(sin_e, 2) + 1.f));
            coordinates[32] = (2.561737691f * cosf(2.f * direction_r) * sin_e * powf(cos_e, 2) * (3.f * powf(sin_e, 2) * 1.f));
            coordinates[33] = (0.522912516f * cosf(3.f * direction_r) * (cos_e * cos_e * cos_e) * (9.f * powf(sin_e, 2) - 1.f));
            coordinates[34] = (2.218529919f * cosf(4.f * direction_r) * sin_e * (cos_e * cos_e * cos_e * cos_e));
            coordinates[35] = (0.70156076f * cosf(5.f * direction_r) * (cos_e * cos_e * cos_e * cos_e * cos_e));
        }
    }
}

void all(float x, float y, float z, float* coordinates, int order)
{
    int degree = (order + 1) * (order + 1);
    float r = sqrt((x * x) + (y * y) + (z * z)); // this ensures we stay within our defined sphere, normalizing the coordinates.
    x /= r; // later on, coordinates that are calculated before normalization can be used to derive distance
    y /= r;
    z /= r;
    float x_2 = x * x;
    float y_2 = y * y;
    float z_2 = z * z;
    if (degree)
    {
        if(degree >= 4)
        {
            coordinates[0] = w_constant; // w
            coordinates[1] = y; // y
            coordinates[2] = z; // z 
            coordinates[3] = x; // x 
        }
        if(degree >= 9)
        {
            coordinates[4] = (1.732050807568877f * x * y); //v 
            coordinates[5] = (1.732050807568877f * y * z); // t
            coordinates[6] = (0.5f * (3.f * z_2 - 1.f)); // r
            coordinates[7] = (1.732050807568877f * x * z); // s
            coordinates[8] = (0.8660254037844386f * (x_2 - y_2)); // u
        }
        if(degree >= 16)
        {
            coordinates[9] = (0.790569415f * y * ((3.f * x_2) - y_2)); // q
            coordinates[10] = (3.872983346207417f * x * y * z); // o
            coordinates[11] = (0.6123724356957945f * y * (5.f * z_2 - 1.f)); // m
            coordinates[12] = (0.5f * z * (5.f * z_2 - 3.f)); // k
            coordinates[13] = (0.6123724356957945f * x * (5.f * z_2 - 1.f)); // l
            coordinates[14] = (1.936491673f * z * (x_2 - y_2)); // n
            coordinates[15] = (0.790569415f * x * (x_2 - (3.f * y_2))); // p
        }
        if(degree >= 25)
        {
            coordinates[16] = (2.958039892f * x * y * (x_2 - y_2));
            coordinates[17] = (2.091650066335189f * y * z * ((3.f * (x_2)-y_2)));
            coordinates[18] = (1.118033989f * x * y * (7.f * z_2 - 1.f));
            coordinates[19] = (0.790569415 * y * z * (7.f * z_2 - 3.f));
            coordinates[20] = (0.125f * (35.f * (z * z * z * z) - 30.f * z_2 + 3.f));
            coordinates[21] = (0.790569415f * x * z * (7.f * z_2 - 3.f));
            coordinates[22] = (0.5590169944f * (x_2 - y_2) * (7.f * z_2 - 1.f));
            coordinates[23] = (2.091650066335189f * x * z * ((x_2 - (3.f * y_2))));
            coordinates[24] = (0.739509972887452f * ((x_2 * x_2) - 6.f * x_2 * y_2 + (y_2 * y_2)));
        }
        if(degree >= 36)
        {
            coordinates[25] = (0.70156076f * y * (5.f * (x_2 * x_2) - 10.f * x_2 * x_2 + (y_2 * y_2)));
            coordinates[26] = (8.874119675f * x * y * z * (x_2 - y_2));
            coordinates[27] = (0.522912516f * y * ((y_2 * y_2) - 2.f * x_2 * y_2 - 3.f * (x_2 * x_2) - 8.f * y_2 * z_2 + 24.f * x_2 * z_2));
            coordinates[28] = (5.123475383f * x * y * z * (2.f * z_2 - x_2 - y_2));
            coordinates[29] = (0.4841229183f * y * ((x_2 * x_2) + 2.f * x_2 * y_2 + (y_2 * y_2) - 12.f * x_2 * z_2 - 12.f * y_2 * z_2 + 8.f * (z_2 * z_2)));
            coordinates[30] = (0.125f * z * (63.f * (z_2 * z_2) - 70.f * z_2 + 15.f));
            coordinates[31] = (0.4841229183f * x * ((x_2 * x_2) + 2 * x_2 * y_2 + (y_2 * y_2) - 12.f * x_2 * z_2 - 12.f * y_2 * z_2 + 8.f * (z_2 * z_2)));
            coordinates[32] = (2.561737691f * z * (2.f * x_2 * z_2 - 2.f * y_2 * z_2 - (x_2 * x_2) + (y_2 * y_2)));
            coordinates[33] = (0.522912516f * x * (2.f * x_2 * y_2 + 8.f * x_2 * z_2 - 24.f * y_2 * z_2 * (x_2 * x_2) + 3.f * (y_2 * y_2)));
            coordinates[34] = (2.218529919f * z * ((x_2 * x_2) - (6.f * x_2 * y_2) + (y_2 * y_2)));
            coordinates[35] = (0.70156076f * x * ((x_2 * x_2) - 10.f * x_2 * y_2 + 5.f * (y_2 * y_2)));
        }
    }
}

void singleInterpolate(CK_DL_API API, float origin, Chuck_ArrayFloat* targetArray, double time, int id)
{
    float target = API->object->array_float_get_idx(targetArray, id);
    float temp = origin;
    double slew = 0.05;
    float delta = 0;
    for (int i = 1; i < time; i++)
    {
        delta = (i / time);
        temp = (origin + (delta * (target - origin)));
    }
}

// impl
CK_DLL_MFUN(x_CoordinatePolar);
CK_DLL_MFUN(y_CoordinatePolar);
CK_DLL_MFUN(z_CoordinatePolar);
CK_DLL_MFUN(r_CoordinatePolar);
CK_DLL_MFUN(s_CoordinatePolar);
CK_DLL_MFUN(t_CoordinatePolar);
CK_DLL_MFUN(u_CoordinatePolar);
CK_DLL_MFUN(v_CoordinatePolar);
CK_DLL_MFUN(l_CoordinatePolar);
CK_DLL_MFUN(m_CoordinatePolar);
CK_DLL_MFUN(n_CoordinatePolar);
CK_DLL_MFUN(o_CoordinatePolar);
CK_DLL_MFUN(p_CoordinatePolar);
CK_DLL_MFUN(q_CoordinatePolar);
CK_DLL_MFUN(k_CoordinatePolar);
CK_DLL_MFUN(x_CoordinateCartesian);
CK_DLL_MFUN(y_CoordinateCartesian);
CK_DLL_MFUN(z_CoordinateCartesian);
CK_DLL_MFUN(r_CoordinateCartesian);
CK_DLL_MFUN(s_CoordinateCartesian);
CK_DLL_MFUN(t_CoordinateCartesian);
CK_DLL_MFUN(u_CoordinateCartesian);
CK_DLL_MFUN(v_CoordinateCartesian);
CK_DLL_MFUN(l_CoordinateCartesian);
CK_DLL_MFUN(m_CoordinateCartesian);
CK_DLL_MFUN(n_CoordinateCartesian);
CK_DLL_MFUN(o_CoordinateCartesian);
CK_DLL_MFUN(p_CoordinateCartesian);
CK_DLL_MFUN(q_CoordinateCartesian);
CK_DLL_MFUN(k_CoordinateCartesian);
CK_DLL_MFUN(HOA4_0);
CK_DLL_MFUN(HOA4_1);
CK_DLL_MFUN(HOA4_2);
CK_DLL_MFUN(HOA4_3);
CK_DLL_MFUN(HOA4_4);
CK_DLL_MFUN(HOA4_5);
CK_DLL_MFUN(HOA4_6);
CK_DLL_MFUN(HOA4_7);
CK_DLL_MFUN(HOA4_8);
CK_DLL_MFUN(all_CoordinatePolar);
CK_DLL_MFUN(all_CoordinateCartesian);
CK_DLL_MFUN(interpolation);