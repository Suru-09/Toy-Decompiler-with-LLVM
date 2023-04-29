#ifndef _LIFTER_SETTINGS_H_
#define _LIFTER_SETTINGS_H_

#include <mutex>

namespace settings {

class Foo;

class LifterSettings {

private:
    class Foo {};
    LifterSettings() = default;
    static void initInstance();

    static std::shared_ptr<LifterSettings> m_instance;
    static std::once_flag m_flag;

public:
    // dummy constructor
    explicit LifterSettings(Foo foo) {};

    static std::shared_ptr<LifterSettings> getInstance();

    // delete copy/move constructors and assignment/move operators.
    LifterSettings(LifterSettings const&) = delete;
    LifterSettings(LifterSettings&&) = delete;
    void operator=(LifterSettings const&) = delete;
    void operator=(LifterSettings&&) = delete;
};

}   // namespace settings

#endif