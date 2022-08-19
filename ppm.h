#if !defined(PPM_H)

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*============*/ 
/* data types */
/*============*/ 
#define WIDTH 1000
#define HEIGHT 1000

typedef struct vec2 {
    int x, y;
} vec2;

typedef struct vec3 {
    int x, y, z;
} vec3;

typedef vec2 pixel;
typedef vec3 colour;

static colour buffer[WIDTH][HEIGHT];


/*=====================*/ 
/* function prototypes */
/*=====================*/ 

// utils
vec2 get_uvi(pixel p);
void fill_display(colour c);

// shapes and drawing
void add_pixel(pixel pos, colour c);
void add_square(vec2 pos, colour c);
void add_circle(vec2 pos, colour c, int r);

// will render a buffer to screen
void render(const char* path);

// file utilities
FILE* open_file(const char* path);

#endif // PPM_H
