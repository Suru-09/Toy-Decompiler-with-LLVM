#ifndef _UDM_SETTINGS_H_
#define _UDM_SETTINGS_H_

#include "JSONFileManager.h"

#include <mutex>
#include <memory>

#include <spdlog/spdlog.h>

namespace settings {

class UdmSettings : public JSONFileManager {

private:
// see the note in CodegenSettings.h for more details.
class Foo {};
explicit UdmSettings();

static void initInstance();

static std::shared_ptr<UdmSettings> m_instance;
static std::once_flag m_flag;
std::shared_ptr<spdlog::logger> logger;

std::string m_optimizedIRPath;
static inline const std::string m_fileName = "../settings/UdmSettings.json";

public:
static std::shared_ptr<UdmSettings> getInstance();

void writeSettingsToFile();
void readSettingsFromFile();

std::string getOptimizedIRPath() const;
void setOptimizedIRPath(const std::string& optimizedIRPath);

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