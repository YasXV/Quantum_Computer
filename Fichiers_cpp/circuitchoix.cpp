#include "circuitchoix.h"
#include <iostream>
#include "qbit.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>

using namespace std;

//constructeur (création de mes boutons "+" et "-"
circuitligne::circuitligne(){
     //mylignes.resize(n*2);
     if(!text.loadFromFile("../Sprites/plusmin.png")){
       cout<<"ERROR"<<endl;
     }

     text.setSmooth(true);
     ajoutbit.setTexture(text);
     suppbit.setTexture(text);
     supp.width=20.f;
     supp.height=10.f;
     supp.left=0.f;
     supp.top=20.f;
     ajout.width=20.f;
     ajout.height=22.f;
     ajout.left=0.f;
     ajout.top=0.f;
     ajoutbit.setTextureRect(ajout);
     suppbit.setTextureRect(supp);
     suppbit.setScale(0.75,0.75);
     ajoutbit.setScale(0.75,0.75);
     ajoutbit.setOrigin({ajoutbit.getLocalBounds().width/2,ajoutbit.getLocalBounds().height/2});
     suppbit.setOrigin({suppbit.getLocalBounds().width/2,suppbit.getLocalBounds().height/2});
      //encadrement des boutons "+","-"

      encadre.setSize({ajoutbit.getLocalBounds().width+5.f,ajoutbit.getLocalBounds().height+5.f});
      encadre.setOrigin({encadre.getLocalBounds().width/2,encadre.getLocalBounds().height/2});
      encadre.setFillColor(sf::Color::Transparent);
      encadre.setOutlineColor(sf::Color::White);
      encadre.setOutlineThickness(2.f);

     }

     //draw de mes boutons "+" et "-"
     void circuitligne::drawTo(sf::RenderWindow &window){
       window.draw(suppbit);
       window.draw(ajoutbit);
       window.draw(encadre);
     }

     //Positionement de mes boutons "+" et "-"
     void circuitligne::setposition(sf::Vector2f position){
       ajoutbit.setPosition(position);
       suppbit.setPosition(position+sf::Vector2f(40.f,0.5f));
       encadre.setPosition(position);
     }


    //surlignage des boutons "+" et "-" quand je passe dessus
    void circuitligne ::plusminussurli(sf::RenderWindow &window){
      if(ajoutbit.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y)){
        encadre.setPosition(ajoutbit.getPosition());
        encadre.setOutlineColor(sf::Color(173,213,230,110));}
      else if(suppbit.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y)){
         encadre.setPosition(suppbit.getPosition());
         encadre.setOutlineColor(sf::Color(173,213,230,110));
       }
      else {encadre.setOutlineColor(sf::Color::White);}
  }

  // quand je clique sur "+" je rajoute un qbit à vect (vect étant mon vect de qbit)
   void circuitligne::pushplusminu(sf::RenderWindow &window,sf::Event myev,vector<qbit> &vect){
     if(ajoutbit.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y)){
       if(myev.type==sf::Event::MouseButtonPressed){
         if(myev.mouseButton.button==sf::Mouse::Left){
           encadre.setPosition(ajoutbit.getPosition());
           encadre.setOutlineColor(sf::Color(173,213,230,240));
           encadre.setFillColor(sf::Color(0,0,0,30));
           plus_select=true;
         }
         }
       }

       else if(suppbit.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y)){
         if(myev.type==sf::Event::MouseButtonPressed){
           if(myev.mouseButton.button==sf::Mouse::Left){
             encadre.setPosition(suppbit.getPosition());
             encadre.setOutlineColor(sf::Color(173,213,230,240));
             encadre.setFillColor(sf::Color(0,0,0,30));
             minus_select=true;
           }
           }
         }


       else { encadre.setOutlineColor(sf::Color::White);
             encadre.setFillColor(sf::Color::Transparent); }


           //cout<<vect.size()<<"size"<<endl;
           //cout<<myqbit.getsize()<<endl;

  }


void circuitligne::ajout_test(vector<qbit> &vect){
  if(plus_select){
    n+=1;
    myqbit.setName(n);
    myqbit.setposition({45.f,212.f+n*55.f});
    vect.insert(vect.end(),myqbit);
    plus_select=false;


  }

  if(minus_select){
    n-=1;
    vect.erase(vect.end());
    minus_select=false;
  }


}
