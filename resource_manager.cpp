#define WIN32_LEAN_AND_MEAN

#include "resource_manager.h"
#include "embedded_resources.h"
#include "globals.h"
#include <filesystem>

void resource_manager::start_download()
{
    static bool started = false;
    if (started)
        return;
    else
        started = true;
    if (m_is_done)
        return;
    auto base = std::string(getenv(crypt_str("APPDATA"))) + std::string(crypt_str("\\Legendware\\"));
    if (!std::filesystem::exists(base))
        std::filesystem::create_directories(base);
    if (!std::filesystem::exists(base + crypt_str("Configs\\")))
        std::filesystem::create_directories(base + crypt_str("Configs\\"));
    if (!std::filesystem::exists(base + crypt_str("Scripts\\")))
        std::filesystem::create_directories(base + crypt_str("Scripts\\"));
    for (size_t i = 0; i < embedded::entries_count; ++i)
    {
        data_info d;
        d.size = (int)embedded::entries[i].size;
        d.buffer = const_cast<uint8_t*>(embedded::entries[i].data);
        m_data[embedded::entries[i].id] = d;
    }
    m_is_done = true;
}
