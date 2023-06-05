#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <string>
#include "vector.h"
using namespace std;


int main() {
  try{
    Vector<string> v{"abc", "efg", "hij", "klm"};//Vector mit Werten

    cout << v << '\n';

    double sum{0};

    Vector<int> v1;//leerer Vector
    Vector<int> v2(0);//Vector mit Größe
    Vector<int> v3({1, 4, 3, 4, 5, 6, 7, 10});//Vector mit Werten
    Vector<double> v4({0,1,2,3,4,5,6,7,8,9});//Kopierkonstruktor
    const Vector<int> v5({0,1,2,3,4,5,6,7,8,9});//const Vector
    Vector<double> v6{v4};//Kopie

    for(auto it{v4.begin()}; it != v4.end(); ++it)
      sum += *it;

    cout << "sum = " << sum << '\n';
  }

  catch(runtime_error& e){
    cerr << "Sorry: " << e.what() << '\n';
  }

  return 0;
}
