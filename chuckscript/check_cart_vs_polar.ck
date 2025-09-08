AmbiMath test;
Math.sqrt(4*pi) => float sqrt4PI;
float check[36];
1 => int order;

test.all(32, 6.0 ,order) @=> float polarcoordinates[];
test.all(0.0,1.0,0.0,order) @=> float cartcoordinates[];

for(int i; i < Math.pow((order+1),2); i++)
{
    cherr <= "Index: " <= i <= " Polar: " <= polarcoordinates[i] <= " | " <= "Cartesian: " <= cartcoordinates[i] <= IO.newline();
}
