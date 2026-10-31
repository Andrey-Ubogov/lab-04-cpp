#include "SmartThermostat.hpp"

SmartThermostat::SmartThermostat(const std::string& name, int power, std::shared_ptr<std::string> roomName, double targetTemp)
    : BaseDevice(name, power, roomName), m_targetTemp(targetTemp) {
    std::cout << "[SmartThermostat] Создан термостат: " << GetName() << std::endl;
}

SmartThermostat::SmartThermostat(const SmartThermostat& other)
    : BaseDevice(other), m_targetTemp(other.m_targetTemp) {
    std::cout << "[SmartThermostat] Копирование термостата" << std::endl;
}

std::string SmartThermostat::Describe() const {
    return "Термостат '" + GetName() + "': целевая температура "
        + std::to_string(m_targetTemp) + " C";
}

void SmartThermostat::SetTargetTemp(double temp) {
    if (temp < 5.0 || temp > 30.0) {
        std::cout << "  Ошибка: Температура должна быть от 5 до 30 C." << std::endl;
        return;
    }
    m_targetTemp = temp;
    std::cout << "  Термостат '" << GetName() << "' настроен на " << m_targetTemp << " C." << std::endl;
}