#ifndef _LIFTER_SETTINGS_H_
#define _LIFTER_SETTINGS_H_

#include <mutex>
#include <memory>

#include <spdlog/spdlog.h>

namespace settings {

class Foo;

class LifterSettings {

private:
    // see the note in CodegenSettings.h for more details.
    class Foo {};
    explicit LifterSettings();
    static void initInstance();

    static std::shared_ptr<LifterSettings> m_instance;
    static std::once_flag m_flag;
    std::shared_ptr<spdlog::logger> logger;

    // settings variables
    std::string m_serverUrl;
    std::string m_binaryPath;

public:
    // dummy constructor
    explicit LifterSettings(Foo foo) {};

    static std::shared_ptr<LifterSettings> getInstance();
    void parseLifterSettings(const std::string& setting);

    // delete copy/move constructors and assignment/move operators.
    LifterSettings(LifterSettings const&) = delete;
    LifterSettings(LifterSettings&&) = delete;
    void operator=(LifterSettings const&) = delete;
    void operator=(LifterSettings&&) = delete;

    std::string getServerUrl() const;
    void setServerUrl(const std::string& serverUrl);
    std::string getBinaryPath() const;
    void setBinaryPath(const std::string& binaryPath);
};

}   // namespace settings

#endif