#include "SmartLamp.hpp"

SmartLamp::SmartLamp(const std::string& name, int power, std::shared_ptr<std::string> roomName, int brightness)
    : BaseDevice(name, power, roomName), m_brightness(brightness) {
    std::cout << "[SmartLamp] —оздана лампа: " << GetName() << std::endl;
}

SmartLamp::SmartLamp(const SmartLamp& other)
    : BaseDevice(other), m_brightness(other.m_brightness) {
    std::cout << "[SmartLamp]  опирование лампы" << std::endl;
}

std::string SmartLamp::Describe() const {
    return BaseDevice::Describe() + ", €ркость: " + std::to_string(m_brightness) + "%";
}

void SmartLamp::SetBrightness(int brightness) {
    if (brightness < 0 || brightness > 100) {
        std::cout << "  ќшибка: яркость должна быть от 0 до 100." << std::endl;
        return;
    }
    m_brightness = brightness;
    std::cout << "  яркость лампы '" << GetName() << "' изменена на " << m_brightness << "%." << std::endl;
}