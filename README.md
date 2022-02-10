# MyBMP
MyBMP is a simple C library for creation of .bmp images. Currently, the only image manipulation functions change the color of a single pixel and change the color of all the pixels.

# Examples
## Plot of polynomials at the complex plane
This program uses MyBMP to color the complex plane according to a color wheel. A point of the complex plane is colored according to it's module (lightness) and it's phase (hue). When plotting a function, the point relative to the complex number z is colored according to the value of the polynomial p(z). The following image is the plot of the function p(z) = z³-i.

![Plot of z³ - i](examples/complexplot/plot.bmp)

## Mandelbrot
This program uses MyBMP to draw the famous mandelbrot set several times and then uses ffmpeg to create a video zooming into the mandelbrot set. The following image shows the mandelbrot set.
![Mandelbrot set](examples/mandelbrot/mandelbrot.bmp)

Teste
