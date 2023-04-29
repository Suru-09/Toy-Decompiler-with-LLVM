#include "settings/CodegenSettings.h"

std::shared_ptr<settings::CodegenSettings> settings::CodegenSettings::m_instance;
std::once_flag settings::CodegenSettings::m_flag;

std::shared_ptr<settings::CodegenSettings> settings::CodegenSettings::getInstance() {
    std::call_once(m_flag, initInstance);
    return m_instance;
}

void settings::CodegenSettings::initInstance() {
    m_instance = std::make_shared<settings::CodegenSettings>(Foo());
};