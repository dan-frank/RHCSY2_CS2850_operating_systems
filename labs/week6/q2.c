//
// Created by Daniel Lucas on 10/11/2020.
//

#include <stdio.h>
struct point{
    int x;
    int y;
};
int distanceSquared(struct point *pt1, struct point *pt2){
    int d1 = (pt2->x - pt1->x);
    d1 *= d1;
    int d2 = (pt2->y - pt1->y);
    d2 *= d2;
    return d1 + d2;
}
int main(){
    struct point pt1;
    struct point *pt2;
    (&pt1)->x = 2;
    (*(&pt1)).y = 0;
    pt2->x = 2;
    (*pt2).y = 3;
    printf("%d\n", distanceSquared(&pt1, pt2));
    return 0;
}