#ifndef BASE_H
#define BASE_H

#include <string>
#include <iostream>

// Абстрактный базовый класс "Автор": ФИО и список произведений
class Base {
protected:
    std::string name;
    std::string* works;   // динамический массив произведений
    int worksCount;

public:
    Base();
    Base(const std::string& name, const std::string* works, int count);
    Base(const Base& other);
    virtual ~Base();

    Base& operator=(const Base& other);

    void setName(const std::string& n);
    std::string getName() const;
    void setWorks(const std::string* w, int count);
    int getWorksCount() const;
    std::string getWork(int index) const;
    void addWork(const std::string& w);
    void removeWork(int index);

    virtual Base* clone() const = 0;          // копия объекта в динамической памяти
    virtual int getType() const = 0;          // 1 - поэт, 2 - романист, 3 - фантаст
    virtual std::string getTypeName() const = 0;
    virtual void show(std::ostream& out) const = 0;
    virtual void edit() = 0;                  // изменение полей через меню
    virtual void save(std::ostream& out) const;
    virtual void load(std::istream& in);

protected:
    void showWorks(std::ostream& out) const;
    void editWorks();                         // подменю работы с произведениями
};

std::ostream& operator<<(std::ostream& out, const Base& obj);

#endif
