#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include "olive.c"

#define WIDTH 800
#define HEIGHT 600

static uint32_t pixels[HEIGHT*WIDTH];

void olivec_fil_rect(uint32_t *pixels, size_t pixels_width, size_t pixels_height, int x, int y, int w, int h)
{
// https://www.youtube.com/watch?v=LmQKZmQh1ZQ -- 33:08
}



int main(void)
{
    olivec_fill(pixels, WIDTH, HEIGHT, 0xFF00FF00);
    const char *file_path = "output.ppm";
    Errno err = olivec_save_to_ppm_file(pixels, WIDTH, HEIGHT, file_path);
    if(err){
        fprintf(stderr, "ERROR: Could not save the file %s: %s\n", file_path, strerror(err));
        return 1;
    }
    return 0;
}
