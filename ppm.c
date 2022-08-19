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

colour buffer[WIDTH][HEIGHT];


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


int main(void)
{
    // fill the background with that colour
    fill_display((colour){24, 94, 167});

    add_square((vec2){200, 200}, (colour){255, 255, 255});
    add_circle((vec2){200, 200}, (colour){0, 0, 0}, 50);

    render("test.ppm");

    return 0;
}

/*=========================*/ 
/* function implementations*/
/*=========================*/ 

vec2 get_uvi(pixel p)
{
    return (vec2){
        .x = floor(((float)p.x / WIDTH) * 255),
        .y = floor(((float)p.y / HEIGHT) * 255),
    };
}

void fill_display(colour c)
{
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
           buffer[y][x] = c;
        }
    }
}

void add_pixel(pixel pos, colour c)
{
   buffer[pos.y][pos.x] = c;
}

// shapes
void add_square(vec2 pos, colour c)
{
    for (int y = pos.y / 2; y < pos.y * 1.5; y++) {
        for (int x = pos.x - (pos.x / 2); x < pos.x + (pos.x / 2); x++) {
            add_pixel((pixel){x, y}, c);
        }
    }
}

/* 
 * Draws circle to buffer
 *
 * @param pos center position of circle
 * @param c colour of circle
 * @param r radiua of circle
 */
void add_circle(vec2 pos, colour c, int r) 
{
    for (int y = pos.y / 2; y < pos.y * 1.5; y++) {
        for (int x = pos.x - (pos.x / 2); x < pos.x + (pos.x / 2); x++) {
            vec2 p = {
                .x = x - pos.x,
                .y = y - pos.y
            };
            double dist = sqrt(p.x*p.x + p.y*p.y);

            if (dist < r + 0.5)
                add_pixel((pixel){x, y}, c);
        }
    }
}

/*
 * Renders a buffer (currently just thebuffer list) to file
 *
 * NOTE: this should be the only function that writes to file
 * TODO: implement file saving instead of just printf
 */
void render(const char* path)
{
    FILE *f = open_file(path);
    fprintf(f, "P6\n%d %d 255\n", WIDTH, HEIGHT); 
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            fprintf(f, "%c%c%c", buffer[y][x].x, buffer[y][x].y, buffer[y][x].z);
        }
    }
    fclose(f);
}


/*===================*/ 
/* file interactions */
/*===================*/ 

FILE* open_file(const char* path)
{
    FILE *f = fopen(path, "w");
    if (f == NULL) {
        fprintf(stderr, "ERROR: could not open file %s\n", path);
        exit(-1);
    }

    return f;
}
