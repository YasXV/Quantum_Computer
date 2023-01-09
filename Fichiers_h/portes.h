#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "qbit.h"
#include "etatquantique.h"
#ifndef PORTES_H
#define PORTES_H

using namespace std;

class portes{
   public :
   //constructeur
   portes(int numberporte);
   sf::FloatRect getlocalbounds() const ; 
   sf::FloatRect getglobalbounds() const;
   float getx() const;
   float gety() const;
   void drawTo(sf::RenderWindow &window);
   void setposition(sf::Vector2f position);
   void dragandDrop(sf::Event myev,sf::RenderWindow &window);
   void follow(sf::RenderWindow &window);
   void cleanse();
   int getporte();
   bool otherbool=false;
   sf::Sprite otherspr;
   void totraycast(vector<qbit> &vect,sf::Event event);
   void surliraycast(vector<qbit> &vect);
   void surliportes(sf::RenderWindow & window);
   sf::Vector2f getposition() const;
   
   
   
   
  private :
  sf::Sprite myspr;
  sf::Texture mytext;
  sf::IntRect myintRect; 
  vector<sf::Sprite> spr;
  bool mybool=false;
  int p=0;
  int e;
  sf::RectangleShape visu;
  sf::RectangleShape outlpo;
  sf::Font myfont;
  sf::Text bla;
  string contenu;
  

};

#endif
