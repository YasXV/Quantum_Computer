#ifndef CIRCUITCHOIX_H
#define CIRCUITCHOIX_H
#include "qbit.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>

using namespace std;

class circuitligne {
	public:
	//constructeur
	circuitligne();
	int n=0;
	//void ajout(sf::Event event,sf::RenderWindow &window);
        void drawTo(sf::RenderWindow &window);
        void setposition(sf::Vector2f position);
        void plusminussurli(sf::RenderWindow &window);
        //void getsize() const;
         void pushplusminu(sf::RenderWindow &window,sf::Event event,vector<qbit> &vect);
				 void ajout_test(vector<qbit> & vect);


	//attributss
	private:
	//vector<qbit> mylignes;
	qbit myqbit;
	sf::Sprite ajoutbit;
	sf::Sprite suppbit;
	sf::Texture text;
	sf::IntRect supp;
	sf::IntRect ajout;
	bool plus_select=false;
	bool minus_select=false;
	//sf::RectangleShape uneligne;
	sf::RectangleShape encadre;


};

#endif
