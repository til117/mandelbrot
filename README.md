# mandelbrot
The aim of the project is to visualize the mandelbrot set, e.g. by looping a plot of the set being zoomed in a specific point.

It is written in C, and is a project for a programming course at KTH.

Firstly, it is important to understand the Mandelbrot set. It is a set of iterations performed on the function: Z_(n+1)=Z_n^2+C where C is a complex number and Z_0=0.
The goal is to find all complex numbers C for which Z_n does not go to infinity. This is achieved by checking if Z_n≤4, because if this criteria is not fulfilled Z_n tends to go to infinity.

This is implemented by splitting C and Z to their corresponding components, i.e. their real and imaginary parts. Then, for each iteration, a counter is introduced and increased by one. This counter is used to zoom in to the set and therefore it is asked in the beginning of the code for the user to choose a mode, (1) for a picture and (2) for the zooming function. If the user chooses the picture mode, the counter is not increased for every iteration and the picture remains the same.

Furthermore, for every pixel of the picture of the set, the complex number C is introduced as a function of the pixels. The value of C is then divided by the square of the counter used for the zooming function in order to reduce C as the number of iterations grow larger. This yields that the zooming point becomes the origin of the complex plane as the number of iterations grow. Therefore a desired value of the zooming point is added to the value of C, thus resulting in a closer zoom on that point as the number of iterations grow larger.

Lastly, after the code for the zooming function is done it is desirable to see colors. This is done by two conversion formulas.
The first one results in values in the rgb-scale, depending on number of iterations. The second one converts them into hexadecimal numbers, used to color the plot.

