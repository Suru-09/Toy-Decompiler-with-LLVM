#ifndef _CODEGEN_SETTINGS_H_
#define _CODEGEN_SETTINGS_H_

#include <mutex>

namespace settings {

class CodegenSettings {

private:
CodegenSettings() = default;
static void initInstance();

class Foo {};
static std::shared_ptr<CodegenSettings> m_instance;
static std::once_flag m_flag;

public:
static std::shared_ptr<CodegenSettings> getInstance();

// dummy constructor
CodegenSettings(Foo foo) {};
CodegenSettings(CodegenSettings const&) = delete;
CodegenSettings(CodegenSettings&&) = delete;
void operator=(CodegenSettings const&) = delete;
void operator=(CodegenSettings&&) = delete;
};

}   // namespace settings

#endif