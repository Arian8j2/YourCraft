#pragma once

#include <map>
#include <rapidjson/document.h>

#define SETTING_FILE_NAME "settings.json"

class CSetting{
private:
    rapidjson::Document m_Doc;

public:
    CSetting();

    std::map<std::string, rapidjson::Value> m_Values;
};