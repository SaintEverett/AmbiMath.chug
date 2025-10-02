AmbiMath test;
12 => int order;

test.all(0, 0 ,order) @=> float polarcoordinates[];

for(int i; i < Math.pow((order+1),2); i++)
{
    cherr <= "Index: " <= i <= " Polar: " <= polarcoordinates[i] <= IO.newline();
}
