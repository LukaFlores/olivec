#ifndef OLIVE_C_
#define OLIVE_C_


// SAVE Image to PPM FIlE
typedef int Errno;
#define return_defer(value) do {result = (value); goto defer;} while(0) 

Errno olivec_save_to_ppm_file(uint32_t *pixels, size_t width, size_t height, const char *file_path)
{
    int result = 0;
    FILE *f = NULL;
    
    {
        f = fopen(file_path, "wb");
        if (f == NULL) return_defer(errno);

        // PPM config
        fprintf(f, "P6\n%zu %zu 255\n", width, height);
        if (ferror(f)) return_defer(errno);

        for(size_t i = 0; i < width*height; ++i){
            uint32_t pixel = pixels[i];

            // RGB: 0xAABBGGRR
            uint8_t bytes[3] = {
                // Shift by 0 Bytes: Extract Red
                  (pixel>>(8*0))&0xFF,
                // Shift by 1 Bytes: Extract Green
                  (pixel>>(8*1))&0xFF,
                // Shift by 2 Bytes: Extract Blue
                  (pixel>>(8*2))&0xFF,
            };
            // Write Pixels to PPM File
            fwrite(bytes, sizeof(bytes), 1, f);
            if (ferror(f)) return_defer(errno);

        }

        
    }


    defer:
        if(f) fclose(f);
        return result;
}

// Fill Image with a COLOR
void olivec_fill(uint32_t *pixels, size_t width, size_t height, uint32_t color)
{
    for (size_t i = 0; i < width*height; ++i){
        pixels[i] = color;
    }
}

// FILL Rectangle at points y , x
void olivec_fil_rect(uint32_t *pixels, size_t pixels_width, size_t pixels_height, int x0, int y0, size_t w, size_t h, uint32_t color)
{
    for (int dy = 0; dy < (int) h; ++dy) {
        int y = y0 + dy;
        // If y is between the range of 0 and pixels_height
        if(0 <= y && y < (int) pixels_height){
            for (int dx = 0; dx < (int) w; ++dx){
                int x = x0 + dx;
                // If y is between the range of 0 and pixels_width
                if (0 <= x && x < (int) pixels_width){
                    pixels[y*pixels_width + x ] = color;
                }
            }
        }
    }
}

// FILL circle centered around point cx, cy with color
void olivec_fill_circle(uint32_t *pixels, size_t pixels_height, size_t pixels_width, 
        int cx, int cy, int r, 
        uint32_t color)
{
    int x1 = cx -  r;
    int y1 = cy -  r;
    int x2 = cx +  r;
    int y2 = cy +  r;

    for (int y = y1; y<= y2; ++y){
        if(0 <= y && y < (int)pixels_height){
            for(int x = x1; x<= x2; ++x){
                if (0 <= x && x < (int)pixels_width){
                    int dx = x - cx;
                    int dy = y - cy;
                    if (dx*dx + dy*dy <= r*r){
                        pixels[y*pixels_height + x] = color;
                    }
                }
            }
        }
    }

}

#endif //OLIVE_C_
