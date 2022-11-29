#include "Scene.hh"

void Scene::Print()
{
    cout<<endl<<"Obiekty na scenie:\n";
    for(ListOfMobileObj::iterator i = MobileObjMap.begin(); i!=MobileObjMap.end(); ++i)
     {
        cout<<"\t->\t"<<i->first<<":\t";
        cout<<"Pos"<<i->second->GetPositoin_m();
        cout<<"\tRPY("<<i->second->GetAng_Roll_deg()<<","
        <<i->second->GetAng_Pitch_deg()<<","<<i->second->GetAng_Yaw_deg()<<")\n";
     }   
    cout<<endl<<endl;
}

std::shared_ptr<MobileObj> Scene::FindMobileObj(std::string name){
    auto iterator = MobileObjMap.find(name);
    if(iterator == MobileObjMap.end()){
        return nullptr;
    }else{
        return iterator->second;
    }
}

bool Scene::IfMobileObjectExists(string Name)
{
    auto It = MobileObjMap.find(Name);

    if (It == MobileObjMap.end())
        return false;
    else    
        return true;
}