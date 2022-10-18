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
        std::map<std::string,std::shared_ptr<MobileObj>> Set_MobileObjs();
        std::shared_ptr<MobileObj> FindMobileObj(const char *sObjName);
        std::shared_ptr<MobileObj> FindMobileObj(const std::string & rObjName);
        void AddMobileObj(MobileObj *pMobObj);

};

#endif