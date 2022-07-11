#include <stdio.h>
#include <assert.h>
#include "strfuncs.h"
#include <stdlib.h>

size_t string_length(const char *str){
	size_t i;
	i = 0;

	while(str[i] != '\0' ){
		i = i + 1;
	}
	return i;
}

char *string_filter(const char *str, char c){
	size_t largo_string = string_length(str);
	char *cadena;
	size_t sin_c;
	size_t j;
	
	sin_c = 0;
	for(size_t i = 0; i < largo_string; i++){
		if(str[i] != c){
			sin_c++;
		}
	}
	printf("%lu\n",sin_c);
	cadena = malloc(sin_c * sizeof(char));
	
	j = 0;
	for(size_t i=0; i < largo_string; i++){
		if(str[i] != c){
			cadena[j] = str[i];
			j = j+1;
		}
	}
	return cadena;
}
