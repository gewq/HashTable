/**
\file Chat.h
\brief Класс Чат. Содержит список пользователей и их количество

Содержит методы:
- регистрации нового пользователя
- входа зарегистрированного пользователя
При регистрации нового пользователя сохраняется кэш пароля.
При входе проверяется совпадение хэшей введённого пароля и
хранимого в объекте класса Chat
*/

#pragma once

#include <string>
#include <array>

#include "../HashTable/HashTable.h"



class Chat {
  public:
    Chat();

    /**
    Зарегистрировать нового пользователя
    \param[in] login Логин пользователя
    \param[in] password Пароль пользователя
    */
    void addUser(const std::string& login, const std::string& password);

    /**
    Проверить зарегистрирован ли пользователь
    \param[in] login Логин пользователя
    \param[in] password Пароль пользователя
    \return Признак того, что логин и пароль соответствуют зарегистрированному пользователю
    */
    bool login(const std::string& login, const std::string& password) const;

  private:
    /**
    Вычислить хэш пароля
    \param[in] password Пароль пользователя
    \return Хэш пароля
    */
    size_t hash(const std::string& password) const;
    
    HashTable users_;	///<Хэш таблица пользователей (логин - хэш пароля)
};



namespace chat {
  void runTest();
}