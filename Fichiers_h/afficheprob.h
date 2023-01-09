#ifndef AFFICHEPROB_H
#define AFFICHEPROB_H
#include "etatquantique.h"
#include "surchargeop.h"
#include <boost/dynamic_bitset.hpp>
#include "qbit.h"
#include "portes.h"
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>

using namespace std;
using namespace ::boost;

class calproba{
        public:
        calproba(int numberbit);
        void change_bitprob(int m);
        void identifporte(int iden, short int a);
        void applietat(vector<qbit> &vect);
        void appliprob();
        void appliphase();
        void appliprobone();
        void absciprob(int b,sf::RenderWindow &window);
        void absciprobph(int b,sf::RenderWindow &window);
        void ordonne(sf::RenderWindow &window);
        void ordonneph(sf::RenderWindow &window);
        etatquant myetat;
        vector<int> etatbit;
        void normetatt();


        private:
        int b;
        string etatabs;
        string probordo;
        sf::Font myfont;
        sf::Text bla;
        sf::Text ordoo;
        sf::RectangleShape bar;
        sf::RectangleShape barph;
        sf::RectangleShape grid;


};

#endif
