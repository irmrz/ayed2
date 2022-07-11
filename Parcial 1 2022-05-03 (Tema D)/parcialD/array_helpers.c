/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"

/**
* @brief returns true when reach last line in flight file
* @return True when is the last line of the file, False otherwise
*/
static bool is_last_line(unsigned int hour, unsigned int type) {
  return  hour == HOURS - 1u && type == TYPE - 1u;
}

void array_dump(DelayTable a) {
  for (unsigned int type = 0u; type < TYPE; ++type) {
    for (unsigned int hour = 0u; hour < HOURS; ++hour) {
      Flight f = a[type][hour];
      fprintf(stdout, "%c: %s flight with %u passengers arrived at %u:00, with %u delay",
        f.code,
        f.type == 0 ? "last_mile" : "layover",
        f.passengers_amount,
        f.hour - 1,
        f.delay
      );
      if (!is_last_line(hour, type))
      {
        fprintf(stdout, "\n");
      }
    }
  }
}

unsigned int compensation_cost (DelayTable a, unsigned int h) {
  unsigned int cost = 0;
  unsigned int lm_delay = 0;
  unsigned int layover_delay = 0;

  for (unsigned int i = 0; i <= h; i++)
  {
    if (a[0][i].delay > 0)
    {
      lm_delay += a[0][i].delay;
    }
    if (a[1][i].delay > 0)
    {
      layover_delay += a[1][i].delay;
    }
    
  }
  cost = (lm_delay-MAX_LM_DELAY_ALLOWED)*COMPENSATION_PER_MINUTE + (layover_delay-MAX_LAYOVER_DELAY_ALLOWED)*COMPENSATION_PER_MINUTE;

  return cost;
}


void array_from_file(DelayTable array, const char *filepath) {
  FILE *file = NULL;

  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  char code;
  int i = 0;
  while (i < HOURS && !feof(file)) {
    /* COMPLETAR: lectura de cada vuelo */
    Flight last_mile_info = flight_from_file(file);
    Flight layover_info = flight_from_file(file);
    last_mile_info.type = 0;
    layover_info.type = 1;

    int res = fscanf(file," #%c#\n",&code);
    if (res != 1) {
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }
    last_mile_info.code = code;
    layover_info.code = code;
    /* Completar acá: completar y guardar ambos Flight en el array multidimensional*/
    array[0][i] = last_mile_info;
    array[1][i] = layover_info;

    i++;
  }
  fclose(file);
}
