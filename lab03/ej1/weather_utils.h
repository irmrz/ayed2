#ifndef _WEATHER_UTILS
#define _WEATHER_UTILS
#include "weather.h"
#include "array_helpers.h"

int minima_historica(WeatherTable a);

void mayor_temp_max(WeatherTable a, int maximas[YEARS]);

void max_mensual_precip(WeatherTable a, int maximas[YEARS]);


#endif