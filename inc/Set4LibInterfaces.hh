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

typedef std::map<std::string, std::shared_ptr<LibInterface>> Set4LibMap;

class Set4LibInterfaces
{
    private:
        Set4LibMap LibMap;

    public:
        Set4LibInterfaces();
        ~Set4LibInterfaces(){};

        void LoadLib(std::string path);
};

#endif