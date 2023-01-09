#ifndef ETATQUANTIQUE_H
#define ETATQUANTIQUE_H
#include <vector>
#include <complex>
using namespace std;

class etatquant{
   public:
     //constructeur
     etatquant(long unsigned int nombrebittravail);
     etatquant();// 2nd constructeur utile pour changer le nombre de bit à travers une méthode

     //proba
     void proba() ;
     void phase() ;
     void probone() ;

     //Portes
     void hd(short int a);
     void NOT(short int a);
     void CNOT(short int ctrl,short int a);
     void CCNOT(short int ctrlu,short int ctrld,short int a);
     void Z(short int a);
     void S(short int a);
     void T(short int a);
     void Y(short int a);

     //probas
     vector<double> probtot;
     vector<complex<double>> etatini;
     vector<double> phasetot;
     vector <double> probofone;
     //Changer le nombre de bit de travail
     void set_nbrbit(int nbr);

   //Attributs
   private:
   long unsigned int n;

};

#endif
