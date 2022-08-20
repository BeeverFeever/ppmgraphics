#if !defined(PPM_H)

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//
// INFO: for the buffer, create a 2d array of colours
// 

/*============*/ 
/* data types */
/*============*/ 
#if !defined (WIDTH)
#define WIDTH 1000
#endif 
#if !defined (HEIGHT)
#define HEIGHT 1000
#endif 

typedef struct vec2 {
    int x, y;
} vec2;

typedef struct vec3 {
    int x, y, z;
} vec3;

typedef vec2 pixel;
typedef vec3 colour;

typedef struct {
    int w, h;
    colour **buffer;
} ppm_img;


/*=====================*/ 
/* function prototypes */
/*=====================*/ 

//====utils====//
ppm_img ppm_create_img(int w, int h);
void ppm_free_img(ppm_img b);
vec2 ppm_get_uv(pixel p);
// take in a buffer to write to
void ppm_fill_img(colour c, ppm_img *img);

//====shapes and drawing====//
void ppm_add_pixel(pixel pos, colour c, ppm_img *img);
void ppm_add_square(vec2 pos, colour c, ppm_img *img);
void ppm_add_circle(vec2 pos, colour c, int r, ppm_img *img);

// will render a buffer to screen
void ppm_render_img(const char* path, ppm_img *img);

//====file utilities===//
static FILE* ppm_open_file(const char* path);

#endif // PPM_H
