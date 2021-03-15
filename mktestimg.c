/* mktestimg 0.1.0 */
/* Copyright 2021 Ayush Bardhan Tripathy.
 * Licensed under MIT License. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

enum {
    FORMAT_NONE = 0,
    FORMAT_PNG,
    FORMAT_JPG,
    FORMAT_BMP,
    FORMAT_COUNT,
};

char *copystr(const char *string) {
    long len = strlen(string); 
    char *out = malloc(sizeof(char) * (len + 1));
    strcpy(out, string); 
    out[len + 1] = '\0';
    return out;
}

void usage(char *prog) {
    printf("usage: %s -w <width> -h <height> [-f <format>] [-c <channels>] [-o] <output>\n", prog);
    printf("width and height have to be non-zero. channels can be 3 or 4.\n");
    printf("available formats: png: %d, jpg: %d, bmp: %d\n", FORMAT_PNG, FORMAT_JPG, FORMAT_BMP);
}

int main(int argc, char **argv) {
    if (argc < 4) {
        usage(argv[0]);
        return 0;
    }

    char *output = NULL; 
    int width = 0, height = 0, channels = 0, format = 0;

    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "-w") && width == 0) {
            width = atoi(argv[++i]);
        }
        else if (!strcmp(argv[i], "-h") && height == 0) {
            height = atoi(argv[++i]);
        }
        else if (!strcmp(argv[i], "-f") && format == 0) {
            format = atoi(argv[++i]);
        }
        else if (!strcmp(argv[i], "-c") && channels == 0) {
            channels = atoi(argv[++i]);
        }
        else {
            if (!i) continue;
            if (!output) {
                if (!strcmp(argv[i], "-o")) i++;
                output = copystr(argv[i]);
            }
            else {
                printf("unknown argument: %s\n", argv[i]);
                return 0;
            }
        }
    }

    if (!(width && height)) {
        fprintf(stderr, "%s: width or height cannot be zero\n", argv[0]);
        return 0;
    }

    if (!format || format >= FORMAT_COUNT) format = FORMAT_PNG;
    if (!channels || channels > 4 || channels < 3) channels = 4;
    if (!output) output = copystr("out.img");

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
    free(output);
    free(data);
    return 0;
}
