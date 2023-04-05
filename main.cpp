/**
\file main.cpp
\brief Модернизация чата. Хранение логина и кэша пароль в хэш-таблице
*/

#include "Chat/Chat.h"
#include "HashTable/HashTable.h"



int main(int argc, char** argv)
{
  try {
    hash_table::runTest();
    chat::runTest();
  }
  catch (const std::out_of_range& error) {
    std::cerr << "Out_of_range error: " << error.what() << std::endl;
  }
  catch (const std::exception& error) {
    std::cerr << error.what() << std::endl;
  }
  catch (...) {
    std::cerr << "Undefined exception" << std::endl;
  }

  return EXIT_SUCCESS;
}