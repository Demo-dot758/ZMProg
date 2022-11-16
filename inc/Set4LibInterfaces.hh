#ifndef SET4LIBINTERFACES_HH
#define SET4LIBINTERFACES_HH

#include "LibInterface.hh"
#include <map>
#include <memory>
/*!
 * \file
 * \brief Definicja klasy Set4LibInterfaces
 * 
 */



class Set4LibInterfaces
{
    public:
        std::map<std::string, std::shared_ptr<LibInterface>> LibMap;
        Set4LibInterfaces();
        ~Set4LibInterfaces(){};

        void LoadLib(std::string path);
};

#endif