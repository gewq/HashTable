/**
\file HashTable.h
\brief Класс Хэш-таблица (Закрытое хэширование). Содержит пару Ключ-Значение

Ключ - логин пользователя
Значение - хэш пароля пользователя
*/

#pragma once

#include <iostream>
#include <vector>


class HashTable {
  public:
    HashTable();

    ~HashTable();

    /**
    Добавить в таблицу пару ключ-значение
    \param[in] login Ключ - логин пользователя
    \param[in] hashPassword Значение - хэш пароля пользователя
    */
    void add(const std::string& login, size_t hashPassword);

    /**
    Удалить из таблицы данные пользователя по логину
    \param[in] login Ключ - логин пользователя
    */
    void remove(const std::string& login);

    /**
    Найти хэш пароля по логину пользователя.
    Если логин не найден - вернёт 0
    \param[in] login Логин пользователя
    \return Хэш пароля
    */
    size_t getHashPassword(const std::string& login) const;

    /**
    Проверить есть ли в таблице заданный логин
    \param[in] login Логин
    \return Признак наличия логина в таблице
    */
    bool isExist(const std::string& login) const;

  private:
    //Статус ячейки массива
    enum PairStatus {
      free, 		///<Свободна
      engaged,	///<Занята
      deleted		///<Удалена
    };

    //Пара ключ-значение
    struct Pair {
      std::string login_;		///<Ключ
      size_t hashPassword_;	///<Значение
      PairStatus status_; 	///<Cостояние ячейки

      Pair():
        login_(""),
        hashPassword_(0),
        status_(PairStatus::free)
      {
      }

      //Конструктор копирования
      Pair(const std::string& login, size_t hashPassword):
        login_(login), hashPassword_(hashPassword),
        status_(PairStatus::engaged)
      {
      }

      //Оператор присваивания
      Pair& operator = (const Pair& other)
      {
        login_ = other.login_;
        hashPassword_ = other.hashPassword_;
        status_ = other.status_;
        return *this;
      }
    };

    /**
    Увеличить размер таблицы
    */
    void resize();

    /**
    Вычислить хэш логина
    \param[in] login Логин пользователя
    \param[in] offset Смещение
    \return Хэш логина
    */
    size_t hash(const std::string& login, int offset) const;

    /**
    Найти индекс массива в котором расположен ключ (логин)
    Если не найдено - вернуть -1
    \param[in] login Логин пользователя
    \return Индекс массива
    */
    int getID(const std::string& login) const;

    /**
    Найти индекс первой свободной ячейки массива в которую можно поместить ключ (логин)
    Если не найдено - вернуть -1
    \param[in] login Логин пользователя
    \return Индекс массива
    */
    int getFirstFreeID(const std::string& login) const;

    std::vector<Pair> data_;	///<Динамический массив пар (ключ-значение)
    size_t nPairs_;	///<Количество добавленных пар ключ-значение
};



namespace hash_table {
  void runTest();
}