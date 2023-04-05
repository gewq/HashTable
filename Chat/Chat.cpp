#include "Chat.h"

#include <iostream>
#include <algorithm>
#include <assert.h>

#include "../Exceptions/EmptyString_Exception/EmptyString_Exception.h"
#include "../Exceptions/LoginTooLong_Exception/LoginTooLong_Exception.h"


namespace {
  //Максимальная длина логина пользователя
  const uint8_t MAX_LOGIN_LENGTH = 10;
}


Chat::Chat()
{
}



void Chat::addUser(const std::string& login, const std::string& password)
{
  //Логин или Пароль не введён
  if (login.empty() || password.empty())  {
    throw EmptyString_Exception();
  }
  //Длина логина больше MAX_LOGIN_LENGTH
  if (login.size() > MAX_LOGIN_LENGTH) {
    throw LoginTooLong_Exception(login, MAX_LOGIN_LENGTH);
  }

  //Пользователь с таким логином уже есть
  if (users_.isExist(login)) {
    return;	//Ничего не делать
  }

  //Добавить в данные пользователя в хэш-таблицу
  users_.add(login, hash(password));
}



bool Chat::login(const std::string& login, const std::string& password) const
{
  //Логин или Пароль не введён
  if (login.empty() || password.empty())  {
    throw EmptyString_Exception();
  }
  //Длина логина больше MAX_LOGIN_LENGTH
  if (login.size() > MAX_LOGIN_LENGTH) {
    throw LoginTooLong_Exception(login, MAX_LOGIN_LENGTH);
  }

  //Пользователь с таким логином не зарегистрирован
  if (!users_.isExist(login)) {
    return false;
  }

  size_t hashInputPassword = hash(password);
  size_t hashUserPassword = users_.getHashPassword(login);

  //Пароль верный
  if (hashInputPassword == hashUserPassword) {
    return true;
  }

  return false;
}



//-------------------------------------------------------------------------
size_t Chat::hash(const std::string& password) const
{
  size_t summa = 0;	//Сумма кодов ASCII строки
  std::for_each(password.begin(), password.end(), [&summa](char symbol) {
    summa += symbol;
  });

  const double A = 0.79;
  const int M = 10;
  return static_cast<size_t>(M * (A*summa));
}



//=========================================================================
void chat::runTest()
{
  Chat chat;

  const size_t TEST_SIZE = 6;
  std::array<std::string, TEST_SIZE> testLogins = {
    "login_1",
    "login_2",
    "login_3",
    "login_4",
    "login_5",
    "login_6",
  };
  std::array<std::string, TEST_SIZE> testPasswords = {
    "asfdj",
    "fsdk",
    "14532twefsdas",
    "sadvas",
    "passwordafds_5",
    "badfksa",
  };

  for (size_t i=0; i<testLogins.size(); ++i) {
    chat.addUser(testLogins.at(i), testPasswords.at(i));
  }

  for (size_t i=0; i<testLogins.size(); ++i) {
    assert(chat.login(testLogins.at(i), testPasswords.at(i)) == true);
  }

  assert(chat.login("notExisted", "dsg") == false);
  assert(chat.login(testLogins.at(0), "incorrectPassword") == false);
  assert(chat.login(testLogins.at(0), testPasswords.at(1)) == false);

  //Тест выброс исключения
//  chat.addUser("", password);	//Login is empty
//  chat.addUser(login, "");		//Password is empty
//  chat.addUser("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", password);	//Login too long
}