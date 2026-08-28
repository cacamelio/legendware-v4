#pragma once
#include "includes.h"

struct data_info
{
    int size;
    uint8_t* buffer;
};

class resource_manager
{
public:
    void start_download();
    bool get_done() { return m_is_done; }
    data_info get_data(std::string id)
    {
        auto it = m_data.find(id);
        if (it != m_data.end())
            return it->second;
        return { 0, nullptr };
    }
    void clear() {};
private:
    bool m_is_done = false;
    std::unordered_map<std::string, data_info> m_data;
};
