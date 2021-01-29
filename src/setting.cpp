#include "setting.h"

CSetting::CSetting(){
    FILE* pFile = fopen(SETTING_FILE_NAME, "r");
    if(!pFile){
        fprintf(stderr, "Error, Cannot open file '%s'\n", SETTING_FILE_NAME);
        throw 1;
    }

    fseek(pFile, 0, SEEK_END);
    int Size = ftell(pFile);
    fseek(pFile, 0, SEEK_SET);

    char* pData = new char[Size + 1];
    fread(pData, 1, Size, pFile);
    pData[Size] = '\0';

    fclose(pFile);

    m_Doc.Parse(pData);
    if(!m_Doc.IsObject()){
        fprintf(stderr, "Error, Cannot parse settings, Get default setting from github\n");
        throw 1;
    }

    #define SETTING_VARIABLE(name, type, default) { rapidjson::Value& Val = m_Doc[name]; if(!Val.Is## type()) Val.Set## type(default); m_Values.insert(std::pair<const char*, rapidjson::Value>(name, Val.Get## type())); }
    #define SETTING_VARIABLE_OBJ(name, type, default, object) { rapidjson::Value& Val = object [name]; if(!Val.Is## type()) Val.Set## type(default); m_Values.insert(std::pair<const char*, rapidjson::Value>(name, Val.Get## type())); }
    
    SETTING_VARIABLE_OBJ("width", Int, 1920, m_Doc["window"])
    SETTING_VARIABLE_OBJ("height", Int, 1080, m_Doc["window"])
    SETTING_VARIABLE_OBJ("fullscreen", Bool, true, m_Doc["window"])

    SETTING_VARIABLE("fov", Int, 70)
    SETTING_VARIABLE("mouse_sens", Int, 100)
    SETTING_VARIABLE("show_fps", Bool, true)

    SETTING_VARIABLE("anti_aliasing", Bool, true)
    SETTING_VARIABLE("v-sync", Bool, false)

    #undef SETTING_VARIABLE
    #undef SETTING_VARIABLE_OBJ

    delete[] pData;
}