#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Movie node
typedef struct Movie {
    char * name;
    int price;
    int capacity;
    struct Movie * next;
} Movie;

// Info node
typedef struct MovieList{
    int length;
    Movie * head;
} MovieList;

// properly initializes a movie list
void MovieListCreate(MovieList **);
// destroys a movie list
void MovieListDestroy(MovieList *);
// inserts a movie into a movie list
void MovieListInsert(MovieList *, char *, int, int);
// Prints the movie list on given stream
void MovieListPrint(MovieList *, FILE *);
// Deletes a movie from the list
void MovieListDelete(MovieList *, char *);
// Books a movie from the list
int MovieListBook(MovieList*, char*, int);
