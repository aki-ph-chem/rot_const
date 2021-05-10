#include<iostream>
#include<math.h>
#include<bits/stdc++.h>

int main(){


const double h = 6.62607015*pow(10,-34);

const double pi = M_PI;

const double c = 2.99792458*pow(10,10); // [cm/s]で表した光速

double result = h/(8*pi*pi*c);


std::cout<<result<<std::endl;

//calc_dbt では変換定数は 2.799275 X 10^-26




    return 0;
}