 class ambiMathPolar
 {
    float W_CONSTANT;
    float SQ34_CONSTANT;
    int mode;
    (1/Math.sqrt(2)) => W_CONSTANT;
    0.86602540 => SQ34_CONSTANT; // constant often used in V,T,R,S,U
    fun float degreeRad(float angle)
    {
        angle * (pi/180) => angle;
        return angle;
    }
    // needed for 1st order
    fun float xCoordinate(float elevation, float direction)
    {
        return Math.cos(degreeRad(direction)) * Math.cos(degreeRad(elevation)); 
    }
    fun float yCoordinate(float elevation, float direction)
    {
        return Math.sin(degreeRad(direction)) * Math.cos(degreeRad(elevation));
    }
    fun float zCoordinate(float elevation, float direction)
    {
        return Math.sin(degreeRad(elevation));
    }
    // needed for 2nd order
    fun float vCoordinate(float elevation, float direction)
    {
        return SQ34_CONSTANT * Math.sin(2 * (degreeRad(direction))) * Math.pow(Math.cos(degreeRad(elevation)),2);
    }
    fun float tCoordinate(float elevation, float direction)
    {
        return SQ34_CONSTANT * Math.sin(degreeRad(direction)) * Math.sin(2 * (degreeRad(elevation)));
    }
    fun float rCoordinate(float elevation, float direction)
    {
        return 0.5 * (3 * Math.pow(Math.sin(degreeRad(elevation)),2) - 1);
    }
    fun float sCoordinate(float elevation, float direction)
    {
        return SQ34_CONSTANT * Math.cos(degreeRad(direction) * Math.sin(2 * degreeRad(elevation)));
    }
    fun float uCoordinate(float elevation, float direction)
    {
        return SQ34_CONSTANT * Math.cos(2 * degreeRad(direction)) * Math.pow(Math.cos(degreeRad(elevation)),2);
    }
    // needed for 3rd order
    fun float qCoordinate(float elevation, float direction)
    {
        return 0.79056941 * Math.sin(3 * degreeRad(direction)) * Math.pow(Math.cos(degreeRad(elevation)),3);
    }
    fun float oCoordinate(float elevation, float direction)
    {
        return 1.93649167 * Math.sin(2 * degreeRad(direction)) * Math.sin(degreeRad(elevation)) * Math.pow(Math.cos(degreeRad(elevation)),2);
    }
    fun float mCoordinate(float elevation, float direction)
    {
        return 0.61237244 * Math.sin(degreeRad(direction)) * Math.cos(degreeRad(elevation)) * (5 * Math.pow(Math.sin(degreeRad(elevation)),2) - 1);
    }
    fun float kCoordinate(float elevation, float direction)
    {
        return 0.5 * Math.sin(degreeRad(elevation)) * (5 * Math.pow(Math.sin(degreeRad(elevation)),2) - 3);
    }
    fun float lCoordinate(float elevation, float direction)
    {
        return 0.61237244 * Math.cos(degreeRad(direction)) * Math.sin(degreeRad(elevation)) * (5 * Math.pow(Math.sin(degreeRad(elevation)),2) -1 );
    }
    fun float nCoordinate(float elevation, float direction)
    {
        return 1.93649167 * Math.cos(2 * degreeRad(direction)) * Math.sin(degreeRad(elevation)) * Math.pow(Math.cos(degreeRad(elevation)),2);
    }
    fun float pCoordinate(float elevation, float direction)
    {
        return 0.79056941 * Math.cos(3 * degreeRad(direction)) * Math.pow(Math.cos(degreeRad(elevation)),4);
    }
    fun void coordinates(float elevation, float direction, float array[], int order)
    {
        if(array.size() == 4 || array.size() == 9 || array.size() == 16)
        {
            Math.pow((order + 1), 2) => float numChans;
            if(numChans == 4)
            {
                xCoordinate(elevation, direction) => array[0];
                yCoordinate(elevation, direction) => array[1];
                zCoordinate(elevation, direction) => array[2];
                W_CONSTANT => array[3];
            }
            else if(numChans == 9)
            {
                xCoordinate(elevation, direction) => array[0];
                yCoordinate(elevation, direction) => array[1];
                zCoordinate(elevation, direction) => array[2];
                W_CONSTANT => array[3];
                rCoordinate(elevation, direction) => array[4];
                sCoordinate(elevation, direction) => array[5];
                tCoordinate(elevation, direction) => array[6];
                uCoordinate(elevation, direction) => array[7];
                vCoordinate(elevation, direction) => array[8];
            }
            else if( numChans == 16)
            {
                xCoordinate(elevation, direction) => array[0];
                yCoordinate(elevation, direction) => array[1];
                zCoordinate(elevation, direction) => array[2];
                W_CONSTANT => array[3];
                rCoordinate(elevation, direction) => array[4];
                sCoordinate(elevation, direction) => array[5];
                tCoordinate(elevation, direction) => array[6];
                uCoordinate(elevation, direction) => array[7];
                vCoordinate(elevation, direction) => array[8];
                lCoordinate(elevation, direction) => array[9];
                mCoordinate(elevation, direction) => array[10];
                oCoordinate(elevation, direction) => array[11];
                nCoordinate(elevation, direction) => array[12];
                pCoordinate(elevation, direction) => array[13];
                qCoordinate(elevation, direction) => array[14];
                kCoordinate(elevation, direction) => array[15];
            }
        }
        else {cherr <= IO.newline() <= "array is not correct size" <= IO.newline();}
    }
}

ambiMathPolar math;
AmbiMath wiz;
0 => float myElevation;
0 => float myDirection;
["X","Y","Z","W","R","S","T","U","V","L","M","O","N","P","Q","K",] @=> string myLetters[];
float myCoordinatesWiz[16]; // X, Y, Z, W, V, T, R, S, U, Q, O, M, K, L, N, P
float myCoordinatesMath[16]; // X, Y, Z, W, V, T, R, S, U, Q, O, M, K, L, N, P

math.coordinates(myElevation, myDirection, myCoordinatesMath, 3);
wiz.all(myDirection, myElevation, myCoordinatesWiz, 3);

for(int j; j < 4; j++)
{
    j*45 => myDirection;
    j*5 => myElevation;
    cherr <= "Direction: " <= myDirection <= " | Elevation: " <= myElevation <= IO.newline();
    for(int i; i < myCoordinatesWiz.size(); i++)
    {
        cherr <= "Chugin " <= myLetters[i] <= ": " <= myCoordinatesWiz[i] <= " | " <= "Class " <= myLetters[i] <= ": " <= myCoordinatesMath[i] <= IO.newline();
    }
    cherr <= "===================" <= IO.newline();
    math.coordinates(myDirection, myElevation, myCoordinatesMath, 3);
    wiz.all(myDirection, myElevation, myCoordinatesWiz, 3);
}