#include <iostream>
#include <map>
#include <sstream>
#include <random>
#include <fstream>

using namespace std;

map<int, string> entrada;
map<int, string> sortida;

string nomfitxer;

ofstream arxiu;

bool es_signe(char c) {
    return c == '.' or c == '?' or c == '!' or c == ',' or c == ';' or c == ':';
}

void llegir_entrada() {
    string aux;
    getline(cin, aux);
    int cont = 0;
    arxiu << aux << endl;
    arxiu.flush();
    while (aux != "****") {
        if (aux.size() > 0) {
            istringstream iss(aux);
            string paraula;
            while (iss >> paraula) {
                if (es_signe(paraula.back())) paraula.pop_back();
                entrada[cont] = paraula;
                ++cont;
            }
        }
        getline(cin, aux);
        arxiu << aux << endl;
        arxiu.flush();
    }
}

void llegir_sortida() {
    string paraula;
    getline(cin, paraula);
    int cont = 0;
    while (paraula != "****") {
        sortida[cont] = paraula;
        ++cont;
        getline(cin, paraula);
    }
}

int numero_aleatori(int ranga, int rangb) {
    random_device generador;
    uniform_int_distribution<int> distribution(ranga, rangb);
    return distribution(generador);
}

void genera_espais(string &a) {
    int nespais = numero_aleatori(0, 5);
    while (nespais >= 0) {
        a.push_back(' ');
        --nespais;
    }
}

string conjunt() {
    string res;
    res.push_back('{');
    int nparaules = numero_aleatori(1, 20);
    while (nparaules > 0) {
        int index = numero_aleatori(0, entrada.size() - 1);
        genera_espais(res);
        if (res.back() != ' ') res.push_back(' ');
        if (index % 101 == 0 and index < sortida.size()) res += sortida[index];
        else res += entrada[index];
        --nparaules;
    }
    genera_espais(res);
    res.push_back('}');
    return res;
}

string sequencia() {
    string res;
    res.push_back('"');
    int nparaules = numero_aleatori(1, 20);
    while (nparaules > 0) {
        int index = numero_aleatori(0, entrada.size() - 1);
        genera_espais(res);
        if (res.back() != ' ') res.push_back(' ');
        if (index % 101 == 0 and index < sortida.size()) res += sortida[index];
        else res += entrada[index];
        --nparaules;
    }
    genera_espais(res);
    res.push_back('"');
    return res;
}

string recursiva(int nodes) {
    string res;
    if (nodes != 0) {
        int nfille = numero_aleatori(0, nodes);
        int nfilld = nodes - nfille;
        if (nodes == 1) nfilld = nfille = 0;
        string e, d;
        int op = numero_aleatori(0, 1);
        e = recursiva(nfille);
        d = recursiva(nfilld);
        res.push_back('(');
        genera_espais(res);
        res += e;
        genera_espais(res);
        if (op == 0) res.push_back('|');
        else res.push_back('&');
        genera_espais(res);
        res += d;
        genera_espais(res);
        res.push_back(')');
    }
    else res = conjunt();
    return res;
}

void frases() {
    int op = numero_aleatori(0, 2);
    if (op == 0) arxiu << "frases " << recursiva(numero_aleatori(1, 10));
    else if (op == 1) arxiu << "frases " << sequencia();
    else if (op == 2) arxiu << "frases " << conjunt();
    int espais = numero_aleatori(2, 100);
    for (int i = 0; i < espais; ++i) arxiu << ' ';
    if (numero_aleatori(0, 1) == 1) arxiu << '?';
    arxiu << endl;
}


int main() {
    cout << "Introdueix el nom del fitxer :" << endl;
    cin >> nomfitxer;
    arxiu.open(nomfitxer, ios::app);
    arxiu << "afegir text " << '"' << "Prova" << '"' << endl;
    arxiu << "autor " << '"' << "Pau" << '"' << endl;
    arxiu.flush();
    cout << "Introdueix el contingut del text :" << endl;
    llegir_entrada();
    arxiu << "triar text {Pau}" << endl;
    arxiu.flush();
    cout << "Introdueix les paraules de prova :" << endl;
    llegir_sortida();
    cout << "Introdueix el nombre de instruccions :" << endl;
    int cont;
    cin >> cont;
    while (cont > 0) {
        frases();
        --cont;
    }
    arxiu << "sortir" << endl;
    arxiu.close();
}