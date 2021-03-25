/* mktestimg 0.1.1 */
/* Copyright 2021 Ayush Bardhan Tripathy.
 * Licensed under MIT License. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MKTESTIMG_VERSION_MAJOR 0
#define MKTESTIMG_VERSION_MINOR 2
#define MKTESTIMG_VERSION_PATCH 0
#define MKTESTIMG_VERSION_STR "0.2.0"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

enum {
    FORMAT_NONE = 0,
    FORMAT_PNG,
    FORMAT_JPG,
    FORMAT_BMP,
    FORMAT_COUNT,
};

void usage(char *prog) {
    printf("usage: %s [-v] -w <width> -h <height> [-f <format>] [-c <channels>] [-o] <output>\n\n", prog);
    printf("width and height have to be non-zero. channels can be 3 or 4.\n");
    printf("available formats: png: %d, jpg: %d, bmp: %d\n", FORMAT_PNG, FORMAT_JPG, FORMAT_BMP);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        usage(argv[0]);
        return 0;
    }

    static char *out_filename = "out.img";
    char *output = NULL; 
    int width = 0, height = 0, channels = 0, format = 0;

    for (int i = 1; i < argc; i += 2) {
        char *key = argv[i];
        char *val = argv[i + 1];

        if (key[0] == '-') {
            if (!val) {
                fprintf(stderr, "argument '%s' is missing value\n\n", key);
                usage(argv[0]);
                return 0;
            }
            else {
                if (!strcmp(key, "-v")) {
                    printf("%s v%s\n", argv[0], MKTESTIMG_VERSION_STR);
                    return 0;
                }
                else if (!strcmp(key, "-w") && width == 0) {
                    width = atoi(val);
                }
                else if (!strcmp(key, "-h") && height == 0) {
                    height = atoi(val);
                }
                else if (!strcmp(key, "-f") && format == 0) {
                    format = atoi(val);
                }
                else if (!strcmp(key, "-c") && channels == 0) {
                    channels = atoi(val);
                }
                else if (!strcmp(key, "-o") && !output) {
                    output = val;
                }
                else {
                    fprintf(stderr, "unknown argument '%s' with value '%s'\n\n", key, val);
                    usage(argv[0]);
                    return 0;
                }
            }
        }
        else if (!output) output = key;
        else continue;
    }

    if (!(width && height)) {
        fprintf(stderr, "%s: width or height cannot be zero\n", argv[0]);
        return 0;
    }

    if (!format || format >= FORMAT_COUNT) format = FORMAT_PNG;
    if (!channels || channels > 4 || channels < 3) channels = 4;
    if (!output) output = out_filename;

    printf("width: %d\nheight: %d\nchannels: %d\noutput: %s\n", width, height, channels, output);

    stbi_write_png_compression_level = 1;
    char *data = malloc(sizeof(char) * width * height * channels);
    
    for (int i = 0, res = width * height; i < res; i++) {
        data[i * channels + 0] = 255;
        data[i * channels + 1] = 0;
        data[i * channels + 2] = 0;
        data[i * channels + 3] = 255;
    }

    if (format == FORMAT_PNG) stbi_write_png(output, width, height, channels, data, width * channels);
    else if (format == FORMAT_BMP) stbi_write_bmp(output, width, height, channels, data);
    else if (format == FORMAT_JPG) stbi_write_jpg(output, width, height, channels, data, 1);

    printf("image created successfully: %s\n", output);
    free(data);
    return 0;
}
