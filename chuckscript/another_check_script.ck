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
                vCoordinate(elevation, direction) => array[4];
                tCoordinate(elevation, direction) => array[5];
                rCoordinate(elevation, direction) => array[6];
                sCoordinate(elevation, direction) => array[7];
                uCoordinate(elevation, direction) => array[8];
            }
            else if( numChans == 16)
            {
                xCoordinate(elevation, direction) => array[0];
                yCoordinate(elevation, direction) => array[1];
                zCoordinate(elevation, direction) => array[2];
                W_CONSTANT => array[3];
                vCoordinate(elevation, direction) => array[4];
                tCoordinate(elevation, direction) => array[5];
                rCoordinate(elevation, direction) => array[6];
                sCoordinate(elevation, direction) => array[7];
                uCoordinate(elevation, direction) => array[8];
                qCoordinate(elevation, direction) => array[9];
                oCoordinate(elevation, direction) => array[10];
                mCoordinate(elevation, direction) => array[11];
                kCoordinate(elevation, direction) => array[12];
                lCoordinate(elevation, direction) => array[13];
                nCoordinate(elevation, direction) => array[14];
                pCoordinate(elevation, direction) => array[15];
            }
        }
        else {cherr <= IO.newline() <= "array is not correct size" <= IO.newline();}
    }
}

AmbiMath works;
ambiMathPolar help;
float myCoordinatesClass[16];
float myCoordinatesChugin[16];

works.all(0.7071067812,0.2588190451,0,myCoordinatesChugin,3);
works.all(45,15,myCoordinatesClass,3);


<<< "Chugin: ", myCoordinatesChugin[3], " | ", "Class: ", myCoordinatesClass[0] >>>;
<<< "Chugin: ", myCoordinatesChugin[1], " | ", "Class: ", myCoordinatesClass[1] >>>;
<<< "Chugin: ", myCoordinatesChugin[2], " | ", "Class: ", myCoordinatesClass[2] >>>;
<<< "Chugin: ", myCoordinatesChugin[0], " | ", "Class: ", myCoordinatesClass[3] >>>;
<<< "Chugin: ", myCoordinatesChugin[4], " | ", "Class: ", myCoordinatesClass[4] >>>;
<<< "Chugin: ", myCoordinatesChugin[5], " | ", "Class: ", myCoordinatesClass[5] >>>;
<<< "Chugin: ", myCoordinatesChugin[6], " | ", "Class: ", myCoordinatesClass[6] >>>;
<<< "Chugin: ", myCoordinatesChugin[7], " | ", "Class: ", myCoordinatesClass[7] >>>;
<<< "Chugin: ", myCoordinatesChugin[8], " | ", "Class: ", myCoordinatesClass[8] >>>;
<<< "Chugin: ", myCoordinatesChugin[9], " | ", "Class: ", myCoordinatesClass[9] >>>;
<<< "Chugin: ", myCoordinatesChugin[10], " | ", "Class: ", myCoordinatesClass[10] >>>;
<<< "Chugin: ", myCoordinatesChugin[11], " | ", "Class: ", myCoordinatesClass[11] >>>;
<<< "Chugin: ", myCoordinatesChugin[12], " | ", "Class: ", myCoordinatesClass[12] >>>;
<<< "Chugin: ", myCoordinatesChugin[13], " | ", "Class: ", myCoordinatesClass[13] >>>;
<<< "Chugin: ", myCoordinatesChugin[14], " | ", "Class: ", myCoordinatesClass[14] >>>;
<<< "Chugin: ", myCoordinatesChugin[15], " | ", "Class: ", myCoordinatesClass[15] >>>;