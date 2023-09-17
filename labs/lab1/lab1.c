#include <math.h>
#include <string.h>
#include "lab1.h"

// part one
double split_bill(double base_amount, double tax_rate, double tip_rate, int num_people){
    double total_bill_amount = base_amount * (1+tax_rate) * (1+tip_rate);
    double result = total_bill_amount / num_people;
    result = (ceilf(result * 100)) /100;
    return result;
}

// part two
double adjust_price(double original_price) {
    double adjust_price = 10 * pow(original_price,0.5);
    return adjust_price;
}

// part three
int sandy_eats(char menu_item []){
    if (strlen(menu_item)%2 == 1){
        return 0;
    }
    char s1[] = "fish";
    char s2[] = "J";
    char s3[] = "K";
    char s4[] = "L";
    char s5[] = "j";
    char s6[] = "k";
    char s7[] = "l";
    char* p1, p2, p3, p4, p5, p6, p7;
    p1 = strstr(menu_item,s1);
    p2 = strstr(menu_item,s2);
    p3 = strstr(menu_item,s3);
    p4 = strstr(menu_item,s4);
    p5 = strstr(menu_item,s5);
    p6 = strstr(menu_item,s6);
    p7 = strstr(menu_item,s7);
    if (p1){
        return 0;
    }
    if (p2){
        return 0;
    }
    if (p3){
        return 0;
    }
    if (p4){
        return 0;
    }
    if (p5){
        return 0;
    }
    if (p6){
        return 0;
    }
    if (p7){
        return 0;
    }
    return 1;
}

// part four
void imagine_fish(char thing []){
    char fish[] = "fish";
    strcat(thing,fish);
}