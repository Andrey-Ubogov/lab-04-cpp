#pragma once
#include "BaseDevice.hpp"

class SmartLamp : public BaseDevice {
private:
    int m_brightness;
public:
    // Добавили shared_ptr в параметры
    SmartLamp(const std::string& name, int power, std::shared_ptr<std::string> roomName, int brightness = 100);
    SmartLamp(const SmartLamp& other);

    std::string GetType() const override { return "Умная лампа"; }
    std::string Describe() const override;
    std::unique_ptr<BaseDevice> Clone() const override {
        return std::make_unique<SmartLamp>(*this);
    }
    void SetBrightness(int brightness);
};