#include "../include/rect.h"

/* Вспомогательная функция для проверки валидности прямоугольника */
static bool is_valid_rect(const rect_t *rect) {
    if (!rect) return false;
    if (rect->width < 0 || rect->height < 0) return false;
    return true;
}

/* Вспомогательная скрытая функция для проверки пересечения отрезков (касание = пересечение) */
static bool overlap_1d(double min1, double max1, double min2, double max2) {
    return (min1 <= max2) && (max1 >= min2);
}

rect_error_t rect_area(const rect_t *rect, double *area) {
    if (!rect || !area) return RECT_ERR_NULL_PTR;
    if (!is_valid_rect(rect)) return RECT_ERR_INVALID_DIM;
    *area = rect->width * rect->height;
    return RECT_SUCCESS;
}

rect_error_t rect_perimeter(const rect_t *rect, double *perimeter) {
    if (!rect || !perimeter) return RECT_ERR_NULL_PTR;
    if (!is_valid_rect(rect)) return RECT_ERR_INVALID_DIM;
    *perimeter = 2.0 * (rect->width + rect->height);
    return RECT_SUCCESS;
}

rect_error_t rect_contains_point(const rect_t *rect, const point_t *pt, bool *is_inside) {
    if (!rect || !pt || !is_inside) return RECT_ERR_NULL_PTR;
    if (!is_valid_rect(rect)) return RECT_ERR_INVALID_DIM;
    
    /* Включаем границы: касание границы считается принадлежностью */
    bool in_x = (pt->x >= rect->top_left.x) && (pt->x <= rect->top_left.x + rect->width);
    bool in_y = (pt->y >= rect->top_left.y) && (pt->y <= rect->top_left.y + rect->height);
    
    *is_inside = in_x && in_y;
    return RECT_SUCCESS;
}

rect_error_t rect_intersect(const rect_t *rect1, const rect_t *rect2, bool *intersect) {
    if (!rect1 || !rect2 || !intersect) return RECT_ERR_NULL_PTR;
    if (!is_valid_rect(rect1) || !is_valid_rect(rect2)) return RECT_ERR_INVALID_DIM;
    
    /* Используем скрытую функцию overlap_1d для осей X и Y */
    bool x_int = overlap_1d(rect1->top_left.x, rect1->top_left.x + rect1->width,
                            rect2->top_left.x, rect2->top_left.x + rect2->width);
    bool y_int = overlap_1d(rect1->top_left.y, rect1->top_left.y + rect1->height,
                            rect2->top_left.y, rect2->top_left.y + rect2->height);
    
    *intersect = x_int && y_int;
    return RECT_SUCCESS;
}
