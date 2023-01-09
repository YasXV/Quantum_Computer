#include "qbit.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>
#include <vector>
#include <iostream>

using namespace std;

//CONSTRUCTEUR : initialisation d'un qbit numéro a
qbit::qbit(int a){
  indicebit=a;
  uneligne.setSize(sf::Vector2f(950.f,3));
  uneligne.setFillColor(sf::Color(220,220,220,180));
  uneligne.setOrigin(sf::Vector2f(0.f,uneligne.getGlobalBounds().height/2));

  if (!myfont.loadFromFile("../Sprites/LikhanNormal.ttf")){
      cout<<"EXIT_FAILURE"<<endl;
  }

  mytext.setFont(myfont);
  bla="Q"+to_string(a);
  mytext.setString(bla);
  mytext.setCharacterSize(20);
  mytext.setFillColor(sf::Color(0,0,0,120));
  mytext.setOrigin(sf::Vector2f(mytext.getGlobalBounds().width,mytext.getGlobalBounds().height/2));
  mytext.setPosition(uneligne.getPosition()-sf::Vector2f(3.f,0.f));
  ray.setSize({uneligne.getLocalBounds().width,32.f});
  ray.setOrigin({0.f,ray.getLocalBounds().height/2});
  ray.setFillColor(sf::Color::Transparent);
  ray.setPosition(uneligne.getPosition());
  ray.setOutlineThickness(2.f);
}

qbit::qbit(){//2éme constructeur qui n'est pas initialiser (initialisation via méthode setName)
  //indicebit=a;
  uneligne.setSize(sf::Vector2f(950.f,3));
  uneligne.setFillColor(sf::Color(220,220,220,180));
  uneligne.setOrigin(sf::Vector2f(0.f,uneligne.getGlobalBounds().height/2));

  if (!myfont.loadFromFile("../Sprites/LikhanNormal.ttf")){
      cout<<"EXIT_FAILURE"<<endl;
  }

  mytext.setFont(myfont);
  //bla="Q"+to_string(a);
  //mytext.setString(bla);
  mytext.setCharacterSize(20);
  mytext.setFillColor(sf::Color(0,0,0,120));
  mytext.setOrigin(sf::Vector2f(mytext.getGlobalBounds().width,mytext.getGlobalBounds().height/2));
  mytext.setPosition(uneligne.getPosition()-sf::Vector2f(3.f,0.f));
  ray.setSize({uneligne.getLocalBounds().width,32.f});
  ray.setOrigin({0.f,ray.getLocalBounds().height/2});
  ray.setFillColor(sf::Color::Transparent);
  ray.setPosition(uneligne.getPosition());
  ray.setOutlineThickness(2.f);
}

//initialisation d'un qbit
void qbit::setName(int a){
  indicebit=a;
  bla="Q"+to_string(a);
  mytext.setString(bla);
  mytext.setCharacterSize(20);
  mytext.setFillColor(sf::Color(0,0,0,120));
  mytext.setOrigin(sf::Vector2f(mytext.getGlobalBounds().width,mytext.getGlobalBounds().height/2));
  mytext.setPosition(uneligne.getPosition()-sf::Vector2f(3.f,0.f));
}

int qbit::getindicebit() const{
  return indicebit;

}
float qbit::getsize() const {
  return(uneligne.getLocalBounds().width);
}

float qbit::getx(){
return(uneligne.getPosition().x);
}

float qbit::gety(){
return(uneligne.getPosition().y);
}


// dessin du qbit e (ligne de circuit)
void qbit::drawTo(sf::RenderWindow &window){
   window.draw(mytext);
   window.draw(uneligne);
   window.draw(ray);
     for(size_t i=0;i<sprligne.size();i++){
       window.draw(sprligne[i]);
  }
 }

//set position qbit
void qbit::setposition(sf::Vector2f position){
  uneligne.setPosition(position);
  mytext.setPosition(uneligne.getPosition()-sf::Vector2f(12.f,3.5f));
  ray.setPosition(uneligne.getPosition());

}
 //raycast du qbit---------------------------------------------------------------------------------------------------------------------
sf::FloatRect qbit::raycast(){
   return(ray.getGlobalBounds());
}

sf::Vector2f qbit::getposition(){
  return(uneligne.getPosition());
}

void qbit::raycastsurli(bool myb){
    if(myb){ray.setOutlineColor(sf::Color(47,79,79,80));}

  else {ray.setOutlineColor(sf::Color::Transparent);}
}
