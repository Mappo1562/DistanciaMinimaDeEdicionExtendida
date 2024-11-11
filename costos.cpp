#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int costo_sub(char a, char b){
    int costo;
    int auxa = static_cast<int>(a);
    int auxb = static_cast<int>(b);
    costo = auxa + 2 * auxb;
    return 1;
}

int costo_ins(char a){
    int costo;
    int aux = static_cast<int>(a);
    costo = 2 * aux;
    return 1;
}

int costo_del(char a){
    int costo;
    int aux = static_cast<int>(a);
    costo = aux/2;
    return 1;
}

int costo_trans(char a, char b){
    int costo;
    int auxa = static_cast<int>(a);
    int auxb = static_cast<int>(b);
    costo = auxa/2 + auxb/2;
    return 1;
}