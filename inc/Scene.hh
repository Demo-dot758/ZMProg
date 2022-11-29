#ifndef SCENE_HH
#define SCENE_HH

#include <iostream>
#include <map>
#include "MobileObj.hh"
#include <memory>
#include <string>
#include "AccessControl.hh"
#include <vector>
/*!
 * \file
 * \brief Definicja klasy Scene
 *
 * Plik zawiera definicję klasy Scene ...
 */

using namespace std;
typedef std::map<std::string, std::shared_ptr<MobileObj>> ListOfMobileObj;

class Scene : public AccessControl
{
    private:
        ListOfMobileObj MobileObjMap;
    public:
        std::vector<std::shared_ptr<MobileObj>> MobileObjectsList;
        Scene(ListOfMobileObj MList){MobileObjMap=MList;};
        ~Scene(){};
        ListOfMobileObj GetMobileObjMap() {return MobileObjMap;};
        std::shared_ptr<MobileObj> FindMobileObj(std::string name);

        void Clear();
        void Close();

        void Print();
        bool IfMobileObjectExists(string Name);
        void AddMobileObject(std::string Name)
        {
            std::shared_ptr<MobileObj> new_Ptr = std::make_shared<MobileObj>();
            this->MobileObjMap.insert({Name, new_Ptr});
        }

};

#endif