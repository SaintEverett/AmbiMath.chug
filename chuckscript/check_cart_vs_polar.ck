AmbiMath test;

float polarcoordinates[36];
float cartcoordinates[36];
5 => int order;

test.all(45,30,polarcoordinates,order);
test.all(0.61237,0.61237,0.5,cartcoordinates,order);

for(int i; i < Math.pow((order+1),2); i++)
{
    cherr <= "Index: " <= i <= " Polar: " <= polarcoordinates[i] <= " | " <= "Cartesian: " <= cartcoordinates[i] <= IO.newline();
}

polarcoordinates.zero();
cartcoordinates.zero();