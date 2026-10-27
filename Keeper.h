#ifndef KEEPER_H
#define KEEPER_H

#include "Base.h"
#include <string>

// Контейнер "Печатное издание": хранит указатели на объекты-наследники Base
class Keeper {
private:
    Base** items;   // динамический массив указателей
    int size;

    void clear();

public:
    Keeper();
    explicit Keeper(const std::string& fileName);   // создание с загрузкой из файла
    Keeper(const Keeper& other);
    ~Keeper();

    Keeper& operator=(const Keeper& other);
    Keeper& operator+=(Base* obj);     // добавление объекта
    Keeper& operator-=(int index);     // удаление объекта по индексу
    Base& operator[](int index);

    void add(Base* obj);
    void remove(int index);
    int getSize() const;
    void showAll(std::ostream& out) const;

    void saveToFile(const std::string& fileName) const;
    void loadFromFile(const std::string& fileName);
};

#endif
