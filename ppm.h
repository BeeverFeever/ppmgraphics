#if !defined(PPM_H)

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*============*/ 
/* data types */
/*============*/ 

// these really don't need to be defined at all as the user passes its own width
// and height however this will be left here for some unknown reason
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

// I could just typedef a vec3 here but it kinda makes more sense to have them
// to be RGB which is what colour is represented by not XYZ
typedef struct {
    int R, G, B;
}colour;

typedef struct {
    int w, h;
    colour **buffer;
} ppm_img;


/*=====================*/ 
/* function prototypes */
/*=====================*/ 

//====utils====//

/*
 * Creates a ppm_img 
 *
 * w    - width of the ppm_img
 * h    - height of the ppm_img
 */
ppm_img ppm_create_img(int w, int h);

/*
 * Frees a ppm_img 
 *
 * b    - the ppm_img that will be freed (don't ask why it is b its 'legacy'
 * reasons)
 */
void ppm_free_img(ppm_img b);

// this was used in development for testing and is left here just because
/* vec2 ppm_get_uv(pixel p); */

//====shapes and drawing====//

/*
 * Fills a whole ppm_img with one colour
 *
 * c    - the colour to fill the ppm_img with
 * *img - the ppm_img to fill
 */
void ppm_fill_img(colour c, ppm_img *img);

/*
 * Adds a single pixel to a ppm_img
 *
 * pos  - the position of the center of the pixel
 * c    - the colour of the pixel
 * *img - the ppm_img to add the pixel to
 */
void ppm_add_pixel(pixel pos, colour c, ppm_img *img);

/*
 * Adds a square to a ppm_img 
 *
 * pos  - the position of the center of the square
 * c    - the colour of the square
 * *img - the ppm_img to add the square to
 */
void ppm_add_square(vec2 pos, colour c, ppm_img *img);

/*
 * Adds a circle to a ppm_img 
 *
 * pos  - the position of the center of the circle
 * c    - the colour of the circle
 * r    - the radius of the circle
 * *img - the ppm_img to add the circle to
 */
void ppm_add_circle(vec2 pos, colour c, int r, ppm_img *img);

/*
 * Renders a buffer to the given file
 *
 * NOTE: this should be the only function that writes to file
 *
 * path - the path of the file to render to 
 * *img - the ppm_img to render
 */
void ppm_render_img(const char* path, ppm_img *img);


//====file utilities===//

/*
 * Opens a file to writing the ppm_img to.
 *
 * path - the path of the file to open
 *
 * returns a FILE pointer to the open file
 */
static FILE* ppm_open_file(const char* path);

#endif // PPM_H
