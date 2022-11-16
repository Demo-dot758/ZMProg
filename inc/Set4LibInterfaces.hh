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
    private:
        std::map<std::string, std::shared_ptr<LibInterface>> LibMap;
    public:
        Set4LibInterfaces();
        ~Set4LibInterfaces(){};

        void LoadLib(std::string path);

        std::map<std::string, std::shared_ptr<LibInterface>>::iterator FindLib(std::string libName)
        {
            return LibMap.find(libName);
        }

        std::map<std::string, std::shared_ptr<LibInterface>>::iterator EndMap()
        {
            return LibMap.end();
        }
        
};

#endif