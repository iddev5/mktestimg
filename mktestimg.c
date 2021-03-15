/* mktestimg 0.1.1 */
/* Copyright 2021 Ayush Bardhan Tripathy.
 * Licensed under MIT License. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MKTESTIMG_VERSION_MAJOR 0
#define MKTESTIMG_VERSION_MINOR 1
#define MKTESTIMG_VERSION_PATCH 1
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

char* copy_str(const char* string) {
    if (string == NULL) {
        fprintf(stderr, "error: The string cannot be empty.\n");
        exit(EXIT_FAILURE);
    }

    long len = strlen(string) + 1;
    char* out = malloc(len);

    strcpy(out, string);
    out[strcspn(out, "\n")] = 0;

    return out;
}

/**
 * @brief Display the command-line manual.
 *
 * @param prog Executable name
 */
void usage(const char* prog) {
    printf("Usage: %s [-v] -w <width> -h <height> [-f <format>] "
           "[-c <channels>] [-o <output>]\n\n"
           "  - <width> and <height> must be non-zero\n"
           "  - <channels> can be 3 or 4\n"
           "  - <formats> available:\n"
           "      png: %d, jpg: %d, bmp: %d\n",
           prog, FORMAT_PNG, FORMAT_JPG, FORMAT_BMP);
}

int main(int argc, char** argv) {
    if (argc == 2 && !strcmp(argv[1], "-v")) {
        printf("%s v%s\n", argv[0], MKTESTIMG_VERSION_STR);
        return EXIT_SUCCESS;
    }

    if (argc < 3) {
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    char* output = NULL;
    int width = 0, height = 0, channels = 0, format = 0;

    for (int i = 1; i < argc; i++)
        if (!strcmp(argv[i], "-w") && width == 0)
            width = atoi(argv[++i]);

        else if (!strcmp(argv[i], "-h") && height == 0)
            height = atoi(argv[++i]);

        else if (!strcmp(argv[i], "-f") && format == 0)
            format = atoi(argv[++i]);

        else if (!strcmp(argv[i], "-c") && channels == 0)
            channels = atoi(argv[++i]);

        else {
            if (!i)
                continue;
            if (!output) {
                if (!strcmp(argv[i], "-o"))
                    i++;
                output = copy_str(argv[i]);
            } else {
                printf("Unexpected field: %s\n"
                       "Try typing: %s - to get help.\n",
                       argv[i], argv[0]);
                return EXIT_FAILURE;
            }
        }

    if (width == 0 || height == 0 || format == 0 || channels == 0 ||
        output == 0) {
        fprintf(stderr, "error: Arguments are malformed.\n");
        return EXIT_FAILURE;
    }

    if (!(width && height)) {
        fprintf(stderr, "%s: width or height cannot be zero!\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!format || format >= FORMAT_COUNT)
        format = FORMAT_PNG;
    if (!channels || channels > 4 || channels < 3)
        channels = 4;
    if (!output)
        output = copy_str("out.jpg");

    printf("width: %d\n"
           "height: %d\n"
           "channels: %d\n"
           "output: %s\n",
           width, height, channels, output);

    stbi_write_png_compression_level = 1;
    char* data = malloc(width * height * channels);

    for (int i = 0, res = width * height; i < res; i++) {
        data[i * channels + 0] = (char)255;
        data[i * channels + 1] = 0;
        data[i * channels + 2] = 0;
        data[i * channels + 3] = (char)255;
    }

    if (format == FORMAT_PNG)
        stbi_write_png(output, width, height, channels, data, width * channels);
    else if (format == FORMAT_BMP)
        stbi_write_bmp(output, width, height, channels, data);
    else if (format == FORMAT_JPG)
        stbi_write_jpg(output, width, height, channels, data, 1);

    printf("Image creation successful: %s\n", output);

    free(output);
    free(data);

    return 0;
}
