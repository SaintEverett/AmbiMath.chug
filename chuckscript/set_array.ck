AmbiMath amath;
float origin[4];
float target[4];
for(int i; i < origin.size(); i++)
{
    Math.random2f(-1.0,1.0) => origin[i];
    Math.random2f(-1.0,1.0) => target[i];
}
amath.interpolate(origin, target, 100::ms);
100::ms => now;
for(int i; i < origin.size(); i++)
{
    cherr <= origin[i] <= " | " <= target[i] <= IO.newline();
}