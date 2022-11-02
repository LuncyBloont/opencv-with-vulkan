#ifndef CVVK_CONFIGMGR_HPP
#define CVVK_CONFIGMGR_HPP

#include "helper.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <vcruntime.h>
#include <vector>
#include <string>
#include <map>

namespace mltsg {

#define MLTSG_CFG(s) std::string(s)

enum class ConfigType
{
    Int,
    Float,
    Double,
    Boolean,
    String
};

struct ConfigItem
{
    std::string key;
    ConfigType type;
    std::vector<char> data;

    template<typename T = int>
    ConfigItem(const std::string& key, ConfigType type, const T& v = 0) : key(key), type(type)
    {
        set(v);
    }

    ConfigItem()
    {
        key = "????";
        type = ConfigType::Int;
        set(0);
    }

    int Int() const { return *(reinterpret_cast<const int*>(data.data())); };
    float Float() const { return *(reinterpret_cast<const float*>(data.data())); };
    double Double() const { return *(reinterpret_cast<const double*>(data.data())); };
    bool Boolean() const { return *(reinterpret_cast<const bool*>(data.data())); };
    std::string String() const { return *(reinterpret_cast<const std::string*>(data.data())); };

    template<typename T>
    void set(const T& val)
    {
        const char* arr = reinterpret_cast<const char*>(&val);
        int count = sizeof(val);
        data.clear();
        for (int i = 0; i < count; ++i)
        {
            data.push_back(arr[i]);
        }
    }
};

inline std::ostream& operator<<(std::ostream& os, const ConfigItem& item)
{
    os << item.key << "=";
    switch (item.type) {
        case ConfigType::Boolean:
            os << (item.Boolean() ? "True" : "False");
            break;
        case ConfigType::Double:
            os << item.Double();
            break;
        case ConfigType::Int:
            os << item.Int();
            break;
        case ConfigType::Float:
            os << item.Float() << "f";
            break;
        case ConfigType::String:
            os << "\"" << item.String() << "\"";
            break;
    }
    return os;
}

template <int id = 0, typename T, typename ...Default>
void makeConfig(const std::string& fname, const std::vector<ConfigItem>& config, 
    const T& dft, const Default&... dfts)
{
    if (id == 0)
    {    
        std::ifstream test(fname, std::ios::in);
        if (test.is_open())
        {
            test.close();
            return;
        }
    }

    std::ofstream ofs(fname, id == 0 ? std::ios::out : std::ios::app);
    if (id < config.size())
    {
        ofs << ConfigItem{ config[id].key, config[id].type, dft };
        ofs << "\n";
    }
    ofs.close();
    if (id < config.size())
    {
        makeConfig<id + 1>(fname, config, dfts...);
    }
}

template <int id = 0>
void makeConfig(const std::string& fname, const std::vector<ConfigItem>& config)
{
    std::ifstream test(fname, std::ios::in);
    if (test.is_open())
    {
        test.close();
        return;
    }

    std::ofstream ofs(fname, id == 0 ? std::ios::out : std::ios::app);
    for (int i = id; i < config.size(); ++i)
    {
        ofs << config[i];
        ofs << "\n";
    }
    ofs.close();
}

inline void readConfig(std::vector<ConfigItem>& config, const std::string& fname)
{
    config.clear();
    std::ifstream ifs(fname, std::ios::in);
    if (!ifs.is_open())
    {
        mltsg::LogErr("failed to open file (%s)\n", CSTR(fname));
        throw std::runtime_error("open");
    }
    while (!ifs.eof())
    {
        std::string line;
        std::getline(ifs, line);
        if (line.size() == 0) { continue; }
        size_t p0 = line.find_first_of('=');
        std::string key = line.substr(0, p0);
        std::string val = line.substr(p0 + 1, line.size() - p0 - 1);

        size_t blk0 = val.find_first_of(' ');
        blk0 = blk0 == std::string::npos ? -1 : blk0;
        size_t blk1 = val.find_last_of(' ');
        blk1 = blk1 == std::string::npos ? val.size() : blk1;
        val = val.substr(blk0 + 1, blk1 - blk0 - 1);

        if (val.size() == 0)
        {
            config.push_back({ key, ConfigType::Boolean, 0 });
        }
        else if (val == "true" || val == "TRUE" || val == "True")
        {
            config.push_back({ key, ConfigType::Boolean, true });
        }
        else if (val == "false" || val == "FALSE" || val == "False")
        {
            config.push_back({ key, ConfigType::Boolean, false });
        }
        else if (val[0] == '"' && val[val.size() - 1] == '"')
        {
            config.push_back({ key, ConfigType::String, val.substr(1, val.size() - 2) });
        }
        else if (val.find('.') != std::string::npos && (val[val.size() - 1] == 'f' || val[val.size() - 1] == 'F'))
        {
            config.push_back({ key, ConfigType::Float, float(std::atof(val.c_str())) });
        }
        else if (val.find('.') != std::string::npos)
        {
            config.push_back({ key, ConfigType::Double, std::atof(val.c_str()) });
        }
        else
        {
            config.push_back({ key, ConfigType::Int, std::atoi(val.c_str()) });
        }
    }
}

inline void readConfig(std::map<std::string, ConfigItem>& config, const std::string &fname)
{
    config.clear();
    std::vector<ConfigItem> vec;
    readConfig(vec, fname);

    for (const auto& item : vec)
    {
        config.insert({ item.key, item });
    }
}

inline void print(const std::string& title, const std::map<std::string, ConfigItem>& config)
{
    mltsg::Log("%s:\n", CSTR(title));
    for (const auto& item : config)
    {
        mltsg::Log("%s\n", CSTR(item.second));
    }
}

inline void print(const std::string& title, const std::vector<ConfigItem>& config)
{
    mltsg::Log("%s:\n", CSTR(title));
    for (const auto& item : config)
    {
        mltsg::Log("    %s\n", CSTR(item));
    }
}

}

#endif