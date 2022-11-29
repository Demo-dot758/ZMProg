#ifndef SCENE_HH
#define SCENE_HH

#include <iostream>
#include <map>
#include "MobileObj.hh"
#include <memory>
#include <string>

/*!
 * \file
 * \brief Definicja klasy Scene
 *
 * Plik zawiera definicję klasy Scene ...
 */

typedef std::map<std::string, std::shared_ptr<MobileObj>> ListOfMobileObj;

class Scene
{
    private:
        ListOfMobileObj MobileObjMap;
    public:
        Scene(){};
        ~Scene(){};
        ListOfMobileObj GetMobileObjMap() {return MobileObjMap;};
        std::shared_ptr<MobileObj> FindMobileObj(std::string name);
        void AddMobileObj(std::string objName, std::shared_ptr<MobileObj> pMobileObj);
        void UpdateMobileObj();
        void Clear();
        void Close();

        std::shared_ptr<MobileObj> FindMobileObj(const char *sObjName);
        std::shared_ptr<MobileObj> FindMobileObj(const std::string & rObjName);
        void AddMobileObj(MobileObj *pMobObj);

};

#endif