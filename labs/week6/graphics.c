#include <stdio.h>

//this program defines and initializes a structure 
//whose members are also structures.
//the content of the structure is then printed
//on screen using four different methods
//for referring to the structure's memebers

struct point{
   int x1;
   int x2;
};
struct rectangle{
   struct point x;
   struct point y;
};

int main(){
        struct point pt1 = {0, 0};
        struct point pt2 = {1, 1};
        struct rectangle r = {pt1, pt2};
        struct rectangle *pr = &r;
        printf("%d,%d\n", r.x.x1, (*pr).x.x2);
        printf("%d,%d\n", (pr->y).x1, (&(pr->y))->x2);
}




