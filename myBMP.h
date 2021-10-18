#ifndef MY_BMP_H
#define MY_BMP_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {

	char *fileName;

	int pixelWidth, pixelHeight;

	unsigned char **rMap, **gMap, **bMap;

} Image;

// Creates image with <pixelWidth> and <pixelHeight> named <fileName>.
Image *createImage(int pixelWidth, int pixelHeight, char *fileName);

// Sets pixel with position (x,y) with color (r, g, b).
void setPixelColor(Image *image, int x, int y, int r, int g, int b);

// Returns r (red) value from pixel (x,y).
unsigned char getRValue(Image *image, int x, int y);

// Returns g (green) value from pixel (x,y).
unsigned char getGValue(Image *image, int x, int y);

// Returns b (blue) value from pixel (x,y).
unsigned char getBValue(Image *image, int x, int y);

// Sets background color to (r, g, b).
void setBackgroundColor(Image *image, int r, int g, int b);

// Saves image content to a new file (or overwrite an existing file) named <fileName>.
void saveToFile(Image *image);

// Deallocates all memory related to Image.
void deleteImage(Image *image);

#endif
