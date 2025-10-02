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
#include <iostream>
#include <cmath>
#include <vector>
#include <array>
#include "SHCT.h"

// query
DLL_QUERY libmath_query(Chuck_DL_Query *QUERY);

#define pi 3.14159265358979323846264
#define MAX_ORDER 12

static const float degree2rad = pi / 180.0f;
static const float rad2deg = 180.0f / pi;

bool cartesian_test(float x, float y, float z)
{
    if (powf(x, 2) + powf(y, 2) + powf(z, 2) <= 1.0005 && powf(x, 2) + powf(y, 2) + powf(z, 2) >= 0.98)
        return TRUE;
    else
        return FALSE;
}

NLOUP<MAX_ORDER> norms;

std::vector<float> SH(unsigned order_, const float azimuth_, const float zenith_, bool n3d) // SH calc
{
    float azimuth_shift = (azimuth_ - 90.f) * degree2rad;      // shift "perspective" so that azi = 0 and zeni = 0 is a unity vector facing outwards from the listener (vector pointing from roughly the nose forward)
    float zenith_shift = (zenith_ - 90.f) * degree2rad;        // same here
    float coszeni = cosf(zenith_shift);                        // pre calculate cos(zenith)
    int size = (order_ + 1) * (order_ + 1);                    // pre-compute size of vector to be returned
    std::vector<float> result = std::vector<float>(size, 0.f); // instantiate vector that is the size of the results that shall be returned
    for (int order = 0; order <= (int)order_; order++)         // all orders from 0 - desired order
    {
        if (order == 0)
            result[0] = norms.SN3D(order, 0);                      // Y^0_0 is omnidirectional
        for (int degree = -order; degree <= order; degree++) // all degrees of current order
        {
            float n = n3d ? norms.N3D(order, degree) : norms.SN3D(order, degree);                                      // normalization term if n3d bool = TRUE, return N3D else SN3D
            float p = (std::assoc_legendref(order, abs(degree), coszeni));                                 // legendre NOTE: degree of legendre is current ambisonic order & order of legendre is current ambisonic degree (very frustrating)
            float r = (degree < 0) ? sinf(abs(degree) * (azimuth_shift)) : cosf(degree * (azimuth_shift)); // degree positive? Re(exp(i*azimuth*degree)) degree negative? Im(exp(i*azimuth*degree))
            result[(order * order) + order + degree] = n * p * r;                                          // place inside vector so it is ordered as Y^0_0, Y^1_-1, Y^1_0, Y^1_1
        }
    }
    return result;
}

void SH(unsigned order_, const float azimuth_, const float zenith_, std::vector<float> result, bool n3d) // SH calc
{
    float azimuth_shift = (azimuth_ - 90.f) * degree2rad; // shift "perspective" so that azi = 0 and zeni = 0 is a unity vector facing outwards from the listener (vector pointing from roughly the nose forward)
    float zenith_shift = (zenith_ - 90.f) * degree2rad;   // same here
    float coszeni = cosf(zenith_shift);                   // pre calculate cos(zenith)
    int size = (order_ + 1) * (order_ + 1) + 1;               // pre-compute size of vector to be returned
    if (result.capacity() != size)
        result.reserve(size);                           // reserve space for vector
    for (int order = 0; order <= (int)order_; order++) // all orders from 0 - desired order
    {
        if (order == 0)
            result[0] = norms.SN3D(order, 0);                      // Y^0_0 is omnidirectional
        for (int degree = -order; degree <= order; degree++) // all degrees of current order
        {
            float n = n3d ? norms.N3D(order, degree) : norms.SN3D(order, degree);                                      // normalization term if n3d bool = TRUE, return N3D else SN3D
            float p = (std::assoc_legendref(order, abs(degree), coszeni));                                 // legendre NOTE: degree of legendre is current ambisonic order & order of legendre is current ambisonic degree (very frustrating)
            float r = (degree < 0) ? sinf(abs(degree) * (azimuth_shift)) : cosf(degree * (azimuth_shift)); // degree positive? Re(exp(i*azimuth*degree)) degree negative? Im(exp(i*azimuth*degree))
            result[(order * order) + order + degree] = n * p * r;                                          // place inside vector so it is ordered as Y^0_0, Y^1_-1, Y^1_0, Y^1_1
        }
    }
}

static float w_constant = 1;
static float g_pi = CK_ONE_PI;

// ambisonic maths
float x(float direction, float elevation)
{
    float x = (cosf(direction * degree2rad) * cosf(elevation * degree2rad));
    return x;
}
float x(float x, float y, float z)
{
    return x;
}
float y(float direction, float elevation)
{
    float y = ((sinf(direction * degree2rad)) * (cosf(elevation * degree2rad)));
    return y;
}
float y(float x, float y, float z)
{
    return y;
}
float z(float direction, float elevation)
{
    float z = (sinf(elevation * degree2rad));
    return z;
}
float z(float x, float y, float z)
{
    return z;
}
float w(float direction, float elevation)
{
    return w_constant;
}
float w(float x, float y, float z)
{
    return w_constant;
}

void all(float x, float y, float z, float *coordinates, int order)
{
    int degree = (order + 1) * (order + 1);
    float r = sqrt((x * x) + (y * y) + (z * z)); // this ensures we stay within the defined sphere, normalizing the coordinates.
    x /= r;                                      // later on, coordinates that are calculated before normalization can be used to derive distance
    y /= r;
    z /= r;
    float x_2 = x * x;
    float y_2 = y * y;
    float z_2 = z * z;
    if (degree)
    {
        if (degree >= 4)
        {
            coordinates[0] = w_constant; // w
            coordinates[1] = y;          // y
            coordinates[2] = z;          // z
            coordinates[3] = x;          // x
        }
        if (degree >= 9)
        {
            coordinates[4] = (1.732050807568877f * x * y);        // v
            coordinates[5] = (1.732050807568877f * y * z);        // t
            coordinates[6] = (0.5f * (3.f * z_2 - 1.f));          // r
            coordinates[7] = (1.732050807568877f * x * z);        // s
            coordinates[8] = (0.8660254037844386f * (x_2 - y_2)); // u
        }
        if (degree >= 16)
        {
            coordinates[9] = (0.790569415f * y * ((3.f * x_2) - y_2));       // q
            coordinates[10] = (3.872983346207417f * x * y * z);              // o
            coordinates[11] = (0.6123724356957945f * y * (5.f * z_2 - 1.f)); // m
            coordinates[12] = (0.5f * z * (5.f * z_2 - 3.f));                // k
            coordinates[13] = (0.6123724356957945f * x * (5.f * z_2 - 1.f)); // l
            coordinates[14] = (1.936491673f * z * (x_2 - y_2));              // n
            coordinates[15] = (0.790569415f * x * (x_2 - (3.f * y_2)));      // p
        }
        if (degree >= 25)
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
        if (degree >= 36)
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

// impl
CK_DLL_MFUN(x_CoordinatePolar);
CK_DLL_MFUN(y_CoordinatePolar);
CK_DLL_MFUN(z_CoordinatePolar);
CK_DLL_MFUN(all_CoordinatePolar);
CK_DLL_MFUN(all_CoordinateCartesian);