#include <stdio.h>
#include "../include/rect.h"

int main(void) {
    rect_t r1 = {{0.0, 0.0}, 10.0, 5.0};
    rect_t r2 = {{5.0, -2.0}, 10.0, 10.0};
    double area, perim;
    bool res;

    printf("=== Демонстрация библиотеки rect ===\n");

    if (rect_area(&r1, &area) == RECT_SUCCESS) {
        printf("Площадь r1: %.2f\n", area);
    }

    if (rect_perimeter(&r1, &perim) == RECT_SUCCESS) {
        printf("Периметр r1: %.2f\n", perim);
    }

    point_t pt = {5.0, 2.0};
    if (rect_contains_point(&r1, &pt, &res) == RECT_SUCCESS) {
        printf("Точка (5.0, 2.0) %s в r1\n", res ? "внутри" : "снаружи");
    }

    if (rect_intersect(&r1, &r2, &res) == RECT_SUCCESS) {
        printf("Прямоугольники r1 и r2 %s\n", res ? "пересекаются" : "не пересекаются");
    }

    return 0;
}
