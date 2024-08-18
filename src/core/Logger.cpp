#include "crystal/core/Logger.h"
#include <iostream>
// #include <string.h>
// #include <iostream>
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

namespace logger
{
    std::string LogTypeToString(LogType log_type){
        switch(log_type){
            case LogType::INFO: return "INFO";
            case LogType::WARN: return "WARN";
            case LogType::ERROR: return "ERROR"; 
            case LogType::SUCCESS: return "SUCCESS";
            case LogType::DESTRUCTION: return "DESTRUCTION";
            case LogType::CONSTRUCTION: return "CONSTRUCTION";
            case LogType::MATH: return "MATH";
            case LogType::GRAPHICS: return "GRAPHICS";
            case LogType::PHYSICS: return "PHYSICS";
            case LogType::AUDIO: return "AUDIO";
            case LogType::USER: return "USER";
            case LogType::VULKAN: return "VULKAN";
            case LogType::OPENGL: return "OPENGL";
            case LogType::DIRECTX: return "DIRECTX";
            case LogType::SHADER: return "SHADER";
            case LogType::RESOURCE: return "RESOURCE";
            case LogType::MESSAGE: return "MESSAGE";
            default: return "UNKNOWN";
        }
    }
    void Info(const std::string& s)
    {
        Info(LogType::MESSAGE,s);
    }
    void Info(LogType type,const std::string& s){
        std::cout << CYAN << "[MESSAGE] " << (type == LogType::MESSAGE ? "" : "[" +LogTypeToString(type) + "] ")<< s << RESET << std::endl;
    }

    void Error(const std::string& s)
    {
        Error(LogType::MESSAGE,s);
    }

    void Error(LogType type,const std::string& s){
        std::cout << RED <<  "[ERROR] "<< "[" <<LogTypeToString(type) << "] " << s << RESET << std::endl;
    }


    void Warn(const std::string& s)
    {
        Warn(LogType::MESSAGE,s);
    }

    void Warn(LogType type,const std::string& s){
        std::cout << YELLOW << "[WARNING] " << "[" <<LogTypeToString(type) << "] " << s << RESET << std::endl;
    }
    
    void Success(const std::string& s)
    {
        Success(LogType::MESSAGE,s);
    }

    void Success(LogType type,const std::string& s){
        std::cout << GREEN << "[SUCCESS] " << "[" <<LogTypeToString(type) << "] " << s << RESET << std::endl;
    }
}