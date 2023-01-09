#include "surchargeop.h"
#include <complex>
#include <iostream>

using namespace std;

const complex<double> operator*(const double& d,complex<double> const& z2){
  return complex<double>(d*z2.real(),d*z2.imag());}

const complex<double> operator*(complex<double> const& z2,const double &d){
  return d*z2;
  }
