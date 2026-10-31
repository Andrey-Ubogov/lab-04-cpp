#include <iostream>
#include <memory>
#include <vector>
#include <Windows.h>
#include "BaseDevice.hpp"
#include "SmartLamp.hpp"
#include "SmartThermostat.hpp"

void DemonstrateInheritance() {
    std::cout << "\n========== ЛР 4. Демонстрация наследования ==========\n" << std::endl;

    // Создаем "комнату" как shared_ptr, чтобы показать разницу
    auto roomPtr = std::make_shared<std::string>("Гостиная");

    std::cout << "--- 1. Порядок вызова конструкторов ---" << std::endl;
    SmartLamp lamp("Умная лампа", 10, roomPtr, 80);
    SmartThermostat thermostat("Термостат 1", 15, roomPtr, 22.5);

    std::cout << "\n--- 2. Виртуальные методы и виртуальный деструктор ---" << std::endl;
    {
        std::unique_ptr<BaseDevice> ptr = std::make_unique<SmartLamp>("Лампа на балконе", 5, roomPtr, 50);
        std::cout << "Описание через указатель: " << ptr->Describe() << std::endl;
        ptr.reset();
        std::cout << "Указатель сброшен." << std::endl;
    }

    std::cout << "\n--- 3. Поверхностное и глубокое копирование ---" << std::endl;

    // --- ПОВЕРХНОСТНОЕ КОПИРОВАНИЕ (Shallow Copy) ---
    std::cout << "-> Поверхностное копирование (делим один shared_ptr):" << std::endl;
    auto shallowRoom = roomPtr; // Копируем указатель, а не строку
    SmartLamp shallowCopy("Лампа (поверхностная копия)", 10, shallowRoom, 60);

    std::cout << "Оригинал: " << lamp.Describe() << std::endl;
    std::cout << "Копия:    " << shallowCopy.Describe() << std::endl;

    // Меняем комнату у копии (через указатель)
    shallowCopy.RenameRoom("Спальня");

    std::cout << "После переименования комнаты у копии:" << std::endl;
    std::cout << "Оригинал: " << lamp.Describe() << "  <-- ИЗМЕНИЛСЯ!" << std::endl;
    std::cout << "Копия:    " << shallowCopy.Describe() << std::endl;

    // --- ГЛУБОКОЕ КОПИРОВАНИЕ (Deep Copy) ---
    std::cout << "\n-> Глубокое копирование (через Clone()):" << std::endl;
    auto deepCopy = lamp.Clone(); // Вызывает наш конструктор копирования (создает новую строку)

    std::cout << "Оригинал: " << lamp.Describe() << std::endl;
    std::cout << "Копия:    " << deepCopy->Describe() << std::endl;

    // Меняем комнату у глубокой копии
    deepCopy->RenameRoom("Кухня");

    std::cout << "После переименования комнаты у глубокой копии:" << std::endl;
    std::cout << "Оригинал: " << lamp.Describe() << "  <-- НЕ ИЗМЕНИЛСЯ!" << std::endl;
    std::cout << "Копия:    " << deepCopy->Describe() << std::endl;

    std::cout << "\n--- 4. Присваивание и this ---" << std::endl;
    SmartLamp lamp1("Лампа 1", 10, roomPtr);
    SmartLamp lamp2("Лампа 2", 12, roomPtr);
    lamp1 = lamp2;
    std::cout << "Всего создано устройств: " << BaseDevice::NextId() - 1 << std::endl;

    std::cout << "\n--- 5. Работа со строками ---" << std::endl;
    std::string text = lamp1.Describe();
    std::cout << "Полное описание: " << text << std::endl;
    size_t pos = text.find("Лампа");
    if (pos != std::string::npos) {
        std::cout << "Найдена подстрока: '" << text.substr(pos, 5) << "'" << std::endl;
    }

    std::cout << "\n--- Конец демонстрации ---\n" << std::endl;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "Russian");
    DemonstrateInheritance();
    return 0;
}
