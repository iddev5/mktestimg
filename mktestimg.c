/* Copyright 2021 Ayush Bardhan Tripathy.
 * Licensed under MIT License.
 */

#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

enum {
    FORMAT_NONE = 0,
    FORMAT_PNG,
    FORMAT_JPG,
    FORMAT_BMP
};

void usage(char *prog) {
    printf("usage: %s -w <width> -h <height> [-f <format>] [-c <channels>] [-o] <output>\n", prog);
    printf("available formats: png: %d, jpg: %d, bmp: %d\n", FORMAT_PNG, FORMAT_JPG, FORMAT_BMP);
}

int main(int argc, char **argv) {
    if (argc < 4) {
        usage(argv[0]);
        return 0;
    }

    char output[255] = "\0";
    int width = 0, height = 0, channels = 0, format = 0;

    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "-w") && width == 0) {
            width = atoi(argv[++i]);
        }
        else if (!strcmp(argv[i], "-h") && height == 0) {
            height = atoi(argv[++i]);
        }
        else if (!strcmp(argv[i], "-c") && channels == 0) {
            channels = atoi(argv[++i]);
        }
        else {
            if (!strcmp(argv[i], "-o")) i++;
            strcpy(output, argv[i]);
            
            //else {
            //    printf("unknown argument: %s\n", argv[i]);
            //    return 0;
            //}
        }
    }

    printf("width: %d\nheight: %d\nchannels: %d\noutput: %s\n", width, height, channels, output);

    stbi_write_png_compression_level = 1;
    char *data = malloc(sizeof(char) * width * height * channels);
    
    for (int i = 0; i < width * height; i++) {
        data[i * channels + 0] = 255;
        data[i * channels + 1] = 0;
        data[i * channels + 2] = 0;
        data[i * channels + 3] = 255;
    }

    if (format = FORMAT_PNG) stbi_write_png(output, width, height, channels, data, width * channels);
    else if (format == FORMAT_BMP) stbi_write_bmp(output, width, height, channels, data);
    else if (format == FORMAT_JPG) stbi_write_jpg(output, width, height, channels, data, 1);

    printf("image created successfully: %s\n", output);
    free(data);
    return 0;
}
