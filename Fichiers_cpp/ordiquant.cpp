#include "etatquantique.h"
#include <boost/dynamic_bitset.hpp>
#include "NOT2.h"
#include "normalisation.h"
#include "surchargeop.h"
#include "portes.h"
#include "qbit.h"
#include "circuitchoix.h"
#include "afficheprob.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>
#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;


//les portes ajouteées sur chaque ligne (une ligne =vect[i]=un qbit) se place les unes aprés les autres !
void replacementt(vector<qbit> &vect){
      for(size_t i=0;i<vect.size();i++){
         if(vect[i].sprligne.size()!=0){
           for(size_t j=0;j<vect[i].sprligne.size();j++) {
            vect[i].sprligne[j].setPosition({vect[i].getx()+25.f+j*64.f,vect[i].gety()});
           }
         }
       }
    }


//la porte s'efface si on clique sur le bouton right
void effacement(vector<qbit> &vect,sf::Event event,sf::RenderWindow &window){
  if(vect.size()!=0){
    for(size_t i=0;i<vect.size();i++){
      for(size_t j=0;j<vect[i].sprligne.size();j++){
      if(vect[i].sprligne[j].getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y)){
        if(event.type==sf::Event::MouseButtonPressed){
          if(event.mouseButton.button==sf::Mouse::Right){
          vect[i].sprligne.erase(vect[i].sprligne.begin()+j);
          vect[i].ordreporte.erase(vect[i].ordreporte.begin()+j);

          }
        }
      }
     }
    }
  }
}


 void normetat(vector<double> &vect){//normalise un vecteur ; utilisé pour normaliser les probabilités
     double sum=0.;
     for(size_t i=0;i<vect.size();i++) {
       sum+=norm(vect[i]);
       }
     for(auto &el : vect){
       el=el/sum;
     }
  }



sf::RenderWindow window;//création de ma fenêtre
sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
sf::RectangleShape headd;//entete
sf::RectangleShape separporte;//rectangle contenant mes portes
sf::RectangleShape separcircuit;//rectangle contenant mon circuit
sf::Font font;//font utilisée pour les nombreux titres
sf::Text text;//Entête
sf::Text probtext;//titre graphe proba
sf::Text phasetext;//titre graphe phase
sf::RectangleShape graphe;//boite contenant le graphe des probas
sf::RectangleShape absc;//abscisse de mon graphe
sf::RectangleShape ordo;//ordonnée de mon graphe
sf::RectangleShape graphepha;//boite contenant mon graphe de phase
sf::RectangleShape abscp;//abscisse de mon graphe
sf::RectangleShape ordop;//ordonnée de mon graphe


circuitligne circuit;//création de  mes boutons "+" et "-"

//création des portes
portes mypo0(0);
portes mypo1(1);
portes mypo2(2);
portes mypo3(3);
portes mypo4(4);
portes mypo5(5);
portes mypo6(6);
portes mypo7(7);

//création de mon vecteur de qbit qb initial ( on a un bit initialement )
vector<qbit> qb;
qbit myqbit(0);
calproba myprob(qb.size());//création d'un élement de la classe calproba qui crée un état initial  en fonction de qb et nous permettra de déterminer les probas/phases

//-----------------MAIN---------------------------------------------------------------------------------------------------------------------------------------------
int main(){

//load du font et Set des propriétes de mes textes
  if (!font.loadFromFile("../Sprites/LikhanNormal.ttf")){
      return EXIT_FAILURE;
  }

//Création de la fenêtre et de ses éléments statiques--------------------------------------------------------------------------------------------------------------------------------------


text.setFont(font);
text.setString("Quantum Composer");
text.setCharacterSize(40);
text.setFillColor(sf::Color::White);

//entête texte graphe proba
probtext.setFont(font);
probtext.setString("Probabilities of computational states");
probtext.setCharacterSize(18);
probtext.setFillColor(sf::Color(47,79,79));
probtext.setPosition(sf::Vector2f(5.f,412.f));
//probtext.setRotation(90);

//entête texte graphe phase
phasetext.setFont(font);
phasetext.setString("Phases of computational states [x pi]");
phasetext.setCharacterSize(18);
phasetext.setFillColor(sf::Color(47,79,79));
phasetext.setPosition(sf::Vector2f(516.f,412.f));
//phasetext.setRotation(90);

//Positionement de mes portes
mypo0.setposition({100.f,105.f});
mypo1.setposition({170.f,105.f});
mypo2.setposition({240.f,105.f});
mypo3.setposition({310.f,105.f});
mypo4.setposition({380.f,105.f});
mypo5.setposition({450.f,105.f});
mypo6.setposition({520.f,105.f});
mypo7.setposition({590.f,105.f});


//Positionement de mes boutons "+" et "-" de mon circuit
circuit.setposition({21.f,175.f});

//qbit(ligne de circuit initiale à l'entrée dans mon interface), qb=vect(vecteur de qbit)
myqbit.setposition({46.f,212.f});
qb.push_back(myqbit);


//entête
headd.setSize(sf::Vector2f(desktop.width,60));
headd.setFillColor(sf::Color::Black);

//rectangle qui délimite le graphe de proba
graphe.setSize(sf::Vector2f(500.f,329.f));
graphe.setPosition(5.f,435.f);
graphe.setFillColor(sf::Color::Transparent);
graphe.setOutlineColor(sf::Color(128,128,128,120));
graphe.setOutlineThickness(3);

//rectangle qui délimite le graphe des phases
graphepha.setSize(sf::Vector2f(500.f,329.f));
graphepha.setPosition(516.f,435.f);
graphepha.setFillColor(sf::Color::Transparent);
graphepha.setOutlineColor(sf::Color(128,128,128,120));
graphepha.setOutlineThickness(3);

//abscisse de mon graphe de proba
absc.setFillColor(sf::Color(0,0,0,100));
absc.setPosition({25.f,730.f});
absc.setSize(sf::Vector2f(470.f,3.f));

//abscisse de mon graphe de phase
abscp.setFillColor(sf::Color(0,0,0,100));
abscp.setPosition({536.f,730.f});
abscp.setSize(sf::Vector2f(470.f,3.f));

//ordonnée de mon graphe de proba
ordo.setOrigin({ordo.getLocalBounds().width/2,0});
ordo.setFillColor(sf::Color(0,0,0,100));
ordo.setSize(sf::Vector2f(3.f,285.f));
ordo.setPosition({25.f,445.f});

//ordonnée de mon graphe de phase
ordop.setOrigin({ordop.getLocalBounds().width/2,0});
ordop.setFillColor(sf::Color(0,0,0,100));
ordop.setSize(sf::Vector2f(3.f,285.f));
ordop.setPosition({536.f,445.f});

//Rectangle qui sépare la zone où sont situer les portes
separporte.setPosition({5.f,70.f});
separporte.setSize(sf::Vector2f(1010,70));
separporte.setFillColor(sf::Color::Transparent);
separporte.setOutlineColor(sf::Color(128,128,128,120));
separporte.setOutlineThickness(3);

//Rectangle qui sépare la zone où sont situer les lignes de circuits
separcircuit.setSize(sf::Vector2f(1010,255));
separcircuit.setPosition(5.f,155.f);
separcircuit.setFillColor(sf::Color::Transparent);
separcircuit.setOutlineColor(sf::Color(128,128,128,120));
separcircuit.setOutlineThickness(3);

//fenêtre
window.create(sf::VideoMode(1024,768),"Yas's Cat");//création de la fenêtre
window.setFramerateLimit(60);
window.setVerticalSyncEnabled(true);

//set l'icône de la fenêtre
sf::Image icon;
 if(!icon.loadFromFile("../Sprites/chat.png")){
   cout<<"EXIT_FAILUREé"<<endl;
 }

 window.setIcon(66,66,icon.getPixelsPtr());

//Tant que la fenêtre est ouverte------------------------------------------------------------------------------------------------------------------------
while(window.isOpen()){

   int b=1;
   sf::Event event;
   //Test des événements-------------------------------------------------------------------------------------------------------------------------------
   while(window.pollEvent(event)){
     //si on clique fermer
     if(event.type==sf::Event::Closed){
         window.close();
       }//la fenêtre se ferme

     //drag and drop des portes
     mypo0.dragandDrop(event,window);
     mypo1.dragandDrop(event,window);
     mypo2.dragandDrop(event,window);
     mypo3.dragandDrop(event,window);
     mypo4.dragandDrop(event,window);
     mypo5.dragandDrop(event,window);
     mypo6.dragandDrop(event,window);
     mypo7.dragandDrop(event,window);
     mypo0.totraycast(qb,event);
     mypo1.totraycast(qb,event);
     mypo2.totraycast(qb,event);
     mypo3.totraycast(qb,event);
     mypo4.totraycast(qb,event);
     mypo5.totraycast(qb,event);
     mypo6.totraycast(qb,event);
     mypo7.totraycast(qb,event);

     //surlignage des boutons "+" et "-"
     circuit.pushplusminu(window,event,qb);

     effacement(qb,event,window);//les portes s'effacent si on clique sur le bouton :Right sur une porte


    }//fin test des événements-------------------------------------------------------------------------------------------------------------------------------------------------------------

    circuit.ajout_test(qb);// ajoute/enléve une ligne de circuit(donc qbit) lorsque j'appuie sur "+"/"-"
    circuit.plusminussurli(window);// surlignage  de mes boutons "+" et "-" dans mon interface quand je passe dessus

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){window.close();}//si on clique sur echap, la fenêtre se ferme
    if(qb.size()>4){window.close();}// si l'utilisateur veux utiliser plus de 4 qbit alors la fenêtre se ferme automatiquement

    //quand une porte arrive au niveau d'une ligne de circuit, le raycast de celui-ci est surligné
    mypo0.surliraycast(qb);
    mypo1.surliraycast(qb);
    mypo2.surliraycast(qb);
    mypo3.surliraycast(qb);
    mypo4.surliraycast(qb);
    mypo5.surliraycast(qb);
    mypo6.surliraycast(qb);
    mypo7.surliraycast(qb);

    //mes portes follow ma souris quand je les prends
    mypo0.follow(window);
    mypo1.follow(window);
    mypo2.follow(window);
    mypo3.follow(window);
    mypo4.follow(window);
    mypo5.follow(window);
    mypo6.follow(window);
    mypo7.follow(window);

    replacementt(qb);//les portes se replacent les unes à côté des autres sur ma ligne de circuit !
    myprob.change_bitprob(qb.size());//change la taille de bit et donc le vecteur associé en fonction de qb!
    myprob.applietat(qb);//applique les portes su rmon état quantique
    myprob.normetatt();//normalise mon état qauntique
    myprob.appliprob();//calcule les probas de mon état quantique!
    myprob.appliphase();//calcule les phases de mon état quantique!
    myprob.appliprobone();//calcule les probas d'avoi un "1" sur chaque position de qbit!

    //surlignage des portes et affichage de leurs noms lorsque je passe dessus
    mypo0.surliportes(window);
    mypo1.surliportes(window);
    mypo2.surliportes(window);
    mypo3.surliportes(window);
    mypo4.surliportes(window);
    mypo5.surliportes(window);
    mypo6.surliportes(window);
    mypo7.surliportes(window);


  window.clear(sf::Color::White);//fond blanc

  //dessin de mes lignes de circuit (et donc qbit) !
  for (int l=0;l<qb.size();l++){
    qb[l].drawTo(window);
  }


  //draw des eléments statiques de mon interface--------------------------------------------------------------------------------------------------------------------------
  window.draw(headd);
  window.draw(text);
  window.draw(separporte);
  window.draw(separcircuit);
  window.draw(graphe);
  window.draw(ordo);
  window.draw(absc);
  window.draw(ordop);
  window.draw(abscp);
  window.draw(graphepha);
  window.draw(phasetext);
  window.draw(probtext);


  myprob.ordonne(window);//affiche les ordonnées dans mon graphe de proba
  myprob.absciprob(qb.size(),window);// dessine mes valeurs en abscisse en fonction de qb.size() ainsi que les bars de proba
  myprob.ordonneph(window);//dessinne mes ordonnes de phase
  myprob.absciprobph(qb.size(),window); //dessine les coordonnées  de mon absci de phase en fonction de qb.size() ainsi que les bars de proba

  //affichage du nom des portes quand je passe dessus
  mypo0.surliportes(window);
  mypo1.surliportes(window);
  mypo2.surliportes(window);
  mypo3.surliportes(window);
  mypo4.surliportes(window);
  mypo5.surliportes(window);
  mypo6.surliportes(window);
  mypo7.surliportes(window);

  //draw des boutons "+" et "-"
  circuit.drawTo(window);
  //draw des portes
  mypo0.drawTo(window);
  mypo1.drawTo(window);
  mypo2.drawTo(window);
  mypo3.drawTo(window);
  mypo4.drawTo(window);
  mypo5.drawTo(window);
  mypo6.drawTo(window);
  mypo7.drawTo(window);
  window.display();//on display le tout


}//fin boucle window.ispoen()


return 0; }
