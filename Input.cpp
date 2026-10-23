#include "Input.h"
#include "AppException.h"
#include <iostream>
#include <cctype>

int readInt(const std::string& prompt, int minVal, int maxVal) {
    std::cout << prompt;
    std::string s;
    if (!std::getline(std::cin, s))
        throw AppException("Ошибка: поток ввода закрыт");
    if (s.empty())
        throw AppException("Ошибка: введена пустая строка, ожидалось число");
    size_t i = 0;
    if (s[0] == '-') i = 1;
    if (i == s.size())
        throw AppException("Ошибка: \"" + s + "\" не является целым числом");
    for (; i < s.size(); i++)
        if (!std::isdigit((unsigned char)s[i]))
            throw AppException("Ошибка: \"" + s + "\" не является целым числом");
    if (s.size() > 9)
        throw AppException("Ошибка: слишком большое число");
    int value = std::stoi(s);
    if (value < minVal || value > maxVal)
        throw AppException("Ошибка: число должно быть в диапазоне от " +
                           std::to_string(minVal) + " до " + std::to_string(maxVal));
    return value;
}

std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    if (!std::getline(std::cin, s))
        throw AppException("Ошибка: поток ввода закрыт");
    if (s.empty())
        throw AppException("Ошибка: поле не может быть пустым");
    return s;
}

// Годы жизни в формате ГГГГ-ГГГГ, либо ГГГГ- если автор жив
std::string readYears(const std::string& prompt) {
    std::string s = readLine(prompt);
    bool ok = (s.size() == 9 || s.size() == 5) && s[4] == '-';
    for (int i = 0; ok && i < 4; i++)
        if (!std::isdigit((unsigned char)s[i])) ok = false;
    if (ok && s.size() == 9) {
        for (int i = 5; i < 9; i++)
            if (!std::isdigit((unsigned char)s[i])) ok = false;
        if (ok && std::stoi(s.substr(5)) < std::stoi(s.substr(0, 4)))
            throw AppException("Ошибка: год смерти не может быть меньше года рождения");
    }
    if (!ok)
        throw AppException("Ошибка: годы жизни вводятся в формате ГГГГ-ГГГГ или ГГГГ-");
    return s;
}

bool readYesNo(const std::string& prompt) {
    std::string s = readLine(prompt + " (д/н): ");
    if (s == "д" || s == "Д" || s == "y" || s == "Y") return true;
    if (s == "н" || s == "Н" || s == "n" || s == "N") return false;
    throw AppException("Ошибка: нужно ввести \"д\" или \"н\"");
}

std::string readFileLine(std::istream& in) {
    std::string s;
    if (!std::getline(in, s))
        throw AppException("Ошибка: файл повреждён или неожиданно закончился");
    return s;
}
