/**
\file LoginTooLong_Exception.h
\brief Класс LoginTooLong_Exception - для обработки исключения "Логин слишком длинный"

Класс LoginTooLong_Exception наследует у класса std::exception и перегружает метод what()
*/

#pragma once

#include <string>
#include <exception>


class LoginTooLong_Exception : public std::exception {
	public:
    /**
    Исключение получает на вход строку об ошибке -
    конструктор по-умолчанию не имеет смысла
    */
    LoginTooLong_Exception() = delete;

    /**
    Параметризованный конструктор.
    \param[in] login Логин
    \param[in] maxLength Максимальная длина логина
    */
    explicit LoginTooLong_Exception(const std::string& login, size_t maxLength);

    /**
    Перегруженный метод базового класса std::exception
    \return Указатель на сообщение об ошибке
    */
    virtual const char* what() const noexcept override;

  private:
    std::string errorMessage_;	///<Сообщение об ошибке
};