#ifndef SCENE_HH
#define SCENE_HH

/*!
 * \file
 * \brief Definicja klasy Scene
 *
 * Plik zawiera definicję klasy Scene ...
 */

#include <iostream>
#include <map>
#include "MobileObj.hh"

class Scene
{
    public:
        void _Set_MobileObjs(std::map<std::string,std::shared_ptr<MobileObj>>);
        std::shared_ptr<MobileObj> FindMobileObj(const char *sObjName);
        std::shared_ptr<MobileObj> FindMobileObj(const std::string & rObjName);
        void AddMobileObj(MobileObj *pMobObj);

};

#endif