#include "afficheprob.h"
#include "qbit.h"
#include "etatquantique.h"
#include "portes.h"
#include  <vector>
#include <iostream>
#include <cmath>
#include <boost/dynamic_bitset.hpp>
#include <bitset>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>

using namespace std;
using namespace ::boost;

//constructeur qui set le nombre de bit de travail,et mon vecteur etatbit qui correspond à mon axe des x (b =nombre bit)
calproba::calproba(int numberbit){
   b=numberbit;
   myetat.set_nbrbit(b);

   if (!myfont.loadFromFile("../Sprites/LikhanNormal.ttf")){ //on importe le font
       cout<<"EXIT_FAILURE"<<endl;
   }
   //mes coordonnées en abscisse
   bla.setFont(myfont);
   bla.setFillColor(sf::Color(0,0,0,170));
   bla.setCharacterSize(13);
   bla.setOrigin(sf::Vector2f(bla.getGlobalBounds().width/2,bla.getGlobalBounds().height/2));

   //échelle en ordonnée
   ordoo.setFont(myfont);
   ordoo.setFillColor(sf::Color(0,0,0,200));
   ordoo.setCharacterSize(13);
   ordoo.setOrigin(sf::Vector2f(ordoo.getGlobalBounds().width/2,ordoo.getGlobalBounds().height/2));
   ordoo.setRotation(-55);
   //ma barre de proba
   bar.setFillColor(sf::Color(0,128,0));
   bar.setOrigin(sf::Vector2f(bar.getGlobalBounds().width/2,bar.getGlobalBounds().height/2));

   //barre de phase
   barph.setFillColor(sf::Color::Magenta);
   barph.setOrigin(sf::Vector2f(barph.getGlobalBounds().width/2,barph.getGlobalBounds().height/2));

   //grid de mes graphe
   grid.setOrigin(sf::Vector2f(0.f,grid.getGlobalBounds().height/2));
   grid.setFillColor(sf::Color(220,220,220,140));
   grid.setSize(sf::Vector2f(470.f,2.f));


 }//FIN CONSTRUCTEUR

//set mon ordonnée des probas
 void calproba::ordonne(sf::RenderWindow &window){
   probordo="0";
      ordoo.setString(probordo);
      ordoo.setPosition({2.f,730.f});
      window.draw(grid);
      window.draw(ordoo);
   probordo="0.25";
      ordoo.setString(probordo);
      ordoo.setPosition({2.f,665.f});
      grid.setPosition({25.f,665.f});
      window.draw(grid);
      window.draw(ordoo);
  probordo="0.5";
    ordoo.setString(probordo);
    ordoo.setPosition({2.f,600.f});
    grid.setPosition({25.f,600.f});
    window.draw(grid);
    window.draw(ordoo);
  probordo="0.75";
    ordoo.setString(probordo);
    ordoo.setPosition({2.f,535.f});
    grid.setPosition({25.f,535.f});
    window.draw(grid);
    window.draw(ordoo);
  probordo="1";
    ordoo.setString(probordo);
    ordoo.setPosition({2.f,470.f});
    grid.setPosition({25.f,470.f});
    window.draw(grid);
    window.draw(ordoo);

}

//set mon ordonnée des phases
 void calproba::ordonneph(sf::RenderWindow &window){
   probordo="0";
      ordoo.setString(probordo);
      ordoo.setPosition({514.f,730.f});
      //grid.setPosition({38.f,960.f});
      window.draw(grid);
      window.draw(ordoo);
    probordo="1/4";
        ordoo.setString(probordo);
        ordoo.setPosition({514.f,697.5f});
        grid.setPosition({536.f,697.5f});
        window.draw(grid);
        window.draw(ordoo);
   probordo="1/2";
      ordoo.setString(probordo);
      ordoo.setPosition({514.f,665.f});
      grid.setPosition({536.f,665.f});
      window.draw(grid);
      window.draw(ordoo);
  probordo="3/4";
      ordoo.setString(probordo);
      ordoo.setPosition({514.f,632.5f});
      grid.setPosition({536.f,632.5f});
      window.draw(grid);
      window.draw(ordoo);
  probordo="1";
    ordoo.setString(probordo);
    ordoo.setPosition({514.f,600.f});
    grid.setPosition({536.f,600.f});
    window.draw(grid);
    window.draw(ordoo);
  probordo="5/4";
    ordoo.setString(probordo);
    ordoo.setPosition({514.f,567.5f});
    grid.setPosition({536.f,567.5f});
    window.draw(grid);
    window.draw(ordoo);
  probordo="3/2";
    ordoo.setString(probordo);
    ordoo.setPosition({514.f,535.f});
    grid.setPosition({536.f,535.f});
    window.draw(grid);
    window.draw(ordoo);
  probordo="7/4";
    ordoo.setString(probordo);
    ordoo.setPosition({514.f,502.5f});
    grid.setPosition({536.f,502.5f});
    window.draw(grid);
    window.draw(ordoo);
  probordo="2";
    ordoo.setString(probordo);
    ordoo.setPosition({514.f,470.f});
    grid.setPosition({536.f,470.f});
    window.draw(grid);
    window.draw(ordoo);

}

//set mes coordonnées en abscisse en fonction du nombre de bit de travail et affiche les barres de probabilités pour chaque bit classique de mon qbit------------------------------------------
void calproba::absciprob(int b,sf::RenderWindow &window){
  if (b==1){
    for (size_t i=0;i<2;i++){
      bitset<1> q(i);
      etatabs=q.to_string();
      bla.setString(etatabs);
      bla.setPosition(sf::Vector2f(40.f+i*(440.f/2),748.f));
      //bla.setRotation(-90);
      bar.setPosition(sf::Vector2f(40.f+i*(440.f/2),730.f));
      bar.setSize(sf::Vector2f(14.f,-myetat.probtot[i]*260.f));
      window.draw(bar);
      window.draw(bla);
   }
  }

  if (b==2){
    for (size_t i=0;i<4;i++){
      bitset<2> q(i);
      etatabs=q.to_string();
      bla.setString(etatabs);
      bla.setPosition(sf::Vector2f(40.f+i*(440.f/4),756.f));
      bla.setRotation(-90);
      bar.setPosition(sf::Vector2f(40.f+i*(440.f/4),730.f));
      bar.setSize(sf::Vector2f(14.f,-myetat.probtot[i]*260.f));
      window.draw(bar);
      window.draw(bla);


    }
  }

  if (b==3){
    for (size_t i=0;i<8;i++){
      bitset<3> q(i);
      etatabs=q.to_string();
      bla.setString(etatabs);
      bla.setPosition(sf::Vector2f(40.f+i*(440.f/8),758.f));
      bla.setRotation(-90);
      bar.setPosition(sf::Vector2f(40.f+i*(440.f/8),730.f));
      bar.setSize(sf::Vector2f(14.f,-myetat.probtot[i]*260.f));
      window.draw(bar);
      window.draw(bla);
   }
  }

  if (b==4){
    for (size_t i=0;i<16;i++){
      bitset<4> q(i);
      etatabs=q.to_string();
      bla.setString(etatabs);
      bla.setPosition(sf::Vector2f(25.f+i*(440.f/16),754.f));
      bla.setRotation(-55);
      bar.setPosition(sf::Vector2f(40.f+i*(440.f/16),730.f));
      bar.setSize(sf::Vector2f(10.f,-myetat.probtot[i]*260.f));
      window.draw(bar);
      window.draw(bla);
   }
  }

}

//fin méthode dessinant mes bars de proba + coordonnées en abscisse -------------------------------------------------------------------------------------------------------------------------


//set mes coordonnées en abscisse en fonction du nombre de bit de travail et affiche les barres de phases pour chaque bit classique de mon qbit------------------------------------------
void calproba::absciprobph(int b,sf::RenderWindow &window){
  if (b==1){
    for (size_t i=0;i<2;i++){
      bitset<1> q(i);
      etatabs=q.to_string();
      bla.setString(etatabs);
      bla.setPosition(sf::Vector2f(551.f+i*(440.f/2),748.f));
      bla.setRotation(-90);
      barph.setPosition(sf::Vector2f(551.f+i*(440.f/2),730.f));
      barph.setSize(sf::Vector2f(14.f,-myetat.phasetot[i]*260.f/2));
      window.draw(barph);
      window.draw(bla);
   }
  }

  if (b==2){
    for (size_t i=0;i<4;i++){
      bitset<2> q(i);
      etatabs=q.to_string();
      bla.setString(etatabs);
      bla.setPosition(sf::Vector2f(551.f+i*(440.f/4),756.f));
      bla.setRotation(-90);
      barph.setPosition(sf::Vector2f(551.f+i*(440.f/4),730.f));
      barph.setSize(sf::Vector2f(14.f,-myetat.phasetot[i]*260.f/2));
      window.draw(barph);
      window.draw(bla);


    }
  }

  if (b==3){
    for (size_t i=0;i<8;i++){
      bitset<3> q(i);
      etatabs=q.to_string();
      bla.setString(etatabs);
      bla.setPosition(sf::Vector2f(551.f+i*(440.f/8),758.f));
      bla.setRotation(-90);
      barph.setPosition(sf::Vector2f(551.f+i*(440.f/8),730.f));
      barph.setSize(sf::Vector2f(14.f,-myetat.phasetot[i]*260.f/2));
      window.draw(barph);
      window.draw(bla);
   }
  }

  if (b==4){
    for (size_t i=0;i<16;i++){
      bitset<4> q(i);
      etatabs=q.to_string();
      bla.setString(etatabs);
      bla.setPosition(sf::Vector2f(536.f+i*(440.f/16),754.f));
      bla.setRotation(-55);
      barph.setPosition(sf::Vector2f(551.f+i*(440.f/16),730.f));
      barph.setSize(sf::Vector2f(10.f,-myetat.phasetot[i]*260.f/2));
      window.draw(barph);
      window.draw(bla);
   }
  }

}
//fin méthode dessinant mes bars de phases + coordonnées en abscisse -------------------------------------------------------------------------------------------------------------------------

//on change le nombre de bit de travail et donc mon axe des absicess associé
void calproba::change_bitprob(int m){
  b=m;
  myetat.set_nbrbit(b);
  etatbit.clear();
  etatbit.resize(pow(2,b));
  for(size_t i=0;i<etatbit.size();i++){
    dynamic_bitset<> el(b,i);
    int element=el.to_ulong();
    etatbit[i]=element;
  }
}

//portes s'applique sur mon etat "myetat"
void calproba::applietat(vector<qbit> &vect){
      if(vect.size()!=0){
       for(size_t i=0;i<vect.size();i++){
        if(vect[i].ordreporte.size()!=0){
            for(size_t j=0;j<vect[i].ordreporte.size();j++){
              short int a=i;
              this->identifporte(vect[i].ordreporte[j],a);
          }
        }
      }
    }
    this->normetatt();
  }

//norme état quantique myetat
  void calproba::normetatt(){
      double sum=0.;
      for(size_t i=0;i<myetat.etatini.size();i++) {
        sum+=norm(myetat.etatini[i]);
        }
      for(auto &el : myetat.etatini){
        el=el/sum;
      }
   }

//calcul propa
void calproba::appliprob(){
  myetat.proba();
}

//calcul phase
void calproba::appliphase(){
  myetat.phase();
}

//calcul proba d'avoir un sur chaque bit
void calproba::appliprobone(){
  myetat.probone();
}


//chaque entier  correspond à un type de porte (defini dans le main avec mypo0,mypo1,....), permet d'identifier le type de porte et de l'appliquer à myetat
void calproba::identifporte(int iden,short int a){
   if(iden==0){myetat.hd(a);}
   else if(iden==1){myetat.NOT(a);}
   else if(iden==2){myetat.CNOT((a-1),a);}
   else if(iden==3){myetat.CCNOT((a-2),(a-1),a);}
   else if(iden==4){myetat.Y(a);}
   else if(iden==5){myetat.T(a);}
   else if(iden==6){myetat.S(a);}
   else if(iden==7){myetat.Z(a);}
 }
