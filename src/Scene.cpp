#include "Scene.hh"

// void Scene::LoadMobObjects(ListMobileOb &ListMobileOb){
//     MobileObjects = ListMobileOb;
// }

// void Scene::Print(){
//     std::cout << "\n Istniejące obiekty mobilne: ";

//     for(ListMobileOb::iterator i = MobileObjMap.begin(); i != MobileObjMap.end(); i++){
//         std::cout << "\n \t" << i->first;
//     }
//     std::cout << endl;
// }

std::shared_ptr<MobileObj> Scene::FindMobileObj(std::string name){
    auto iterator = MobileObjMap.find(name);
    if(iterator == MobileObjMap.end()){
        return nullptr;
    }else{
        return iterator->second;
    }
}

// bool Scene::ExistMobObjects(std::string name){
//     auto iterator = MobileObjects.find(name);
//     if(iterator == MobileObjects.end()){
//         return false;
//     }else{
//         return true;
//     }
// }