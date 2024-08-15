#include <math.h>

#include "headers/globals.h"
#include "headers/utils.h"

float rad_to_deg(float radians)
{
    return 180 * radians / PI;
}

float deg_to_rad(float degrees)
{
    return PI * degrees / 180;
}

float get_degrees(float degrees)
{
    return fmod(360 + fmod(degrees, 360), 360);
}
