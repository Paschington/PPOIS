/**
 * @file Polynomial.h
 * @brief Класс многочлена от одной переменной с вещественными коэффициентами.
 * @author Сусло Павел
 * @date 2026
 */
#pragma once
#include <iostream>
/**
 * @brief Многочлен от одной переменной.
 *
 * Коэффициенты хранятся от младшего к старшему: coeffs[i] — коэффициент при x^i.
 * Ведущие нули автоматически удаляются методом Trim().
 */

class Polynomial {
public:
/**
     * @brief Создать многочлен по степени и массиву коэффициентов.
     * @param degree Степень многочлена (>= 0).
     * @param coeffs Массив коэффициентов от x^0 до x^degree.
     * @throw std::invalid_argument если degree < 0 или coeffs == nullptr.
     */
    Polynomial(int degree, const double* coeffs);
/// Создать нулевой многочлен.
    Polynomial();
/**
     * @brief Конструктор копирования.
     * @param other Объект, с которого делается копия.
     */
    Polynomial(const Polynomial& other);
/**
     * @brief Оператор присваивания копированием.
     * @param other Объект, из которого копируются данные.
     * @return Ссылка на текущий объект.
     */
    Polynomial& operator=(const Polynomial& other);
 /// Деструктор. Освобождает память массива коэффициентов.
    ~Polynomial();
 /**
     * @brief Получить степень многочлена.
     * @return Степень (0 для нулевого многочлена).
     */

    int Degree() const;
/**
     * @brief Получить коэффициент при x^power.
     * @param power Степень.
     * @return Коэффициент или 0, если power вне диапазона.
     */
    double operator[](int power) const;
/**
     * @brief Вычислить значение многочлена в точке x.
     * @param x Точка.
     * @return Значение многочлена.
     */
    double operator()(double x) const;
/**
     * @brief Прибавить другой многочлен к текущему.
     * @param other Слагаемое.
     * @return Ссылка на текущий объект.
     */
    Polynomial& operator+=(const Polynomial& other);
/**
     * @brief Вычесть другой многочлен из текущего.
     * @param other Вычитаемое.
     * @return Ссылка на текущий объект.
     */
    Polynomial& operator-=(const Polynomial& other);
/**
     * @brief Умножить текущий многочлен на другой.
     * @param other Множитель.
     * @return Ссылка на текущий объект.
     */
    Polynomial& operator*=(const Polynomial& other);
/**
     * @brief Разделить текущий многочлен на другой.
     * @param other Делитель.
     * @return Ссылка на текущий объект (частное).
     * @throw std::invalid_argument если делитель — нулевой многочлен.
     */
    Polynomial& operator/=(const Polynomial& other);
/**
     * @brief Вычислить остаток от деления.
     * @param other Делитель.
     * @return Остаток от деления.
     * @throw std::invalid_argument если делитель — нулевой многочлен.
     */

    Polynomial Remainder(const Polynomial& other) const;
/**
     * @brief Сравнение на равенство (с учётом погрешности).
     * @param other Другой многочлен.
     * @return true, если степени и коэффициенты совпадают.
     */

    bool operator==(const Polynomial& other) const;
/**
     * @brief Сравнение на неравенство.
     * @param other Другой многочлен.
     * @return true, если многочлены различаются.
     */
    bool operator!=(const Polynomial& other) const;

private:
    int degree;///< Степень многочлена
    double* coeffs;///< Массив коэффициентов от x^0 до x^degree
/// Убрать ведущие нулевые коэффициенты и пересчитать степень.
    void Trim();
};
/**
 * @brief Сложение двух многочленов.
 * @param lhs Первый многочлен.
 * @param rhs Второй многочлен.
 * @return Сумма.
 */
Polynomial operator+(Polynomial lhs, const Polynomial& rhs);
/**
 * @brief Вычитание двух многочленов.
 * @param lhs Уменьшаемое.
 * @param rhs Вычитаемое.
 * @return Разность.
 */
Polynomial operator-(Polynomial lhs, const Polynomial& rhs);
/**
 * @brief Умножение двух многочленов.
 * @param lhs Первый множитель.
 * @param rhs Второй множитель.
 * @return Произведение.
 */
Polynomial operator*(Polynomial lhs, const Polynomial& rhs);
/**
 * @brief Деление двух многочленов.
 * @param lhs Делимое.
 * @param rhs Делитель.
 * @return Частное.
 */
Polynomial operator/(Polynomial lhs, const Polynomial& rhs);
/**
 * @brief Записать многочлен в поток.
 * @param os Поток вывода.
 * @param p Многочлен.
 * @return Ссылка на поток.
 */

std::ostream& operator<<(std::ostream& os, const Polynomial& p);
/**
 * @brief Прочитать многочлен из потока.
 * @param is Поток ввода.
 * @param p Многочлен.
 * @return Ссылка на поток.
 */
std::istream& operator>>(std::istream& is, Polynomial& p);