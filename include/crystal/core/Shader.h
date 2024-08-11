#pragma once
#include <fstream>
#include <cerrno>
namespace crystal{
class Shader{
    public:
        unsigned int ID;
        Shader(const char* vertex_file,const char* fragment_file);
        void Activate();
        void Delete();
};

}