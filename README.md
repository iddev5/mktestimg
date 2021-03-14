# mktestimg
Simple CLI application to generate an image of given dimensions, format and channels. Written in C!
Uses stb_image_write.h

## Supported Formats
- png
- jpg
- bmp

## Building
```./build.sh```

## Usage
```./mktestimg```
will output all the necessary info
```
usage: ./mktestimg -w <width> -h <height> [-f <format>] [-c <channels>] [-o] <output>
available formats: png: 1, jpg: 2, bmp: 3
```

