#include "BaseDevice.hpp"

BaseDevice::BaseDevice(const std::string& name, int power, std::shared_ptr<std::string> roomName)
    : m_id(NextId()), m_name(name), m_isOn(false), m_isBroken(false),
    m_powerConsumption(power), m_roomName(roomName) {
    std::cout << "[BaseDevice] Создано устройство #" << m_id << ": " << m_name << std::endl;
}

// ГЛУБОКОЕ КОПИРОВАНИЕ: создаём новую строку для комнаты
BaseDevice::BaseDevice(const BaseDevice& other)
    : m_id(NextId()), m_name(other.m_name), m_isOn(other.m_isOn),
    m_isBroken(other.m_isBroken), m_powerConsumption(other.m_powerConsumption) {
    // Если у оригинала есть комната, создаём ЕЁ КОПИЮ
    if (other.m_roomName) {
        m_roomName = std::make_shared<std::string>(*other.m_roomName);
    }
    std::cout << "[BaseDevice] Копирование (глубокое): #" << other.m_id << " -> #" << m_id << std::endl;
}

BaseDevice::BaseDevice(BaseDevice&& other) noexcept
    : m_id(other.m_id), m_name(std::move(other.m_name)), m_isOn(other.m_isOn),
    m_isBroken(other.m_isBroken), m_powerConsumption(other.m_powerConsumption),
    m_roomName(std::move(other.m_roomName)) {
    other.m_id = -1;
    std::cout << "[BaseDevice] Перемещение: #" << m_id << std::endl;
}

BaseDevice& BaseDevice::operator=(const BaseDevice& other) {
    std::cout << "[BaseDevice] Оператор присваивания" << std::endl;
    if (this == &other) return *this;
    m_name = other.m_name;
    m_isOn = other.m_isOn;
    m_isBroken = other.m_isBroken;
    m_powerConsumption = other.m_powerConsumption;
    // Глубокое присваивание комнаты
    if (other.m_roomName) {
        m_roomName = std::make_shared<std::string>(*other.m_roomName);
    }
    else {
        m_roomName.reset();
    }
    return *this;
}

BaseDevice::~BaseDevice() {
    std::cout << "[BaseDevice] Уничтожено устройство #" << m_id << ": " << m_name << std::endl;
}

int BaseDevice::NextId() {
    return ++s_lastId;
}

std::string BaseDevice::FormatHeader() const {
    std::string room = m_roomName ? *m_roomName : "без комнаты";
    return "Устройство #" + std::to_string(m_id) + " '" + m_name + "' (" + std::to_string(m_powerConsumption) + " Вт, комната: " + room + ")";
}

std::string BaseDevice::Describe() const {
    return FormatHeader() + ", тип: " + GetType();
}

void BaseDevice::RenameRoom(const std::string& newName) {
    if (m_roomName) {
        *m_roomName = newName;
        std::cout << "  Комната устройства #" << m_id << " переименована в '" << newName << "'." << std::endl;
    }
}

void BaseDevice::TurnOn() {
    if (m_isBroken) {
        std::cout << "  Ошибка: Устройство '" << m_name << "' сломано! Нельзя включить." << std::endl;
        return;
    }
    m_isOn = true;
    std::cout << "  Устройство '" << m_name << "' включено." << std::endl;
}

void BaseDevice::TurnOff() { m_isOn = false; std::cout << "  Устройство '" << m_name << "' выключено." << std::endl; }
void BaseDevice::Break() { m_isBroken = true; m_isOn = false; std::cout << "  Устройство '" << m_name << "' сломалось!" << std::endl; }
void BaseDevice::Repair() { m_isBroken = false; std::cout << "  Устройство '" << m_name << "' отремонтировано." << std::endl; }