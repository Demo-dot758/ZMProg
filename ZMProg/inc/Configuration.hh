#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH


#include "Scene.hh"
#include "MobileObj.hh"
#include <vector>

/*!
 * \brief Typ definiujący listę dla nazw bibliotek.
 */
typedef std::vector<std::string> ListOfLibs;

/*!
 * \file
 * \brief Definicja klasy Configuration
 *
 * Plik zawiera deficje klasy Configuration
 */
class Configuration {
  private:

  /*!
   * \brief Lista nazw bibliotek
   */
  ListOfLibs LibList;

  /*!
   * \brief Lista obiektów mobilnych w postaci pary nazwy i wskaźnika na obiekt.
   */
  ListOfMobileObj ObjList;

  public:

  /*!
   * \brief Dodaje obiekt mobilny odczytany z pliku konfiguracyjnego XML 
   */
  void AddMobObj(const std::string &Name,const Vector3D &Shift,  const Vector3D &Scale, const Vector3D &Rotation,const Vector3D &Trans,  const std::string &RGB );
  
   /*!
   * \brief Dodaje nazwę biblioteki odczytaną z pliku konfiguracyjnego XML
   */
  void AddLibName(const std::string &LibName);

  /*!
  * \brief Zwraca listę nazw bibliotek
  */
  ListOfLibs GetLibList(){
    return LibList;
  }

  /*!
   * \brief Zwraca listę obiektów mobilnych
   */
  ListOfMobileObj GetObjList(){
    return ObjList;
  }

  void PrintMobileObjectList()
  {
    cout<<endl<<"Obiekty na scenie:\n";
    for(ListOfMobileObj::iterator i = ObjList.begin(); i!=ObjList.end(); ++i)
     {
        cout<<"\t->\t"<<i->first<<":\t";
        cout<<"Pos"<<i->second->GetPositoin_m();
        cout<<"\tRPY("<<i->second->GetAng_Roll_deg()<<","
        <<i->second->GetAng_Pitch_deg()<<","<<i->second->GetAng_Yaw_deg()<<")\n";
     }   
    cout<<endl<<endl;
  }
};
#endif