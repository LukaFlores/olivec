#ifndef OLIVE_C_
#define OLIVE_C_


void olivec_fill(uint32_t *pixels, size_t width, size_t height, uint32_t color)
{
    for (size_t i = 0; i < width*height; ++i){
        pixels[i] = color;
    }
}


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

#endif //OLIVE_C_
