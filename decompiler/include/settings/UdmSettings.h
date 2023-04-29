#ifndef _UDM_SETTINGS_H_
#define _UDM_SETTINGS_H_

#include <mutex>

namespace settings {

class UdmSettings {

private:
// see the note in CodegenSettings.h for more details.
class Foo {};
UdmSettings() {};

static void initInstance();

static std::shared_ptr<UdmSettings> m_instance;
static std::once_flag m_flag;

public:
static std::shared_ptr<UdmSettings> getInstance();

// dummy constructor
UdmSettings(Foo foo) {};
// delete copy/move constructors and assignment/move operators.
UdmSettings(UdmSettings const&) = delete;
UdmSettings(UdmSettings&&) = delete;
void operator=(UdmSettings const&) = delete;
void operator=(UdmSettings&&) = delete;
};
}  // namespace settings

#endif