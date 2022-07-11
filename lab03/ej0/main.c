#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1000

static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Sort an array given in a file in disk.\n"
           "\n"
           "The input file must have the following format:\n"
           " * The first line must contain only a positive integer,"
           " which is the length of the array.\n"
           " * The second line must contain the members of the array"
           " separated by one or more spaces. Each member must be an integer."
           "\n\n"
           "In other words, the file format is:\n"
           "<amount of array elements>\n"
           "<array elem 1> <array elem 2> ... <array elem N>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

unsigned int data_from_file(const char *path,
                            unsigned int indexes[],
                            char letters[],
                            unsigned int max_size){  
    unsigned int length;
    length = 0;

    FILE *fichero = NULL;
    fichero = fopen(path,"r");

    while (!feof(fichero) && length < max_size)
    {
        int res = fscanf(fichero, "%u '%c'\n", &indexes[length],&letters[length]);

        if (res != 2)
        {
            fprintf(stderr, "File does not exist.\n");
            exit(EXIT_FAILURE);
        }
        length++;
    }
    fclose(fichero);
    return length;
}

int main(int argc, char *argv[]) {
    char *file;
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];

    file = parse_filepath(argc,argv);
    
    unsigned int length= data_from_file(file,indexes,letters,MAX_SIZE); 
    
    for (unsigned int  i = 0; i < length; i++)
    {
        unsigned int j = 0;
        while (indexes[j] != i)
        {
            j++;
        }
        sorted[i] = letters[j];
    }
    
    
    dump(sorted, length);

    return EXIT_SUCCESS;
}

