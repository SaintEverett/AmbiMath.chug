//-----------------------------------------------------------------------------
// file: AmbiMath.h
// desc: class library for 'AmbiMath'
//
// author: Everett M. Carpenter
// date: Summer 2025
//-----------------------------------------------------------------------------
#include "chugin.h"
// query
DLL_QUERY libmath_query(Chuck_DL_Query* QUERY);

static int w_constant = 1;
static double g_pi = CK_ONE_PI;

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
    double r = (0.5 * (3 * (pow((sinf(degreeRad(elevation))), 2)) - 1));
    return r;
}
double r(float x, float y, float z)
{
    double r = (0.5 * (3 * (pow(z, 2)) - 1));
    return r;
}
double s(float direction, float elevation)
{
    double s = (0.8660254038 * (cosf(degreeRad(direction))) * (sinf((2 * degreeRad(elevation)))));
    return s;
}
double s(float x, float y, float z)
{
    double s = (1.732050807568877 * x * z);
    return s;
}
double t(float direction, float elevation)
{
    double t = (0.8660254038 * (sinf(degreeRad(direction))) * (sinf((2 * degreeRad(elevation)))));
    return t;
}
double t(float x, float y, float z)
{
    double t = (1.732050807568877 * y * z);
    return t;
}
double u(float direction, float elevation)
{
    double u = (0.8660254038 * cosf(2 * degreeRad(direction)) * pow(cosf(degreeRad(elevation)), 2));
    return u;
}
double u(float x, float y, float z)
{
    double u = (0.8660254037844386 * (pow(x, 2) - pow(y, 2)));
    return u;
}
double v(float direction, float elevation)
{
    double v = (0.8660254038 * sinf(2 * degreeRad(direction)) * pow(cosf(degreeRad(elevation)), 2));
    return v;
}
double v(float x, float y, float z)
{
    double v = (1.732050807568877 * x * y);
    return v;
}
double l(float direction, float elevation)
{
    double l = (0.6123724357 * cosf(degreeRad(direction)) * cosf(degreeRad(elevation)) * (5 * pow(sinf(degreeRad(elevation)), 2) - 1));
    return l;
}
double l(float x, float y, float z)
{
    double l = (0.6123724356957945 * x * (5 * pow(z, 2) - 1));
    return l;
}
double m(float direction, float elevation)
{
    double m = (0.6123724357 * sinf(degreeRad(direction)) * cosf(degreeRad(elevation)) * (5 * pow(sinf(degreeRad(elevation)), 2) - 1));
    return m;
}
double m(float x, float y, float z)
{
    double m = (0.6123724356957945 * y * (5 * pow(z, 2) - 1));
    return m;
}
double o(float direction, float elevation)
{
    double o = (1.936491673 * sinf(2 * degreeRad(direction)) * sinf(degreeRad(elevation)) * pow(cosf(degreeRad(elevation)), 2));
    return o;
}
double o(float x, float y, float z)
{
    double o = (3.872983346207417 * x * y * z);
    return o;
}
double n(float direction, float elevation)
{
    double n = (1.936491673 * cosf(2 * degreeRad(direction)) * sinf(degreeRad(elevation)) * pow(cosf(degreeRad(elevation)), 2));
    return n;
}
double n(float x, float y, float z)
{
    double n = (1.936491673 * z * (pow(x, 2) - pow(y, 2)));
    return n;
}
double p(float direction, float elevation)
{
    double p = (0.790569415 * cosf(3 * degreeRad(direction)) * pow(cosf(degreeRad(elevation)), 3));
    return p;
}
double p(float x, float y, float z)
{
    double p = (0.790569415 * x * (pow(x, 2) - (3 * pow(y, 2))));
    return p;
}
double q(float direction, float elevation)
{
    double q = (0.790569415 * sinf(3 * degreeRad(direction)) * pow(cosf(degreeRad(elevation)), 3));
    return q;
}
double q(float x, float y, float z)
{
    double q = (0.790569415 * y * ((3 * pow(x, 2)) - pow(y, 2)));
    return q;
}
double k(float direction, float elevation)
{
    double k = (0.5 * sinf(degreeRad(elevation)) * (5 * pow(sinf(degreeRad(elevation)), 2) - 3));
    return k;
}
double k(float x, float y, float z)
{
    double k = (0.5 * z * (5 * pow(z, 2) - 3));
    return k;
}
double hoa4_0(float direction, float elevation)
{
    double coord = (0.739509972887452 * sinf(4 * degreeRad(direction)) * pow(sinf(degreeRad(elevation)), 4));
    return coord;
}
double hoa4_0(float x, float y, float z)
{
    double coord = (2.958039892 * x * y * (pow(x, 2) - pow(y, 2)));
    return coord;
}
double hoa4_1(float direction, float elevation)
{
    double coord = (2.091650066335189 * sinf(3 * degreeRad(direction)) * sinf(degreeRad(elevation)) * pow(cosf(degreeRad(elevation)), 3));
    return coord;
}
double hoa4_1(float x, float y, float z)
{
    double coord = (2.091650066335189 * y * z * ((3 * (pow(x, 2)) - pow(y, 2))));
    return coord;
}
double hoa4_2(float direction, float elevation)
{
    double coord = (0.5590169943749474 * sinf(2 * degreeRad(direction)) * pow(cosf(degreeRad(elevation)), 2) * (7 * pow(sinf(degreeRad(elevation)), 2) - 1));
    return coord;
}
double hoa4_2(float x, float y, float z)
{
    double coord = (1.118033989 * x * y * (7 * pow(z, 2) - 1));
    return coord;
}
double hoa4_3(float direction, float elevation)
{
    double coord = (0.3952847075210474 * sinf(degreeRad(direction)) * sinf(2 * degreeRad(elevation)) * (7 * (pow(sinf(degreeRad(elevation)), 2)) - 3));
    return coord;
}
double hoa4_3(float x, float y, float z)
{
    double coord = (0.790569415 * y * z * (7 * pow(z, 2) - 3));
    return coord;
}
double hoa4_4(float direction, float elevation)
{
    double coord = (0.125 * (35 * pow(sinf(degreeRad(elevation)), 4) - 30 * pow(sinf(degreeRad(elevation)), 2) + 3));
    return coord;
}
double hoa4_4(float x, float y, float z)
{
    double coord = (0.125 * (35 * pow(z, 4) - 30 * pow(z, 2) + 3));
    return coord;
}
double hoa4_5(float direction, float elevation)
{
    double coord = (0.3952847075210474 * cosf(degreeRad(direction)) * sinf(2 * degreeRad(elevation)) * (7 * pow(sinf(degreeRad(elevation)), 2) - 3));
    return coord;
}
double hoa4_5(float x, float y, float z)
{
    double coord = (0.790569415 * x * z * (7 * pow(z, 2) - 3));
    return coord;
}
double hoa4_6(float direction, float elevation)
{
    double coord = (0.5590169943749474 * cosf(2 * degreeRad(direction)) * pow(cosf(degreeRad(elevation)), 2) * (7 * pow(sinf(degreeRad(elevation)), 2) - 1));
    return coord;
}
double hoa4_6(float x, float y, float z)
{
    double coord = (0.5590169944 * (pow(x, 2) - pow(y, 2)) * (7 * pow(z, 2) - 1));
    return coord;
}
double hoa4_7(float direction, float elevation)
{
    double coord = (2.091650066335189 * cosf(3 * degreeRad(direction)) * sinf(degreeRad(elevation)) * pow(cosf(degreeRad(elevation)), 3));
    return coord;
}
double hoa4_7(float x, float y, float z)
{
    double coord = (2.091650066335189 * x * z * ((pow(x, 2) - (3 * pow(y, 2)))));
    return coord;
}
double hoa4_8(float direction, float elevation)
{
    double coord = (0.739509972887452 * cosf(4 * degreeRad(direction)) * pow(cosf(degreeRad(elevation)), 4));
    return coord;
}
double hoa4_8(float x, float y, float z)
{
    double coord = (0.739509972887452 * ((pow(x, 4)) - 6 * pow(x, 2) * pow(y, 2) + pow(y, 4)));
    return coord;
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
