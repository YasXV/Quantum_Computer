#ifndef QBIT_H
#define QBIT_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>
#include <vector>
#include <iostream>
#include "etatquantique.h"

using namespace std;

class qbit{
      public:
      qbit(int a);
      qbit();
      void setName(int a);
      int getindicebit() const;
      void drawTo(sf::RenderWindow &window);
      void setposition(sf::Vector2f position);
      float getx();
      float gety();
      sf::FloatRect raycast();
      sf::Vector2f getposition();
      void raycastsurli(bool myb);
      vector<sf::Sprite> sprligne;// vector des sprites "otherspr" sur chaque qbit (donc vecteur qui contient les sprites des portes sur chaque qbit)
      vector<int> ordreporte;// vector dans lequel est assigné dans l'ordre un l'entier qui correspond à chaque porte  pour chaque qbit( ainsi on sait quels portes s'appliquent sur quel qbit )
      float getsize() const;


     private:
     int indicebit;
     sf::RectangleShape ray;
     sf::RectangleShape uneligne;
     sf::Text mytext;
     sf::Font myfont;
     string bla;




};



#endif
