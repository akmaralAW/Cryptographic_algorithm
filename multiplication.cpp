#include "grandentier.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>

GrandEntier GrandEntier::operator*(const GrandEntier& grand_entier) const {
    GrandEntier A;
    GrandEntier B;
    GrandEntier A_high;
    GrandEntier B_high;
    GrandEntier A_low;
    GrandEntier B_low;
    GrandEntier T1;
    GrandEntier T2;
    GrandEntier T3;
    GrandEntier result;
    GrandEntier Sum_A, Sum_B, Sub;

    A = grand_entier.m_bits;
    B = m_bits;


    if ( A.m_bits.size() != B.m_bits.size() && A.m_bits.size() < B.m_bits.size()){
        int difference = B.m_bits.size()-A.m_bits.size();
        for(int i = 0; i < difference; i++){
            A.m_bits.push_back(0);
        }
    }
    if (A.m_bits.size() != B.m_bits.size() && B.m_bits.size() < A.m_bits.size()){
        int difference = A.m_bits.size()-B.m_bits.size();
        for (int j = 0; j < difference; j++){
            B.m_bits.push_back(0);
        }
    }


    double n = std::max(A.m_bits.size(), B.m_bits.size());
    if (n==0) {
        return 0; 
    }
    if (n==1) {
        unsigned  int m = A.m_bits[0]*B.m_bits[0];
        return GrandEntier(m);
    }

    reverse(A.m_bits.begin(), A.m_bits.end());
    reverse(B.m_bits.begin(), B.m_bits.end());

    double high = ceil(n/2);
    double low = floor(n/2);

    A_high.m_bits = {A.m_bits.begin(), A.m_bits.begin()+high};
    A_low.m_bits =  {A.m_bits.begin() + high, A.m_bits.end()};
    B_high.m_bits = {B.m_bits.begin(), B.m_bits.begin()+high};
    B_low.m_bits =  {B.m_bits.begin() + high, B.m_bits.end()};

    reverse(A_high.m_bits.begin(), A_high.m_bits.end());
    reverse(A_low.m_bits.begin(), A_low.m_bits.end());
    reverse(B_high.m_bits.begin(), B_high.m_bits.end());
    reverse(B_low.m_bits.begin(), B_low.m_bits.end());

    Sum_A = A_high + A_low;
    Sum_B = B_high + B_low;

    T1 = B_high*A_high;
    T2 = B_low*A_low;
    T3 = Sum_B*Sum_A;

    Sub = (T3 - T1) - T2;
    T1.shiftBits(int(2*low));
    Sub.shiftBits(int(low));
    result = T1 + Sub + T2;

    return result;

}

