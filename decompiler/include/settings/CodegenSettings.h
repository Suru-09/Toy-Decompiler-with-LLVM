#ifndef _CODEGEN_SETTINGS_H_
#define _CODEGEN_SETTINGS_H_

#include <mutex>

namespace settings {

/**
 * @brief Singleton that hold all the detalis in the codegen phase.
 * @Suru-09 Note
 *  The interesting fact is that all the setting classes are singletons that are
 * thread-safe and I am also using smart pointers.Important thing to be note is that I 
 * am not using new keyword to create the instance of the class. I am using make_shared function to
 * create the instance of the class. This is because in case of smart pointers, new calls 
 * alloc two times, one time for the reference count and one time for the object itself.
 * Also, in case of the singleton pattern, the std::make_shared can't be called because
 * it needs access to the constructor in a public way. So, i am using a dummy constructor,
 * that is public, and i am passing a dummy object to the constructor. This is the reason
 * why i am using the Foo class.
 */
class CodegenSettings {

private:
CodegenSettings() = default;
static void initInstance();


// see the comment above
class Foo {};
static std::shared_ptr<CodegenSettings> m_instance;
static std::once_flag m_flag;

public:
static std::shared_ptr<CodegenSettings> getInstance();

// dummy constructor
CodegenSettings(Foo foo) {};

// delete copy/move constructors and assignment/move operators.
CodegenSettings(CodegenSettings const&) = delete;
CodegenSettings(CodegenSettings&&) = delete;
void operator=(CodegenSettings const&) = delete;
void operator=(CodegenSettings&&) = delete;
};

}   // namespace settings

#endif