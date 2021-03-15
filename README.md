# mktestimg
Simple CLI application to generate an image of given dimensions, format and channels. Written in C!
Uses stb_image_write.h

## Supported Formats
- png
- jpg
- bmp

## Building
```./build.sh``` on any Unix-like platform.  
For windows, just copy the command used inside it and run yourself (with gcc).

## Usage
```./mktestimg```
will output all the necessary info
```
usage: mktestimg [-v] -w <width> -h <height> [-f <format>] [-c <channels>] [-o] <output>
width and height have to be non-zero. channels can be 3 or 4.
available formats: png: 1, jpg: 2, bmp: 3
```
