#include "../../myBMP.h"
#include <stdlib.h>
#include <math.h>

int main() {

	const int width = 1000, height = 1000;
double left = -2.0, right = 1.0, top = 1.5, bottom = -1.5;

	const double zoomCenterX = -0.77568377;
	const double zoomCenterY =  0.13646737;

	const int NUM_ITERATIONS = 500;
	const int NUM_FRAMES = 600;

	double beginWidth = 2.0, endWidth = 0.00002;

	double nowWidth = beginWidth;
	double r = pow(endWidth/beginWidth, 1.0/(double) NUM_FRAMES);

	for(int n = 0; n <= NUM_FRAMES; ++n) {

		double left = zoomCenterX - (nowWidth/2.0);
		double right = zoomCenterX + (nowWidth/2.0);
		double top = zoomCenterY + (nowWidth/2.0);
		double bottom = zoomCenterY - (nowWidth/2.0);

		char name[] = "video/mandelbrotXXX.bmp";
		name[16] = '0' + n/100;
		name[17] = '0' + (n/10) % 10;
		name[18] = '0' + n % 10;

		Image *image = createImage(width, height, name);

		for(int i = 0; i < width; ++i)
			for(int j = 0; j < height; ++j) {

				double x = left + (i * (right - left)) / (width - 1);
				double y = bottom + (j * (top - bottom)) / (height - 1);

				double x0 = 0.0, y0 = 0.0;

				int iteration = 0;
				while(x0*x0 + y0*y0 <= 4 && iteration < NUM_ITERATIONS) {

					double aux = x0*x0 - y0*y0 + x;
					y0 = 2 * x0 * y0 + y;
					x0 = aux;
					++iteration;

				}

				int color = 255 * ((double)(NUM_ITERATIONS - iteration) / (double) NUM_ITERATIONS);

				setPixelColor(image, i, j, color, 0, 0);
			}

		saveToFile(image);
		deleteImage(image);

		nowWidth *= r;
	}

    system("ffmpeg -framerate 24 -i video/mandelbrot%03d.bmp video/mandelbrotZoom.mp4");
    system("rm video/*.bmp");

	return 0;
}