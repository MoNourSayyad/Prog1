#include <stdio.h>
#include "../prog1lib/lib/base.h"
#include <stdbool.h>
#include "../prog1lib/lib/basedefs.h"

#define Hi
#ifdef Hi
#define msgprint(cond,message) if (cond) {puts(message);} 
#else
#define msgprint(cond,message)
#endif


char* J(void* x) {
  return "Im J"; 
}

char* Y(void* x) {
  return "Im Y"; 
}

void printSmth(char* (*letter)(void*)) {
   prints(letter((int*) 3));
}
int main(void) {
    
   /* puts("hi");
    printf("hi, again\n");
    bool t = true;
    printf("%d", t);
    char name [100] = "";  
    float n = 10.32;
    printf("%7.1f\n", n);
    char c = getchar();
    printf("You typed: %c\n", c);
    printf("Type ur name: ");
    getchar();
    fgets(name,sizeof(name), stdin);
    name[sizeof(name) -1 ] - '\0';
    printf("%s",name);
   */
/*
    int m =3;
    int x = 1 << m;
    printf("%d\n",x);
    printf("%08x\n",x);
    msgprint(100>10, "hi");

   struct Point {
    int x;
    int y;
};

struct Line {
    struct Point pt1;
    struct Point pt2;
};

/*typedef struct Circle {int x, y, radius;}circle;
typedef struct Rectangle {int x, y, width, height;}rectangle;
typedef enum ShapeTag {CIRCLE, RECTANGLE}shapetag;
typedef struct Shape {
    shapetag tag;
    union {
        circle circle;
        rectangle rectangle;
    };
    
}shape;
    shape s;
    s.tag = CIRCLE;
    s.circle.x = 100;
    s.circle.y = 50;
    s.circle.radius = 50;
     switch (s.tag) {
 case CIRCLE:
 printf("circle: %d %d %d\n", 
s.circle.x , s.circle.y , 
s.circle.radius);
 break;
 case RECTANGLE:
 printf("rectangle: %d %d %d %d\n", 
s.rectangle.x, s.rectangle.y, 
s.rectangle.width, 
s.rectangle.height);
 break;
 }*/

   typedef struct {
 enum { CIRCLE, RECTANGLE } tag;
 union {
 struct { int x, y, radius; } circle;
 struct { int x, y, width, height; } rectangle;
 };
 }Shape;
// printi(i_of_s("23"));
/*
printiln((int)23.5);
char d = 0xff;
printf("%d\n",(signed) d);
//int d;
//d = getchar();
//printi(d);
*/
 /*
 int a[ ] = { 33, 11, 15, 7, -7 };
 printiln(a[0]); // output: 33
 printiln(a[4]); // output: -7
 int i = -1;
 // out of bounds!
 printiln(a[i]); // output: 0 (one left of array)
 i = 5;
 // out of bounds!
 printiln(a[i]); // output: 32767 (one right of array)
 

 char p;
 p = getchar();
 int pop;
// pop = getchar();
printcln(p);
printiln(p);
println();

printi(sizeof(a)/sizeof(a[0]));
assert_code();

typedef struct Point{
    int x, y;
}Point;

Point ptsa[] = {{1,2},{23,42}};
Point (*P)[2] = &ptsa;
Point pts = {1,2};
int *po = (int*) ptsa;
for (int i = 0; i < 4; i++)
{
    printiln(po[i]);
}

*/
/*
char* lol = "hidhsid";
lol = "sd";
printf("%d\n",&lol);
printf("%c\n",*lol);
printf("%s\n",lol);
printf("%d\n",rand());
*/
char line[8];
get_line(line, 8);
int r = line[0] - '1';
printf("%d", r);

printSmth(J);

return 0;


}


