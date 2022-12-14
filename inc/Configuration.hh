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
  void AddMobObj(const std::string &name, Vector3D &Scale, const std::string &Rgb);
  
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
};
#endif