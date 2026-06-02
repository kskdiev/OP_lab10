import ctypes
import os
import sys

# Определение путей и загрузка библиотеки
lib_path = os.path.join(os.path.dirname(__file__), "..", "build", "librect.so")
if not os.path.exists(lib_path):
    print(f"Библиотека не найдена: {lib_path}")
    sys.exit(1)

lib = ctypes.CDLL(lib_path)

# --- Описание структур данных ---
class Point(ctypes.Structure):
    _fields_ = [("x", ctypes.c_double),
                ("y", ctypes.c_double)]

class Rect(ctypes.Structure):
    _fields_ = [("top_left", Point),
                ("width", ctypes.c_double),
                ("height", ctypes.c_double)]

# --- Настройка сигнатур (argtypes, restype) ---
# rect_error_t rect_area(const rect_t *rect, double *area);
lib.rect_area.argtypes = [ctypes.POINTER(Rect), ctypes.POINTER(ctypes.c_double)]
lib.rect_area.restype = ctypes.c_int

# rect_error_t rect_perimeter(const rect_t *rect, double *perimeter);
lib.rect_perimeter.argtypes = [ctypes.POINTER(Rect), ctypes.POINTER(ctypes.c_double)]
lib.rect_perimeter.restype = ctypes.c_int

# rect_error_t rect_contains_point(const rect_t *rect, const point_t *pt, bool *is_inside);
lib.rect_contains_point.argtypes = [ctypes.POINTER(Rect), ctypes.POINTER(Point), ctypes.POINTER(ctypes.c_bool)]
lib.rect_contains_point.restype = ctypes.c_int

# rect_error_t rect_intersect(const rect_t *rect1, const rect_t *rect2, bool *intersect);
lib.rect_intersect.argtypes = [ctypes.POINTER(Rect), ctypes.POINTER(Rect), ctypes.POINTER(ctypes.c_bool)]
lib.rect_intersect.restype = ctypes.c_int

def main():
    print("--- Запуск Python ctypes тестов ---")
    failures = 0
    
    r1 = Rect(Point(0.0, 0.0), 10.0, 5.0)
    r2 = Rect(Point(5.0, -2.0), 10.0, 10.0)
    pt = Point(5.0, 2.0)
    
    area = ctypes.c_double()
    if lib.rect_area(ctypes.byref(r1), ctypes.byref(area)) == 0:
        if area.value == 50.0:
            print("PASS: Площадь вычислена верно")
        else:
            print(f"FAIL: Площадь неверна ({area.value})")
            failures += 1
            
    perim = ctypes.c_double()
    if lib.rect_perimeter(ctypes.byref(r1), ctypes.byref(perim)) == 0:
        if perim.value == 30.0:
            print("PASS: Периметр вычислен верно")
        else:
            print(f"FAIL: Периметр неверен ({perim.value})")
            failures += 1
            
    is_inside = ctypes.c_bool()
    if lib.rect_contains_point(ctypes.byref(r1), ctypes.byref(pt), ctypes.byref(is_inside)) == 0:
        if is_inside.value:
            print("PASS: Точка корректно найдена внутри прямоугольника")
        else:
            print("FAIL: Ошибка принадлежности точки")
            failures += 1
            
    intersect = ctypes.c_bool()
    if lib.rect_intersect(ctypes.byref(r1), ctypes.byref(r2), ctypes.byref(intersect)) == 0:
        if intersect.value:
            print("PASS: Прямоугольники корректно пересекаются")
        else:
            print("FAIL: Ошибка пересечения прямоугольников")
            failures += 1

    if failures > 0:
        print(f"\n[ОШИБКА] Провалено Python-тестов: {failures}")
        sys.exit(1)
        
    print("\n[УСПЕХ] Все Python-тесты пройдены!")

if __name__ == "__main__":
    main()
