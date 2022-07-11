#include <stdio.h>
#include "weather.h"
#include "weather_utils.h"

int minima_historica(WeatherTable a) {
    int min;

    for (unsigned int año = 0; año < YEARS; año++)
    {
        for (unsigned int mes = january; mes <= december ; mes++)
        {
            for (unsigned int dia = 0; dia < DAYS; dia++)
            {
                if (mes == january && dia == 0)
                {
                    min = a[año][mes][dia]._min_temp;
                }
                else
                {
                    if (min > a[año][mes][dia]._min_temp)
                    {
                        min = a[año][mes][dia]._min_temp;
                    }
                    
                }
                
            }
            
        }
        
    }
    return min;
}

void mayor_temp_max(WeatherTable a, int output[YEARS]){
    int maxima_año;
    for (unsigned int año = 0u; año < YEARS; año++)
    {
        maxima_año = a[año][january][1]._max_temp;
        for (unsigned int mes = january; mes <= december ; mes++)
        {
            for (unsigned int dia = 0u; dia < DAYS; dia++)
            {
                if (maxima_año < a[año][mes][dia]._max_temp)
                {
                    maxima_año = a[año][mes][dia]._max_temp;
                }
                
            }
            
        }
        output[año] = maxima_año;
    }
}

void max_mensual_precip(WeatherTable a, int maximas[YEARS]){
    unsigned int mesMax,precMax,precM;

    for (unsigned int año = 0u; año < YEARS; año++)
    {
        mesMax = january;
        precMax = 0;

        for (unsigned int mes = january; mes <= december ; mes++)
        {
            precM = 0;

            for (unsigned int dia = 0u; dia < DAYS; dia++)
            {
                precM = precM + a[año][mes][dia]._rainfall;

                if (precM > precMax)
                {
                    precMax = precM;
                    mesMax = mes;
                }
                
            }
            
        }
        maximas[año] = mesMax;
    }
    
}