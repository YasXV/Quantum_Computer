#include "etatquantique.h"
#include <boost/dynamic_bitset.hpp>
#include "surchargeop.h"
#include "normalisation.h"
#include "NOT2.h"
#include <vector>
#include <iostream>
#include <complex>
#include <cmath>
using namespace::std;
using namespace::boost;

 /*CONSTRUCTEUR :
 ( n : nombre de bit que l'utilisateur veut manipuler)
 (etatini : etat  quantique dans l'espace de hilbert résultant)*/
 etatquant::etatquant(long unsigned int nombrebittravail ){
    n=nombrebittravail;
    etatini=vector<complex<double>>(pow(2,n),complex<double>(0.,0.));
    etatini[0]=complex<double>(1.,0.);
}

etatquant::etatquant(){}

  void etatquant::set_nbrbit(int nbr){
      n=nbr;
      etatini.clear();
      etatini.resize(pow(2,n));
      etatini=vector<complex<double>>(pow(2,n),complex<double>(0.,0.));
      etatini[0]=complex<double>(1.,0.);
  }


  //PROBABILITES------------------------------------------------------------------------------------------------------------------------------------------------------------------


 //calcul des probas de chaque n bit de mon état quantique dans l'espace de hilbert
  void etatquant::proba() {
            probtot.clear();
            for(size_t i=0;i<etatini.size();i++){
              probtot.insert(probtot.end(),norm(etatini[i]));
            }
           }


  //calcul des phases de chaque n bit de mon état quantique dans l'espace de hilbert
  void etatquant::phase() {
            phasetot.clear();
            for(size_t i=0;i<etatini.size();i++){
              phasetot.insert(phasetot.end(),(arg(etatini[i])/M_PI));
            }

            for(size_t i=0;i<phasetot.size();i++){
              if((phasetot[i])<0){phasetot[i]+=2;}
            }
            for(size_t i=0;i<phasetot.size();i++){
              if(phasetot[i]==2 ){phasetot[i]=0;}
            }
  }

  //calcul de la probabilité d'avoir un "1" sur chaque psition a de mon n bit
  void etatquant::probone() {
            probofone.clear();
            for(size_t a=0;a<4;a++){
              double sum=0.;
              for(size_t i=0;i<etatini.size();i++){
                  dynamic_bitset<> q(n,i);
                  if (q[a]==1){sum+=norm(etatini[i]);}
              }
              probofone.insert(probofone.end(),sum);
            }
        }




  //PORTES QUANTIQUES -----------------------------------------------------------------------------------------------------------------------------------------------------

  //Porte de hadamard (nécéssaire pour la superposition d'état,agis sur le bit a)
 void etatquant::hd(short int a) {
   vector<complex<double>> stock(pow(2,n),complex<double>(0.,0.));
   ;stock=etatini;
   double coeffi=1/sqrt(2);
   for (size_t i=0 ;i<etatini.size();i++){
         size_t neww=NOT2(n,i,a);
         dynamic_bitset<> q(n,i);
         if (q[a]==0){
           etatini[i]=coeffi*stock[i]+coeffi*stock[neww];}
         else {etatini[i]=-1*coeffi*stock[i]+coeffi*stock[neww];}
   }
   normetat(etatini);
}


  //Porte NOT((X de pauli),agis sur le bit a)
  void etatquant::NOT(short int a){
       vector<complex<double>> stock(16,complex<double>(0.,0.));
      ;stock=etatini;
       for (size_t i=0;i<etatini.size();i++){
            size_t neww=NOT2(n,i,a);
            etatini[neww]=stock[i];
       }
      normetat(etatini);
  }


  //Porte CNOT(1 bit de crontrôle : ctrl | agis sur le bit a)
   void etatquant::CNOT(short int ctrl,short int a){
      vector<complex<double>> stock(16,complex<double>(0.,0.));
      ;stock=etatini;
      for (size_t i=0;i<etatini.size();i++){
            size_t neww=NOT2(n,i,a);
            dynamic_bitset<>q(n,i);
            if (q[ctrl]==1){
              etatini[neww]=stock[i];}
            else{etatini[i]=stock[i];}
      }
  }


 //Porte CCNOT(2 bit de crontrôle : ctrlu,ctrld | agis sur le bit a)
  void etatquant::CCNOT(short int ctrlu,short int ctrld,short int a){
        vector<complex<double>> stock(16,complex<double>(0.,0.));
        ;stock=etatini;
        for (size_t i=0;i<etatini.size();i++){
              dynamic_bitset<>q(n,i);
              if ((q[ctrlu]==1) & (q[ctrld]==1)){
                size_t neww=NOT2(n,i,a);
                etatini[neww]=stock[i];}
              else{etatini[i]=stock[i];}
        }
  }


  //Porte Z de pauli (agis sur le bit a)
   void etatquant::Z(short int a) {
     for (size_t i=0;i<etatini.size();i++){
       complex<double> coeffi(cos(M_PI),sin(M_PI));
       if(norm(etatini[i])!=0){
             dynamic_bitset<>q(n,i);
             if (q[a]==1){etatini[i]=coeffi*etatini[i];}
       }
     }
     normetat(etatini);
  }


  //Porte S (agis sur le bit a)
  void etatquant::S(short int a){
        complex<double> coeffi(0.,1.);
        a=a;
        for (size_t i=0;i<etatini.size();i++){
              dynamic_bitset<>q(n,i);
              if (q[a]==0){etatini[i]=etatini[i];}
              else{etatini[i]=coeffi*etatini[i];}
        }
      normetat(etatini);
  }

  //Porte T(agis sur le bit a)
  void etatquant::T(short int a){
        complex<double> coeffi(cos(M_PI/4),sin(M_PI/4));
        for (size_t i=0;i<etatini.size();i++){
              dynamic_bitset<>q(n,i);
              if (q[a]==0){etatini[i]=etatini[i];}
              else{etatini[i]=coeffi*etatini[i];}
        }
        normetat(etatini);
  }


  //Porte Y((de pauli),agis sur le bit a)
  void etatquant::Y(short int a){
        vector<complex<double>> stock(16,complex<double>(0.,0.));
        ;stock=etatini;
        complex<double> coeffi(cos(M_PI/2),sin(M_PI/2));
        complex<double> coeffi2(cos((3*M_PI)/2),sin((3*M_PI)/2));
        for (size_t i= 0;i<etatini.size();i++){
              size_t neww=NOT2(n,i,a);
              dynamic_bitset<>q(n,i);
              if (q[a]==0){etatini[neww]=coeffi*stock[i];}
              else {etatini[neww]=coeffi2*stock[i];}
        }
        normetat(etatini);
   }
