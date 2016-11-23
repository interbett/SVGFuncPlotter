


#include <stdio.h>
#include "libSVG.h"

int main() {
	int i;
	int N = 11;

	  int svg_size = (N + 1) * 30 * 2;

	  int xAchseX1 = 0;
	  int xAchseX2 = svg_size;
	  int xAchseY = svg_size / 2;

	  int yAchseX = svg_size / 2;
	  int yAchseY1 = 0;
	  int yAchseY2 = svg_size;

  FILE *svg = svg_create("hallo_tutor.svg", svg_size, svg_size);

  svg_rect(svg, 0, 0, ((N+1)*30*2), ((N+1)*30*2), "black", 10, "white");

  svg_line(svg, yAchseX, yAchseY1, yAchseX, yAchseY2, "red", 4);
  svg_line(svg, xAchseX1, xAchseY, xAchseX2, xAchseY, "black", 2);

  svg_line(svg,xAchseX2 - 5, xAchseY + 5, xAchseX2, xAchseY,"balck", 20);
    svg_line(svg,xAchseX2 - 5, xAchseY - 5, xAchseX2, xAchseY,"black", 20);
    printf("<text x=\"%d\" y=\"%d\">x</text>\n", xAchseX2 - 10,
  	 xAchseY + 20);

    for ( i = -N; i <= N; i++) {
        if (i != 0) {
          int j = xAchseX1 + (i + N + 1) * 30;
          svg_line(svg,j, xAchseY + 5, j, xAchseY - 5,"black", 2);
          svg_number_as_text(svg,j - 5, xAchseY + 20,"balck",10 ,"",i);
        }
      }
    svg_line(svg,yAchseX, yAchseY1, yAchseX - 5, yAchseY1 + 5,"black", 20);
      svg_line(svg,yAchseX, yAchseY1, yAchseX + 5, yAchseY1 + 5,"black", 20);
      printf("<text x=\"%d\" y=\"%d\">y</text>\n", yAchseX - 20,
    	 yAchseY1 + 10);
    for ( i = -N; i <= N; i++) {
        if (i != 0) {
          int j = yAchseY2 - (i + N + 1) * 30;
          svg_line(svg,yAchseX + 5, j, yAchseX - 5, j,"balck" ,2);
          svg_number_as_text(svg,yAchseX + 10, j + 5,"black",10,"", i);
        }
      }

  svg_finish(svg);  // Schliesst die Bilderstellung ab

  return 0;
}
