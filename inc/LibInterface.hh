#ifndef LIBINTERFACE_HH
#define LIBINTERFACE_HH

#include <iostream>
#include "Interp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy LibInterface
 *
 * Plik zawiera definicję klasy LibInterface ...
 */

class LibInterface
{
    public:
        ~LibInterface() {}
        void * _LibHandler();
        std::string _CmdName();
        void _pCreateCmd(Interp4Command*(*)(void));    
};

#endif
