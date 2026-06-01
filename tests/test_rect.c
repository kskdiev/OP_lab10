#include <stdio.h>
#include <stdbool.h>
#include "../include/rect.h"

int failures = 0;

void check(bool cond, const char* msg) {
    if (!cond) {
        printf("FAIL: %s\n", msg);
        failures++;
    } else {
        printf("PASS: %s\n", msg);
    }
}

void test_invalid(void) {
    printf("\n--- Тесты невалидных данных ---\n");
    rect_t r = {{0.0, 0.0}, 10.0, 10.0};
    double val;
    check(rect_area(NULL, &val) == RECT_ERR_NULL_PTR, "Площадь с NULL-указателем прямоугольника");
    check(rect_area(&r, NULL) == RECT_ERR_NULL_PTR, "Площадь с NULL-указателем для результата");
    
    rect_t r_bad = {{0.0, 0.0}, -5.0, 10.0};
    check(rect_area(&r_bad, &val) == RECT_ERR_INVALID_DIM, "Обработка отрицательной ширины");
}

void test_boundary(void) {
    printf("\n--- Тесты граничных условий ---\n");
    rect_t r_zero = {{0.0, 0.0}, 0.0, 0.0};
    double val;
    check(rect_area(&r_zero, &val) == RECT_SUCCESS && val == 0.0, "Площадь вырожденного прямоугольника (0x0)");
    
    rect_t r1 = {{0.0, 0.0}, 10.0, 10.0};
    point_t p_edge = {10.0, 5.0};
    bool res;
    check(rect_contains_point(&r1, &p_edge, &res) == RECT_SUCCESS && res == true, "Точка на границе принадлежит прямоугольнику");
    
    rect_t r2 = {{10.0, 0.0}, 10.0, 10.0};
    check(rect_intersect(&r1, &r2, &res) == RECT_SUCCESS && res == true, "Касание прямоугольников (по границе) считается пересечением");
}

void test_typical(void) {
    printf("\n--- Тесты типичных сценариев ---\n");
    rect_t r1 = {{0.0, 0.0}, 10.0, 5.0};
    double val;
    check(rect_area(&r1, &val) == RECT_SUCCESS && val == 50.0, "Корректное вычисление площади");
    check(rect_perimeter(&r1, &val) == RECT_SUCCESS && val == 30.0, "Корректное вычисление периметра");
    
    rect_t r2 = {{2.0, 2.0}, 10.0, 10.0};
    bool res;
    check(rect_intersect(&r1, &r2, &res) == RECT_SUCCESS && res == true, "Пересекающиеся прямоугольники");
    
    rect_t r3 = {{20.0, 20.0}, 5.0, 5.0};
    check(rect_intersect(&r1, &r3, &res) == RECT_SUCCESS && res == false, "Непересекающиеся прямоугольники");
}

int main(void) {
    test_invalid();
    test_boundary();
    test_typical();
    
    if (failures > 0) {
        printf("\n[ОШИБКА] Провалено тестов: %d\n", failures);
        return 1;
    }
    printf("\n[УСПЕХ] Все C-тесты успешно пройдены!\n");
    return 0;
}
