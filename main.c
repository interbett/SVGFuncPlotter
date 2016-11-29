#include <stdio.h>
#include "libSVG.h"
#include <math.h>

#define SIZE 15

#define SVG_HEIGHT 1000
#define SVG_WIDTH  1000

#define X_MIN       -SIZE
#define X_MAX        SIZE
#define Y_MIN       -SIZE
#define Y_MAX        SIZE

#define RES 0.01

//Conversion from SVG to mathematical coordinates
double x_svg2mat(int xSVG) {
	double xMAT;
	xMAT = X_MIN + xSVG *(X_MAX - X_MIN)/SVG_WIDTH;
	return xMAT;
}

double y_svg2mat(int ySVG) {
	double yMAT;
	yMAT = (Y_MIN + ySVG*(Y_MAX - Y_MIN) /SVG_HEIGHT)*(-1);
	return yMAT;
}

//Conversion from mathematical coordinates to SVG
int x_mat2svg(double xMAT) {
	double xSVG;
	int xRet;
	xSVG = (xMAT - X_MIN)*SVG_WIDTH/(X_MAX-X_MIN);
	xRet = (int) xSVG;
	return xRet;
}

int y_mat2svg(double yMAT) {
   double ySVG;
   int yRet;
   ySVG = (Y_MAX - yMAT)*SVG_HEIGHT/(Y_MAX-Y_MIN);
   yRet = (int) ySVG;
   return yRet;
}

int main(void) {
	FILE *svg = svg_create("coordinateSystem.svg", SVG_WIDTH , SVG_HEIGHT);
// Border Rectangle
	svg_rect(svg, 0, 0, SVG_WIDTH, SVG_HEIGHT, "grey", 2, "white");
// X Axis
	svg_line(svg, x_mat2svg(X_MIN), y_mat2svg(0), x_mat2svg(X_MAX), y_mat2svg(0), "black", 2);

// Y Axis
	svg_line(svg, x_mat2svg(0), y_mat2svg(Y_MIN), x_mat2svg(0), y_mat2svg(Y_MAX), "black", 2);

// X Tags
	double x = X_MIN + 1;
	int    ix;

  while(x <= (X_MAX - 1)) {
	ix = (int) x;
	if (ix != 0) {
		svg_line(svg, x_mat2svg(x), y_mat2svg(-0.2), x_mat2svg(x), y_mat2svg(0.2), "black", 1);
		svg_number_as_text(svg,x_mat2svg(x-0.2), y_mat2svg(-0.5),"black",10 ,"",ix);
   }
   x = x + 1;
  }

// Y Tags
  double y = Y_MIN + 1;
  int    iy;

  while(y <= (Y_MAX - 1)) {
    iy = (int) y;
   if (iy!= 0) {
       svg_line(svg, x_mat2svg(-0.2), y_mat2svg(y), x_mat2svg(0.2), y_mat2svg(y), "black", 1);
      svg_number_as_text(svg,x_mat2svg(0.3), y_mat2svg(y-0.2),"black",10 ,"",iy);
        }
   y = y + 1;
  }

// Arrows
   svg_line(svg, x_mat2svg(X_MAX-0.3), y_mat2svg(0+0.3), x_mat2svg(X_MAX), y_mat2svg(0), "black", 1);
   svg_line(svg, x_mat2svg(X_MAX-0.3), y_mat2svg(0-0.3), x_mat2svg(X_MAX), y_mat2svg(0), "black", 1);
   svg_line(svg, x_mat2svg(0+0.3), y_mat2svg(Y_MAX-0.3), x_mat2svg(0), y_mat2svg(Y_MAX), "black", 1);
   svg_line(svg, x_mat2svg(0-0.3), y_mat2svg(Y_MAX-0.3), x_mat2svg(0), y_mat2svg(Y_MAX), "black", 1);

// Function drawer
	double last_x,last_y;
	int first = 1;
	x = X_MIN;
	while(x <= X_MAX) {
  
		//	y = x;
		//	y = sin(x);
		//	y=pow(x,2);
		//	y=-pow(x,2);
			y = tan(x);

		if (y < Y_MIN) {
			y = Y_MIN;
			first = 1;
		}
		if (y > Y_MAX) {
			y = Y_MAX;
		}
    	if (first != 1)  {
			svg_line(svg, x_mat2svg(last_x), y_mat2svg(last_y), x_mat2svg(x), y_mat2svg(y), "red", 2);
		}
		last_x = x;
		last_y = y;   
		first = 0;
		if  (y == Y_MAX) {
    		first = 1;
    	}
    	x = x + RES;
	}
   svg_finish(svg); // Closes the picture
  return 0;
}