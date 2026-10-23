#ifndef APPEXCEPTION_H
#define APPEXCEPTION_H

#include <exception>
#include <string>

// Класс исключений программы, хранит текст с пояснением ошибки
class AppException : public std::exception {
private:
    std::string message;
public:
    explicit AppException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

#endif
