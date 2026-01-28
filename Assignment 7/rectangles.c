
#include <stdio.h>
#include "../prog1lib/lib/base.h"

typedef struct draw_options_s {
    bool has_border;
    String fill_pattern;
} DrawOptions;

typedef struct rectangle_s {

    // todo
    int width;
    int height;
    int x_Coordinate;
    int y_Coordinate;

} Rectangle;

/* Gibt ein DrawOptions Struct zurück, das dafür sorgt dass Rechtecke nur durch
 * Rauten und ohne Rahmen skizziert werden.
 */
DrawOptions make_draw_options_flat() {
    return (DrawOptions){
        .has_border = false,
        .fill_pattern = "#",
    };
}

DrawOptions makeDrawOptionsflat() {
    DrawOptions draw;
    draw.has_border = false;
    draw.fill_pattern = "#";
    return draw;
}

/* Gibt ein DrawOptions Struct zurück, das dafür sorgt dass Rechtecke mit einem
 * Rahmen skizziert werden. Die Füllung des Rechtecks wird durch den String
 * "fill" bestimmt, der ständig wiederholend in das Rechteck geschrieben wird.
 */
DrawOptions make_draw_options_fill(String fill) {
    require("fill is a non-empty string", s_length(fill) > 0);

    return (DrawOptions){
        .has_border = true,
        .fill_pattern = fill,
    };
}

DrawOptions make_draw_options_range(char from, char to) {

    // todo
    require("Characters must be in [32,126]", from >= 32 && to <= 126);
    require("from must be less than to", from < to);

}

Rectangle make_rectangle(int x, int y, int w, int h) {

    // todo

    require("Value of height can't be neagtive", h >= 0);
    require("Value of width can't be neagtive", w >= 0);
    require("Values of x or y coords can't be neagtive", x >= 0 || y >= 0);
    Rectangle rectangle;
    rectangle.x_Coordinate = x;
    rectangle.y_Coordinate = y;
    rectangle.height = h;
    rectangle.width = w;
    return rectangle;
    
}

bool intersects(Rectangle a, Rectangle b) {

    // todo

    if (a.x_Coordinate + a.width <= b.x_Coordinate) return false; // Rectangle A is entirely to the left of B.
    if (b.x_Coordinate + b.width <= a.x_Coordinate) return false; // Rectangle B is entirely to the left of A (A is to the right of B).
    if (a.y_Coordinate + a.height <= b.y_Coordinate) return false; // Rectangle A is entirely below B.
    if (b.y_Coordinate + b.height <= a.y_Coordinate) return false; // Rectangle B is entirely below A (A is above B).

    return true;
}

void print_rectangle(Rectangle rect, DrawOptions options) {

    // todo

    int x = rect.x_Coordinate;
    int y = rect.y_Coordinate;
    int w = rect.width;
    int h = rect.height;
    String fill = options.fill_pattern;

    for (int i = 0; i < y; i++)
        printf("\n");
    
    
    for (int row = 2; row < h+2; row++){
        for (int i = 0; i < x; i++)
            printf(" ");

        if (options.has_border) {
            if (row == 2 || row == h + 1) {
                printf("+");
                for (int i = 0; i < w - 2; i++)
                    printf("-");

                if (w > 1)
                    printf("+");

                printf("\n");
                
               
            } else {
                printf("|");
                
                for (int col = 0; col < w-2; col++)
                {
                    int idx = (row * (w - 2) + col) % s_length(fill);
                    printc(fill[idx]);
                }
                if (w > 1)
                    printf("|");
                printf("\n");
            }
        }
        else {
            for (int col = 0; col < w; col++)
                printf(fill);
            printf("\n");
        }     
    }
}

void test_intersects(void) {
    test_equal_i(intersects(
        make_rectangle(0, 0, 10, 10),
        make_rectangle(32, 32, 10, 10)
    ), false);

    test_equal_i(intersects(
        make_rectangle(100, 100, 32, 16),
        make_rectangle(50, 32, 50, 10)
    ), false);

    test_equal_i(intersects(
        make_rectangle(50, 32, 50, 10),
        make_rectangle(100, 100, 32, 16)
    ), false);

    test_equal_i(intersects(
        make_rectangle(16, 16, 16, 16),
        make_rectangle(16, 16, 4, 4)
    ), true);

    test_equal_i(intersects(
        make_rectangle(16, 16, 16, 16),
        make_rectangle(8, 20, 32, 4)
    ), true);

    test_equal_i(intersects(
        make_rectangle(16, 16, 16, 16),
        make_rectangle(20, 8, 4, 32)
    ), true);
}

int main(void) {
    test_intersects();

    print_rectangle(make_rectangle(0, 0, 9, 5), make_draw_options_fill(" "));
    puts("===");
    print_rectangle(make_rectangle(3, 3, 10, 5), make_draw_options_fill("123"));
    puts("===");
    print_rectangle(make_rectangle(5, 2, 4, 6), make_draw_options_fill(":_:"));
    puts("===");
    print_rectangle(make_rectangle(1, 2, 4, 4), make_draw_options_flat());

    return 0;
}

/* Beispielausgaben:

print_rectangle(make_rectangle(0, 0, 9, 5), make_draw_options_fill(" "));
+-------+
|       |
|       |
|       |
+-------+

print_rectangle(make_rectangle(3, 3, 10, 5), make_draw_options_fill("123"));



   +--------+
   |12312312|
   |31231231|
   |23123123|
   +--------+

print_rectangle(make_rectangle(5, 2, 4, 6), make_draw_options_fill(":_:"));


     +--+
     |:_|
     |::|
     |_:|
     |:_|
     +--+

print_rectangle(make_rectangle(1, 2, 4, 4), make_draw_options_flat());


 ####
 ####
 ####
 ####

*/
