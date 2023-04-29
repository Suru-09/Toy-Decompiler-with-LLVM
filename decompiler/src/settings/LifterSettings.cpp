#include "settings/LifterSettings.h"

std::shared_ptr<settings::LifterSettings> settings::LifterSettings::m_instance;
std::once_flag settings::LifterSettings::m_flag;

std::shared_ptr<settings::LifterSettings> settings::LifterSettings::getInstance() {
    std::call_once(m_flag, initInstance);
    return m_instance;
}

void settings::LifterSettings::initInstance() {
    m_instance = std::make_shared<settings::LifterSettings>(Foo());
};