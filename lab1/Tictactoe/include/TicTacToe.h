/**
 * @file TicTacToe.h
 * @brief Класс игры «Крестики-нолики».
 * @author Сусло Павел
 * @date 2026
 */

#pragma once
#include <iostream>
/**
 * @brief Значение клетки на доске.
 */

enum class Cell {
    Empty,///< Пустая клетка
    X,///< Крестик
    O///< Нолик
};
/**
 * @brief Игра «Крестики-нолики» для двух игроков на поле N×N.
 *
 * Класс полностью инкапсулирует состояние игры: доску, размер поля.
 * Внешний код не имеет доступа к массиву cells_ напрямую — только
 * через методы Get/Set/CanPlace.
 */

class Board {
public:
     /**
     * @brief Создать пустое поле размера @p size.
     * @param size Размер стороны поля (не меньше 1).
     */
    explicit Board(int size);
    /**
     * @brief Конструктор копирования.
     * @param other Объект, с которого делается копия.
     */
    Board(const Board& other);
    /**
     * @brief Оператор присваивания копированием.
     * @param other Объект, из которого копируются данные.
     * @return Ссылка на текущий объект.
     */
    Board& operator=(const Board& other);
    /// Деструктор. Освобождает динамическую память.
    ~Board();
    /**
     * @brief Получить размер стороны поля.
     * @return Размер поля.
     */

    int Size() const;
     /**
     * @brief Получить значение клетки.
     * @param row Строка (0-based).
     * @param col Столбец (0-based).
     * @return Значение клетки.
     */
    Cell Get(int row, int col) const;
    /**
     * @brief Установить значение клетки.
     * @param row Строка (0-based).
     * @param col Столбец (0-based).
     * @param value Новое значение.
     */
    void Set(int row, int col, Cell value);
    /**
     * @brief Проверить, можно ли поставить знак в клетку.
     * @param row Строка.
     * @param col Столбец.
     * @return true, если клетка в границах и пуста.
     */
    bool CanPlace(int row, int col) const;
    /**
     * @brief Проверить, собрал ли игрок линию.
     * @param player Знак игрока (X или O).
     * @return true, если есть линия из 3+ знаков.
     */
    bool HasWinner(Cell player) const;
    /**
     * @brief Проверить, заполнено ли поле полностью.
     * @return true, если все клетки заняты.
     */
    bool IsFull() const;
    /**
     * @brief Сравнение на равенство.
     * @param other Другой объект.
     * @return true, если размеры и все клетки совпадают.
     */

    bool operator==(const Board& other) const;
    /**
     * @brief Сравнение на неравенство.
     * @param other Другой объект.
     * @return true, если объекты различаются.
     */
    bool operator!=(const Board& other) const;
    /**
     * @brief Доступ к строке доски.
     * @param row Номер строки.
     * @return Указатель на начало строки.
     */

    Cell* operator[](int row);
    /// Константная версия operator[].
    const Cell* operator[](int row) const;

private:
    int size_;///< Размер стороны поля
    Cell* cells_;///< Динамический массив клеток size_ × size_
};

/**
 * @brief Записать доску в поток.
 * @param os Поток вывода.
 * @param board Доска.
 * @return Ссылка на поток.
 */
std::ostream& operator<<(std::ostream& os, const Board& board);

/**
 * @brief Прочитать доску из потока.
 * @param is Поток ввода.
 * @param board Доска.
 * @return Ссылка на поток.
 */
std::istream& operator>>(std::istream& is, Board& board);

