#pragma once
#include "BaseDevice.hpp"

class SmartThermostat final : public BaseDevice {
private:
    double m_targetTemp;
public:
    SmartThermostat(const std::string& name, int power, std::shared_ptr<std::string> roomName, double targetTemp);
    SmartThermostat(const SmartThermostat& other);

    std::string GetType() const override { return "Термостат"; }
    std::string Describe() const override;
    std::unique_ptr<BaseDevice> Clone() const override {
        return std::make_unique<SmartThermostat>(*this);
    }
    void SetTargetTemp(double temp);
};