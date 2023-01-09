#include "normalisation.h"
#include <complex>
#include <vector>
#include <iostream>
using namespace ::std;

//normalise un état
void normetat(vector<complex<double>> &vect){
    double sum=0.;
    for(size_t i=0;i<vect.size();i++) {
      sum+=norm(vect[i]);
      }
    for(auto &el : vect){
      el=el/sum;
    }
 }
