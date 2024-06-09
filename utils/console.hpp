#pragma once
#include "console_abstract.hpp"
#include "console_windows.hpp"

namespace utils {
class console final
{
  public:
    static void initialize(); // 初始化m_pconsole
    static void deinitialize(); // 删除m_pconsole
    static console_abstract* get_instance(); // 获取m_pconsole实例

  private:
    static console_abstract* m_pconsole;
};

console_abstract* console::m_pconsole = nullptr;

inline void console::initialize() {
    if (m_pconsole == nullptr) {
        m_pconsole = new console_windows();
    }
}

inline void console::deinitialize() {
    delete m_pconsole;
    m_pconsole = nullptr;
}

inline console_abstract* console::get_instance() {
    return m_pconsole;
}

} // namespace utils
