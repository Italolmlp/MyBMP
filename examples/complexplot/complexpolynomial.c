#include "../../myBMP.h"
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

// Calculate polynomial value at z.
double complex p(double complex *coef, int nCoef, double complex z);

double hueToRGB(double p, double q, double t) {
	if(t < 0.0) t += 1.0;
	if(t > 1.0) t -= 1.0;
	if(t < 1.0/6.0) return p + (q - p) * 6.0 * t;
	if(t < 1.0/2.0) return q;
	if(t < 2.0/3.0) return p + (q - p) * (2.0/3.0 - t) * 6.0;
	return p;
}

int main() {

	const int width = 1000, height = 1000;
	double left, right, bottom, top;
	printf("Type the plot x interval and plot y interval\n");
	scanf("%lf%lf%lf%lf", &left, &right, &bottom, &top);

	printf("Type the polynomial degree: ");
	int degree;
	scanf("%d", &degree);

	double complex *coef = malloc((degree + 1) * sizeof(double complex));

	printf("Type the complex coefficients from power 0 to power %d\n", degree);

	for(int i = 0; i <= degree; ++i) {
		double real, imaginary;
		scanf("%lf%lf", &real, &imaginary);
		coef[i] = real + I * imaginary;
	}

	Image *image = createImage(width, height, "plot.bmp");

	double maxModule = 0.0;

	for(int i = 0; i < width; ++i) {
		for(int j = 0; j < height; ++j) {

			double complex z = (left + ((i * (right - left))/(width - 1))) + I * (bottom + ((j * (top - bottom))/(height - 1)));
			double complex pz = p(coef, degree + 1, z);
		
			if(maxModule < cabs(pz))
				maxModule = cabs(pz);
		}	
	}

	for(int i = 0; i < width; ++i) {
		for(int j = 0; j < height; ++j) {

			double complex z = (left + ((i * (right - left))/(width - 1))) + I * (bottom + ((j * (top - bottom))/(height - 1)));
			double complex pz = p(coef, degree + 1, z);

			int r, g, b;

			double m = cabs(pz);

			double h = (acos(-1.0) + carg(pz))/(2.0 * acos(-1.0));
			double s = 1.0;
			double l = (1.6 / acos(-1.0 )) * atan(m);

        	double q = l < 0.5 ? l * (1 + s) : l + s - l * s;
        	double p = 2.0 * l - q;

			g = (int) (255.0 * hueToRGB(p, q, h - (1.0/3.0)));
			b = (int) (255.0 * hueToRGB(p, q, h));
			r = (int) (255.0 * hueToRGB(p, q, h + (1.0/3.0)));	

			setPixelColor(image, i, j, r, g, b);

		}
	}


	saveToFile(image);

	return 0;
}

// Calculate polynomial value at z.
double complex p(double complex *coef, int nCoef, double complex z) {
	double complex zp = 1;
	double complex s = 0;
	for(int i = 0; i < nCoef; ++i) {
		s += coef[i] * zp;
		zp *= z;
	}
	return s;
}

