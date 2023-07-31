
#include <iostream>
#include <fstream>

#define MAXNAMESIZE 16

enum EWeapon
{
  none, sword, lance, bow
};

//estructura de datos que deben persistir
struct SGameData
{
  char name[MAXNAMESIZE];
  EWeapon  currentWeapon;
  unsigned int  enemysKilled;
};


void Log(const char* msg)
{
  std::cout << msg << "\n";
}


int main()
{
    std::cout << "Hello World!\n";


    //leer el archivo de savegame
    std::fstream savefile("data.sav", std::ios::in | std::ios::out);

    if (savefile.is_open())
    {
      Log("savefile abierto");

      //leer datos del archivo
      SGameData data;
      savefile.read(data.name, MAXNAMESIZE);
      savefile.read(  (char*) & data.currentWeapon, 4);
      savefile.read( (char*)&data.enemysKilled, 4);

      std::cout << "hola " << data.name;
      std::cout << "tienes arma " << data.currentWeapon << " y has matado a " << data.enemysKilled;

    }
    else
    {
      Log("crear savefile vacio e inicial");
      SGameData data;
      Log("Escribe tu nombre, aventurero");
      std::cin >> data.name;
      data.currentWeapon = EWeapon::none;
      data.enemysKilled = 0;
      savefile.open("data.sav", std::ios::out);
      if (savefile.is_open())
      {
        //dumpear la estructura data
        savefile.seekp(0, std::ios::beg);
        savefile.write(  (const char *) & data, sizeof(SGameData));
      }
      else
      {
        Log("no se pudo crear el archivo");
      }
      
    }

    savefile.close();

    return 0;
}