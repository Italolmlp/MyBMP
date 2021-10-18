#include "myBMP.h"
#include <stdlib.h>
#include <stdio.h>

// Creates image with <pixelWidth> and <pixelHeight> named <fileName>.
Image *createImage(int pixelWidth, int pixelHeight, char *fileName) {

	Image *image = malloc(sizeof(Image));

	image->fileName = fileName;
	image->pixelWidth = pixelWidth;
	image->pixelHeight = pixelHeight;

	image->rMap = malloc(pixelHeight * sizeof(unsigned char *));
	image->gMap = malloc(pixelHeight * sizeof(unsigned char *));
	image->bMap = malloc(pixelHeight * sizeof(unsigned char *));

	for(int i = 0; i < pixelHeight; ++i) {
		image->rMap[i] = malloc(pixelWidth * sizeof(unsigned char));
		image->gMap[i] = malloc(pixelWidth * sizeof(unsigned char));
		image->bMap[i] = malloc(pixelWidth * sizeof(unsigned char));
	}

	return image;
}

// Sets pixel with position (x,y) with color (r, g, b).
void setPixelColor(Image *image, int x, int y, int r, int g, int b) {

	if(x < 0 || x >= image->pixelWidth || y < 0 || y > image->pixelHeight)
		return;

	image->rMap[y][x] = (unsigned char)r;
	image->gMap[y][x] = (unsigned char)g;
	image->bMap[y][x] = (unsigned char)b;

}

// Sets background color to (r, g, b).
void setBackgroundColor(Image *image, int r, int g, int b) {
	for(int x = 0; x < image->pixelWidth; ++x)
		for(int y = 0; y < image->pixelHeight; ++y)
			setPixelColor(image, x, y, r, g, b);
}

// Saves image content to a new file (or overwrite an existing file) named <fileName>.
void saveToFile(Image *image) {

	char *fileName = image->fileName;

	FILE *file = fopen(fileName, "w");
	if(file == NULL)
		return;

	int rowWidth = 3 * image->pixelWidth + (4 - (3 * image->pixelWidth) % 4) % 4;
	int fileSize = 14 + 40 + rowWidth * image->pixelHeight;
	int dataOffset = 14 + 40;
	int colorsUsed = (1 << 24);

	// Signature
	fprintf(file, "BM");

	// File size
	fprintf(file, "%c%c%c%c", (char)((fileSize >> 0 ) & 0xFF),
							  (char)((fileSize >> 8 ) & 0xFF),
							  (char)((fileSize >> 16) & 0xFF),
							  (char)((fileSize >> 24) & 0xFF));
	// Unused
	fprintf(file, "%c%c%c%c", (char)(0), (char)(0), (char)(0), (char)(0));
 
 	// Offset
	fprintf(file, "%c%c%c%c", (char)((54 >> 0 ) & 0xFF),
							  (char)((54 >> 8 ) & 0xFF),
							  (char)((54 >> 16) & 0xFF),
							  (char)((54 >> 24) & 0xFF));

	// Size of info header.
	fprintf(file, "%c%c%c%c", (char)((40 >> 0 ) & 0xFF),
							  (char)((40 >> 8 ) & 0xFF),
							  (char)((40 >> 16) & 0xFF),
							  (char)((40 >> 24) & 0xFF));

	// Width and Height
	fprintf(file, "%c%c%c%c", (char)((image->pixelWidth >> 0 ) & 0xFF),
							  (char)((image->pixelWidth >> 8 ) & 0xFF),
							  (char)((image->pixelWidth >> 16) & 0xFF),
							  (char)((image->pixelWidth >> 24) & 0xFF));
	fprintf(file, "%c%c%c%c", (char)((image->pixelHeight >> 0 ) & 0xFF),
							  (char)((image->pixelHeight >> 8 ) & 0xFF),
							  (char)((image->pixelHeight >> 16) & 0xFF),
							  (char)((image->pixelHeight >> 24) & 0xFF));
	// Number of planes
	fprintf(file, "%c%c", (char)((1 >> 0) & 0xFF), (char)((1 >> 8) & 0xFF));

	// Bits per Pixel
	fprintf(file, "%c%c", (char)((24 >> 0 ) & 0xFF), (char)((24 >> 8 ) & 0xFF));
	
	// Compression
	fprintf(file, "%c%c%c%c", (char)((0 >> 0 ) & 0xFF),
							  (char)((0 >> 8 ) & 0xFF),
							  (char)((0 >> 16) & 0xFF),
							  (char)((0 >> 24) & 0xFF));
	
	// Image Size
	fprintf(file, "%c%c%c%c", (char)((0 >> 0 ) & 0xFF),
							  (char)((0 >> 8 ) & 0xFF),
							  (char)((0 >> 16) & 0xFF),
							  (char)((0 >> 24) & 0xFF));
	
	// PixelsPerM
	fprintf(file, "%c%c%c%c", (char)((0 >> 0 ) & 0xFF),
							  (char)((0 >> 8 ) & 0xFF),
							  (char)((0 >> 16) & 0xFF),
							  (char)((0 >> 24) & 0xFF));
	fprintf(file, "%c%c%c%c", (char)((0 >> 0 ) & 0xFF),
							  (char)((0 >> 8 ) & 0xFF),
							  (char)((0 >> 16) & 0xFF),
							  (char)((0 >> 24) & 0xFF));
	
	// Colors used
	fprintf(file, "%c%c%c%c", (char)((colorsUsed >> 0 ) & 0xFF),
							  (char)((colorsUsed >> 8 ) & 0xFF),
							  (char)((colorsUsed >> 16) & 0xFF),
							  (char)((colorsUsed >> 24) & 0xFF));
	
	// Important Colors
	fprintf(file, "%c%c%c%c", (char)((0 >> 0 ) & 0xFF),
							  (char)((0 >> 8 ) & 0xFF),
							  (char)((0 >> 16) & 0xFF),
							  (char)((0 >> 24) & 0xFF));
	
	// Pixel Data
	for(int y = 0; y < image->pixelHeight; ++y) {
		for(int x = 0; x < image->pixelWidth; ++x) {

			fprintf(file, "%c%c%c",image->bMap[y][x], image->gMap[y][x], image->rMap[y][x]);

		}
		for(int i = 0; i < (4 - (3 * image->pixelWidth) % 4) % 4; ++i)
			fprintf(file, "%c", (char)(0));
	}
	fclose(file);
}

// Deallocates all memory related to Image.
void deleteImage(Image *image) {

	for(int i = 0; i < image->pixelHeight; ++i) {
		free(image->rMap[i]);
		free(image->gMap[i]);
		free(image->bMap[i]);
	}

	free(image->rMap);
	free(image->gMap);
	free(image->bMap);
}	