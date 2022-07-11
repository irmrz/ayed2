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
* @brief returns true when reach last entry in flight table
* @return True when is the last entre of the flight table, False otherwise
*/
static bool is_last_line(unsigned int hour, unsigned int type) {
  return  hour == HOURS - 1u && type == TYPE - 1u;
}

void array_dump(DeliveryTable a) {
  for (unsigned int type = 0u; type < TYPE; ++type) {
    for (unsigned int hour = 0u; hour < HOURS; ++hour) {
      Flight f = a[type][hour];
      fprintf(stdout, "%c: flight with %u %s arrived at %u:00", f.code, f.items_amount, f.type == 0 ? "boxes" : "letters", f.hour - 1);
      if (!is_last_line(hour, type))
      {
        fprintf(stdout, "\n");
      }
    }
  }
}

unsigned int extra_space_fee_cost (DeliveryTable a, unsigned int h) {
  unsigned int total = 0u;
  unsigned int boxes_extra = 0u;
  unsigned int letters_extra = 0u;

  for (unsigned int  i = 0u; i <= h && i < HOURS; i++)
  {
    if (a[boxes][i].items_amount > 0)
    {
      boxes_extra += a[boxes][i].items_amount;
    }
    if (a[letters][i].items_amount > 0)
    {
      letters_extra += a[letters][i].items_amount;
    }
  }

  if (boxes_extra > MAX_ALLOWED_BOXES)
  {
    total += (boxes_extra-MAX_ALLOWED_BOXES)*BOX_PENALTY;
  }
  if (letters_extra > MAX_ALLOWED_LETTERS)
  {
    total += (letters_extra-MAX_ALLOWED_LETTERS)*LETTER_PENALTY;
  }

  return total;
}


void array_from_file(DeliveryTable array, const char *filepath) {
  FILE *file = NULL;

  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  char code;
  unsigned int arrival_hour;
  int i = 0;
  while (i < HOURS && !feof(file)) {
    int res = fscanf(file,"_%c_",&code);
    if (res != 1) {
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }
    res = fscanf(file," %u ", &arrival_hour);
    if (res != 1) {
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }
    /* COMPLETAR: Generar y guardar ambos Flight en el array multidimensional */
    Flight flight_boxes = flight_from_file(file,code,arrival_hour);
    Flight flight_letters = flight_from_file(file,code,arrival_hour);

    array[0][i] = flight_boxes;
    array[1][i] = flight_letters;

    i++;
  }
}
