#include "Configuration.hh"

void Configuration::AddMobObj(const std::string &Name,const Vector3D &Shift,  const Vector3D &Scale,
const Vector3D &Rotation,const Vector3D &Trans,  const std::string &RGB )
{
 auto _nMobObj = std::make_shared<MobileObj>(); //nowy obiekt
 
 _nMobObj -> SetName(Name.c_str());
//  _nMobObj -> SetColourInRGB(RGB);
 _nMobObj -> SetScale(Scale);
 _nMobObj -> SetShift_m(Shift);
 _nMobObj -> SetPosition_m(Trans);

 _nMobObj -> SetAng_Roll_deg(Rotation[0]);
 _nMobObj -> SetAng_Pitch_deg(Rotation[1]);
 _nMobObj -> SetAng_Yaw_deg(Rotation[2]);


 ObjList.insert({Name, _nMobObj});
}
void Configuration::AddLibName(const std::string &LibName){
    LibList.push_back(LibName);
}