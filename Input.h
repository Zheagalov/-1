#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <istream>

// Функции ввода данных с клавиатуры с проверкой
int readInt(const std::string& prompt, int minVal, int maxVal);
std::string readLine(const std::string& prompt);
std::string readYears(const std::string& prompt);
bool readYesNo(const std::string& prompt);
// Чтение строки из файла, при конце файла выбрасывает исключение
std::string readFileLine(std::istream& in);

#endif
