#include "settings/UdmSettings.h"

std::shared_ptr<settings::UdmSettings> settings::UdmSettings::m_instance;
std::once_flag settings::UdmSettings::m_flag;

std::shared_ptr<settings::UdmSettings> settings::UdmSettings::getInstance() {
    std::call_once(m_flag, initInstance);
    return m_instance;
}

void settings::UdmSettings::initInstance() {
    m_instance = std::make_shared<settings::UdmSettings>(Foo());
};