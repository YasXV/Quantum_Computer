#include "NOT2.h"
#include<boost/dynamic_bitset.hpp>
#include <vector>

using namespace std;


size_t NOT2(long unsigned int n,size_t i, short int a){
        boost::dynamic_bitset<> q(n,i);
        q.flip(a);
        a=a;
        size_t b=q.to_ulong();
        return b;
        }
