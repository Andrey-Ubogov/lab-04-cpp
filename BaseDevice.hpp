#pragma once

#include <string>
#include <iostream>
#include <memory>

class BaseDevice {
protected:
    std::string FormatHeader() const;

public:
    static int NextId();

    BaseDevice(const std::string& name, int power, std::shared_ptr<std::string> roomName);
    BaseDevice(const BaseDevice& other);            // Глубокое копирование
    BaseDevice(BaseDevice&& other) noexcept;
    BaseDevice& operator=(const BaseDevice& other);
    virtual ~BaseDevice();

    virtual std::string GetType() const = 0;
    virtual std::unique_ptr<BaseDevice> Clone() const = 0;
    virtual std::string Describe() const;

    void TurnOn();
    void TurnOff();
    void Break();
    void Repair();

    // Метод для изменения названия комнаты (через указатель)
    void RenameRoom(const std::string& newName);

    int GetId() const { return m_id; }
    std::string GetName() const { return m_name; }
    bool GetIsOn() const { return m_isOn; }
    bool GetIsBroken() const { return m_isBroken; }
    int GetPower() const { return m_powerConsumption; }

private:
    inline static int s_lastId = 0;

    int m_id;
    std::string m_name;
    bool m_isOn;
    bool m_isBroken;
    int m_powerConsumption;
    std::shared_ptr<std::string> m_roomName; // Поле для демонстрации копирования
};