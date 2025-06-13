AmbiMath amath;
float coordinates[4];

amath.interpolate(coordinates[1],coordinates[3],1000::ms);

cherr <= coordinates[1] <= " " <= coordinates[3] <= IO.newline();