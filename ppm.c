// TODO: make it so that you can just add a shape to a list and the render
// function will go through and render that list of shapes

#include "ppm.h"
#include <stdio.h>

/* colour buffer[WIDTH][HEIGHT]; */

int main(void)
{
    ppm_img img = ppm_create_img(WIDTH, HEIGHT);
    // fill the background with that colour
    ppm_fill_img((colour){24, 94, 167}, &img);

    // add some shapes
    ppm_add_square((vec2){200, 200}, (colour){255, 255, 255}, &img);
    ppm_add_circle((vec2){200, 200}, (colour){0, 0, 0}, 50, &img);
    ppm_add_circle((vec2){100, 674}, (colour){153, 73, 213}, 78, &img);
    
    ppm_render_img("test.ppm", &img);

    return 0;
}


/*=========================*/ 
/* function implementations*/
/*=========================*/ 
ppm_img ppm_create_img(int w, int h)
{
    ppm_img img;
    img.w = w;
    img.h = h;
    img.buffer = malloc(h * sizeof(colour*));
    for (size_t i = 0; i < h; i++)
    {
        img.buffer[i] = malloc(w * sizeof(colour));
    }

    return img;
}

void ppm_free_img(ppm_img b)
{
    for (size_t i = 0; i < b.h; i++)
        free(b.buffer[i]);

    free(b.buffer);
}

vec2 get_uvi(pixel p)
{
    return (vec2){
        .x = floor(((float)p.x / WIDTH) * 255),
        .y = floor(((float)p.y / HEIGHT) * 255),
    };
}

void ppm_fill_img(colour c, ppm_img *img)
{
    for (int y = 0; y < img->h; y++) {
        for (int x = 0; x < img->w; x++) {
           img->buffer[y][x] = c;
        }
    }
}

void ppm_add_pixel(pixel pos, colour c, ppm_img *img)
{
   img->buffer[pos.y][pos.x] = c;
}

// shapes
void ppm_add_square(vec2 pos, colour c, ppm_img *img)
{
    for (int y = pos.y / 2; y < pos.y * 1.5; y++) {
        for (int x = pos.x - (pos.x / 2); x < pos.x + (pos.x / 2); x++) {
            ppm_add_pixel((pixel){x, y}, c, img);
        }
    }
}

void ppm_add_circle(vec2 pos, colour c, int r, ppm_img *img)
{
    for (int y = pos.y - r; y < pos.y + r; y++) {
        for (int x = pos.x - r; x < pos.x + r; x++) {
            vec2 p = {
                .x = x - pos.x,
                .y = y - pos.y
            };
            double dist = sqrt(p.x*p.x + p.y*p.y);

            if (dist < r + 0.5)
                ppm_add_pixel((pixel){x, y}, c, img);
        }
    }
}

/*
 * Renders a buffer (currently just thebuffer list) to file
 *
 * NOTE: this should be the only function that writes to file
 */
void ppm_render_img(const char* path, ppm_img *img)
{
    FILE *f = ppm_open_file(path);
    fprintf(f, "P6\n%d %d 255\n", img->w, img->h); 
    for (int y = 0; y < img->h; y++) {
        for (int x = 0; x < img->w; x++) {
            fprintf(f, "%c%c%c", img->buffer[y][x].x, img->buffer[y][x].y, img->buffer[y][x].z);
        }
    }
    fclose(f);
}


/*===================*/ 
/* file interactions */
/*===================*/ 

static FILE* ppm_open_file(const char* path)
{
    FILE *f = fopen(path, "w");
    if (f == NULL) {
        fprintf(stderr, "ERROR: could not open file %s\n", path);
        exit(-1);
    }
    return f;
}
