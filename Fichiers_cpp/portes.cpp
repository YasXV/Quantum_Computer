#include "portes.h"
#include "qbit.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>
#include <vector>
#include <iostream>

using namespace std;

//CONSTRUCTEUR : création de mes ports, set du contenu en fonctioon de la porte , myint rect prend une porte de mon sprite 'portes.png en fonction de "e"
portes::portes(int numberporte){
  e=numberporte;
  if(!mytext.loadFromFile("../Sprites/porte.png")){
    cout<<"ERROR"<<endl;
  }
  if (!myfont.loadFromFile("../Sprites/LikhanNormal.ttf")){
      cout<<"EXIT_FAILURE"<<endl;
  }


  if(e==0){contenu="Hadamard";}
  else if(e==1){contenu="NOT gate";}
  else if(e==2){contenu="CNOT gate";}
  else if(e==3){contenu="CCNOT gate";}
  else if(e==4){contenu="Y gate";}
  else if(e==5){contenu="T gate";}
  else if (e==6){contenu="S gate";}
  else if (e==7){contenu="Z gate";}
  bla.setString(contenu);
  bla.setFont(myfont);
  bla.setFillColor(sf::Color::Transparent);
  bla.setCharacterSize(12);
  bla.setOrigin(sf::Vector2f(bla.getGlobalBounds().width/2,bla.getGlobalBounds().height/2));
  mytext.setSmooth(true);
  myspr.setTexture(mytext);
  myintRect.width=47.f;
  myintRect.height=47.f;
  myintRect.left=13.f+numberporte*10.f+numberporte*47.f;
  myintRect.top=11.f;
  myspr.setTextureRect(myintRect);
  myspr.setOrigin({myspr.getLocalBounds().width/2,myspr.getLocalBounds().height/2});
  otherspr.setTexture(mytext);
  otherspr.setTextureRect(myintRect);
  otherspr.setOrigin({otherspr.getLocalBounds().width/2,otherspr.getLocalBounds().height/2});
  otherspr.setScale(sf::Vector2f(0.85f,0.85f));
  visu.setSize(sf::Vector2f(65.f,20.f));
  visu.setFillColor(sf::Color::Transparent);
  visu.setOrigin({visu.getLocalBounds().width/2,visu.getLocalBounds().height/2});
  outlpo.setSize(sf::Vector2f(47.f,47.f));
  outlpo.setOrigin({outlpo.getLocalBounds().width/2,outlpo.getLocalBounds().height/2});
  outlpo.setFillColor(sf::Color::Transparent);
  outlpo.setOutlineThickness(2.f);

  }

int portes::getporte(){
  return e;
 }

sf::Vector2f portes::getposition() const{
   return(myspr.getPosition());
 }

float portes::getx() const{
  return(myspr.getPosition().x);
 }

float portes::gety() const{
  return(myspr.getPosition().y);
 }

sf::FloatRect portes::getlocalbounds() const{
  return(myspr.getLocalBounds());
 }

sf::FloatRect portes::getglobalbounds() const{
  return(myspr.getGlobalBounds());
 }

void portes::drawTo(sf::RenderWindow &window){
  window.draw(myspr);
  window.draw(visu);
  window.draw(bla);
  window.draw(outlpo);
  if(mybool){
    window.draw(otherspr);
  }
}



void portes::setposition(sf::Vector2f position){
  myspr.setPosition(position);


}

//drag and drop des portes
void portes::dragandDrop(sf::Event myev,sf::RenderWindow &window){
  if(this->getglobalbounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y)){
    if(myev.type==sf::Event::MouseButtonPressed){
      if(myev.mouseButton.button==sf::Mouse::Left){
        if(p==0){
         p=1;
        otherbool=true;
        mybool=true;
        otherspr.setPosition({float(sf::Mouse::getPosition(window).x),float(sf::Mouse::getPosition(window).y)});
       }
      }
    }
  }
 }

void portes::follow(sf::RenderWindow &window ){
  if(otherbool){
    otherspr.setPosition({float(sf::Mouse::getPosition(window).x),float(sf::Mouse::getPosition(window).y)});
  }
}

void portes::cleanse(){
  otherbool=false;
  mybool=false;
  p=0;

}


//si on approche une porte du raycast d'un vect[i](ligne de circuit donc qbit) et que l'on clique gauche alors la porte se met automatiquement sur la ligne de circuit vect[i] (un qbit)
void portes::totraycast(vector<qbit> &vect,sf::Event event){
    for(size_t i=0;i<vect.size();i++){
     if((otherspr.getGlobalBounds().intersects(vect[i].raycast())) & (otherbool)){
      if(event.type==sf::Event::MouseButtonPressed){
        if(event.mouseButton.button==sf::Mouse::Left){
          mybool=true;
          otherspr.setPosition({vect[i].getx()+25.f,vect[i].gety()});
          vect[i].sprligne.push_back(otherspr);
          vect[i].ordreporte.insert(vect[i].ordreporte.end(),e);
          this->cleanse();
          for(size_t j=0;j<vect.size();j++){
               vect[j].raycastsurli(false);
         }
        }
       }
      }
     }
   }

//si on approche une porte du raycast de n'importe quel vect[i]  alors celui-ci est surligné
void portes::surliraycast(vector<qbit> &vect) {
  for(size_t i=0;i<vect.size();i++){
    if((otherspr.getGlobalBounds().intersects(vect[i].raycast())) & (otherbool)) {
      vect[i].raycastsurli(true);
    }

   else if((otherbool) & (!otherspr.getGlobalBounds().intersects(vect[i].raycast()))){
   vect[i].raycastsurli(false);}

 }
}

//Surlignage des portes et affichage de leurs noms lorsque je passe dessus *_*
void portes::surliportes(sf::RenderWindow &window){
      if(this->getglobalbounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y)){
        visu.setPosition(this->getposition()+sf::Vector2f(0.f,36.f));
        bla.setPosition(visu.getPosition());
        outlpo.setPosition(this->getposition());
        outlpo.setFillColor(sf::Color(0,0,0,28));
        outlpo.setOutlineColor(sf::Color(0,0,0,45));
        visu.setFillColor(sf::Color(0,0,0,160));
        bla.setFillColor(sf::Color::White);

      }

      else {visu.setFillColor(sf::Color::Transparent);
      bla.setFillColor(sf::Color::Transparent);
      outlpo.setFillColor(sf::Color::Transparent);
     outlpo.setOutlineColor(sf::Color::Transparent);}
}
