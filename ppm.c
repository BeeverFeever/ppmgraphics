#include <stdio.h>
#include <math.h>

#define WIDTH 400
#define HEIGHT 400

/*============*/ 
/* data types */
/*============*/ 
typedef struct vec2 {
    int x, y;
} vec2;

typedef struct vec3 {
    int x, y, z;
} vec3;

typedef vec2 pixel;
typedef vec3 colour;

colour display[WIDTH][HEIGHT];


/*=====================*/ 
/* function prototypes */
/*=====================*/ 

// utils and initialisation
vec2 get_uvi(pixel p);
void fill_display(colour c);

// shapes and drawing
void draw_pixel(pixel pos, colour c);
void draw_square(vec2 pos, colour c);
void draw_circle(vec2 pos, colour c, int r);

// will render a buffer to screen
void render();

/*=========================*/ 
/* function implementations*/
/*=========================*/ 
int main(void)
{
    printf("P6\n%d %d 255\n", WIDTH, HEIGHT); 

    fill_display((colour){255, 255, 0});

    /* draw_square((vec2){10, 200}, (colour){255, 255, 255}); */
    draw_circle((vec2){200, 200}, (colour){0, 0, 0}, 50);

    render();

    return 0;
}

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
            display[y][x] = c;
        }
    }
}

void draw_pixel(pixel pos, colour c)
{
    display[pos.y][pos.x] = c;
}

// shapes
void draw_square(vec2 pos, colour c)
{
    for (int y = pos.y / 2; y < pos.y * 1.5; y++)
    {
        for (int x = pos.x - (pos.x / 2); x < pos.x + (pos.x / 2); x++)
        {
            /* if (y == pos.y - (pos.y / 2) || y == pos.y + (pos.y / 2)) {} */
            draw_pixel((pixel){x, y}, c);
            /* printf("debug\n"); */
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
void draw_circle(vec2 pos, colour c, int r)
{
    for (int y = pos.y / 2; y < pos.y * 1.5; y++)
    {
        for (int x = pos.x - (pos.x / 2); x < pos.x + (pos.x / 2); x++)
        {
            vec2 p = {
                .x = x - pos.x,
                .y = y - pos.y
            };
            double dist = sqrt(p.x*p.x + p.y*p.y);

            if (dist < r + 0.5)
                draw_pixel((pixel){x, y}, c);
        }
    }
}

/*
 * Renders a buffer (currently just the display list) to file
 *
 * NOTE: this should be the only function that writes to file
 * TODO: implement file saving instead of just printf
 */
void render()
{
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c%c%c", display[y][x].x, display[y][x].y, display[y][x].z);
        }
    }
}

