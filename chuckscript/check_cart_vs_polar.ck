AmbiMath test;
Math.sqrt(4*pi) => float sqrt4PI;
float check[36];
1 => int order;

test.all(90, 1 ,order) @=> float polarcoordinates[];
test.all(1.0,0.0,0.0,order) @=> float cartcoordinates[];

for(int i; i < Math.pow((order+1),2); i++)
{
    cherr <= "Index: " <= i <= " Polar: " <= polarcoordinates[i]*sqrt4PI <= " | " <= "Cartesian: " <= cartcoordinates[i]*sqrt4PI <= IO.newline();
}
