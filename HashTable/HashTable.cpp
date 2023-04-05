#include "HashTable.h"

#include <algorithm>
#include <assert.h>
#include <array>
#include <numeric>

HashTable::HashTable()
{
  nPairs_ = 0;
  data_.reserve(4);
  //Заполнить вектор начальными значениями
  for(size_t i=0; i < data_.capacity(); ++i) {
    data_.push_back(Pair());
  }
}



HashTable::~HashTable()
{

}



//Добавить пару ключ-значение в таблицу
void HashTable::add(const std::string& login, size_t hashPassword)
{
  int id = getFirstFreeID(login);

  //Нет свободной ячейки
  if (id == -1) {
    resize();
    add(login, hashPassword);
  }
  //Есть свободная ячейка
  else {
    //Поместить пару в свободную ячейку
    data_.at(id) = Pair(login, hashPassword);
    ++nPairs_;
  }
}



void HashTable::remove(const std::string& login)
{
  int id = getID(login);
  //Элемента нет
  if (id == -1) {
    return;
  }
  data_.at(id).status_ = deleted;
}



size_t HashTable::getHashPassword(const std::string& login) const
{
  int id = getID(login);
  //Элемента нет
  if (id == -1) {
    return 0;
  }

  return data_.at(id).hashPassword_;
}



bool HashTable::isExist(const std::string& login) const
{
  int id = getID(login);
  //Элемента нет
  if (id == -1) {
    return false;
  }
  return true;
}



//-------------------------------------------------------------------------
void HashTable::resize()
{
  //Запомнить текущую таблицу
  std::vector<Pair> oldData = data_;

  data_.reserve(data_.size()*2);	//Увеличить размер

  //Очистить таблицу
  data_.clear();
  nPairs_ = 0;

  //Инициализировать заново таблицу
  for(size_t i=0; i<data_.capacity(); ++i) {
    data_.push_back(Pair());
  }

  //Скопировать данные из старого массива в новый
  for(size_t i=0; i<oldData.size(); ++i) {
    if (oldData.at(i).status_ == engaged) {
      add(oldData.at(i).login_, oldData.at(i).hashPassword_);
    }
  }
}



size_t HashTable::hash(const std::string& login, int offset) const
{
  size_t summa = 0;	//Сумма кодов ASCII строки
  std::for_each(login.begin(), login.end(), [&summa](char symbol) {
    summa += symbol;
  });

  // квадратичные пробы
  return (summa % data_.capacity() + offset*offset) % data_.capacity();
}



int HashTable::getID(const std::string& login) const
{
  //Взять пробы по всем индексам таблицы
  for(size_t i = 0; i < data_.capacity(); ++i) {
    int id = hash(login, i);
    //Найден элемент с таким же логином
    if (data_.at(id).login_ == login) {
      //Ячейка отмечена как занятая
      if (data_.at(id).status_ == PairStatus::engaged) {
        return id;
      }
    }
    //Дошли до свободной ячейки - дальше элементов нет
    if (data_.at(id).status_ == free) {
      break;
    }
  }
  return -1;
}



int HashTable::getFirstFreeID(const std::string& login) const
{
  //Взять пробы по всем индексам таблицы
  for(size_t i = 0; i < data_.capacity(); ++i) {
    int id = hash(login, i);
    //Найдена пустая ячейка (незанятая или с удалённым содержимым)
    if ( (data_.at(id).status_ == PairStatus::free) ||
         (data_.at(id).status_ == PairStatus::deleted) ) {
      return id;
    }
  }
  //Нет свободной ячейки
  return -1;
}



//=========================================================================
static void testAdd();
static void testRemove();
static void testIsExist();


void hash_table::runTest()
{
  testAdd();
  testRemove();
  testIsExist();
}



static void testAdd()
{
  HashTable ht;

  const size_t TEST_SIZE = 6;

  std::array<std::string, TEST_SIZE> testLogins = {
    "login_1",
    "login_2",
    "login_3",
    "login_4",
    "login_5",
    "login_6",
  };

  std::array<size_t, TEST_SIZE> testPasswordHashes = {
    1214,
    1224,
    1234,
    1244,
    1254,
    1264,
  };

  for (size_t i=0; i<testLogins.size(); ++i) {
    ht.add(testLogins.at(i), testPasswordHashes.at(i));
    assert(ht.getHashPassword(testLogins.at(i)) == testPasswordHashes.at(i));
  }
}



static void testRemove()
{
  HashTable ht;

  const size_t TEST_SIZE = 6;

  std::array<std::string, TEST_SIZE> testLogins = {
    "login_1",
    "login_2",
    "login_3",
    "login_4",
    "login_5",
    "login_6",
  };

  std::array<size_t, TEST_SIZE> testPasswordHashes = {
    1214,
    1224,
    1234,
    1244,
    1254,
    1264,
  };

  for (size_t i=0; i<testLogins.size(); ++i) {
    ht.add(testLogins.at(i), testPasswordHashes.at(i));
  }

  for (size_t i=0; i<testLogins.size(); ++i) {
    ht.remove(testLogins.at(i));
    assert(ht.getHashPassword(testLogins.at(i)) == 0);
  }

  ht.remove("not exist");	//Удалить несуществующий элемент
}



static void testIsExist()
{
  HashTable ht;

  const size_t TEST_SIZE = 6;

  std::array<std::string, TEST_SIZE> testLogins = {
    "login_1",
    "login_2",
    "login_3",
    "login_4",
    "login_5",
    "login_6",
  };

  std::array<size_t, TEST_SIZE> testPasswordHashes = {
    1214,
    1224,
    1234,
    1244,
    1254,
    1264,
  };

  for (size_t i=0; i<testLogins.size(); ++i) {
    ht.add(testLogins.at(i), testPasswordHashes.at(i));
  }

  for (size_t i=0; i<testLogins.size(); ++i) {
    assert(ht.isExist(testLogins.at(i)) == true);
  }
  assert(ht.isExist("not exist") == false);
}