AmbiMath test;

float polarcoordinates[25];
float cartcoordinates[25];

test.all(45,30,polarcoordinates,4);
test.all(0.61237,0.61237,0.5,cartcoordinates,4);

for(int i; i < polarcoordinates.size(); i++)
{
    cherr <= "Polar: " <= polarcoordinates[i] <= " | " <= "Cartesian: " <= cartcoordinates[i] <= IO.newline();
}