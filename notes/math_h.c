#include <stdio.h>
#include <math.h>

int main(){
    float x = sqrt(10);
    printf("%d\n",(int)x);
    // printf("%d",x);      warning, with output of garbage value
    printf("%f\n",x);


    int y = round(3.5);
    printf("%d\n",y);

    int z = floor(3.14);
    int h = ceil(3.14);

    int m = fabs(-100);
    printf("%d\n",m);

    float log_3 = log(3);   //use e as base
    printf("%f\n",log_3);

    float k = sin(3);
    printf("%f",k);
    return 0;
}