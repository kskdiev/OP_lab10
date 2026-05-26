/**
 * @file rect.h
 * @brief Публичный интерфейс библиотеки для работы с прямоугольниками
 */
#ifndef RECT_H
#define RECT_H

#include <stdbool.h>
#include <stddef.h>

/** @brief Коды возврата функций библиотеки */
typedef enum {
    RECT_SUCCESS = 0,         /**< Успешное выполнение */
    RECT_ERR_NULL_PTR = -1,   /**< Ошибка: передан NULL-указатель */
    RECT_ERR_INVALID_DIM = -2 /**< Ошибка: недопустимые размеры (отрицательные ширина/высота) */
} rect_error_t;

/** @brief Точка на плоскости */
typedef struct {
    double x; /**< Координата X */
    double y; /**< Координата Y */
} point_t;

/** @brief Прямоугольник (задается левым верхним углом, шириной и высотой) */
typedef struct {
    point_t top_left; /**< Левый верхний угол */
    double width;     /**< Ширина прямоугольника */
    double height;    /**< Высота прямоугольника */
} rect_t;

/**
 * @brief Вычисляет площадь прямоугольника
 * @param rect Указатель на прямоугольник
 * @param area Указатель для сохранения площади
 * @return rect_error_t Код ошибки (RECT_SUCCESS при успехе)
 */
rect_error_t rect_area(const rect_t *rect, double *area);

/**
 * @brief Вычисляет периметр прямоугольника
 * @param rect Указатель на прямоугольник
 * @param perimeter Указатель для сохранения периметра
 * @return rect_error_t Код ошибки
 */
rect_error_t rect_perimeter(const rect_t *rect, double *perimeter);

/**
 * @brief Проверяет принадлежность точки прямоугольнику
 * @param rect Указатель на прямоугольник
 * @param pt Указатель на точку
 * @param is_inside Указатель для сохранения результата (true, если внутри или на границе)
 * @return rect_error_t Код ошибки
 */
rect_error_t rect_contains_point(const rect_t *rect, const point_t *pt, bool *is_inside);

/**
 * @brief Проверяет пересечение двух прямоугольников
 * @param rect1 Указатель на первый прямоугольник
 * @param rect2 Указатель на второй прямоугольник
 * @param intersect Указатель для сохранения результата (true, если пересекаются)
 * @return rect_error_t Код ошибки
 */
rect_error_t rect_intersect(const rect_t *rect1, const rect_t *rect2, bool *intersect);

#endif /* RECT_H */
