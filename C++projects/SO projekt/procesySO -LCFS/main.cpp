#include <iostream>
#include "procesy.h"
#include <algorithm>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>

using namespace std;

bool sortowanie2(const Procesy & l, const Procesy &r )
{
    return l.czas_przyjscia<r.czas_przyjscia;
}
int main()
{
    srand(time(NULL));
    Procesy test;
    test.tworz_zapisz();
    test.wczytaj();
    sort(test.dane.begin(), test.dane.end(), sortowanie2);//sortowanie po czasie przyjœcia
    test.wypisz();

    //ALGORYTM LCFS
    float dzialanie=0;
    float czekanie=0;
    int g=0;//takt procesora
    int minimum;
    int indeks;//indeks el. który ma się wykonać
    vector<int>lista_wykonanie;
    vector<string>lista_nazw;
    int y=test.dane.size();//uzywam stalej bo vektor zmienia swoja wielkosc
    for(int h=0; h<y; h++)//pêtla po iloœci procesow
    {
        if(test.dane.empty()==true)
        {
            break;
        }
        if(test.dane[h].czas_przyjscia<=g)
        {
            for(unsigned int w=0; w<test.dane.size(); w++)
            {
                if(test.dane[w].czas_przyjscia<=g)
                {
                    lista_wykonanie.push_back(test.dane[w].czas_wykonania);
                    lista_nazw.push_back(test.dane[w].nazwa);
                    indeks=w;
                }
            }
            g=g+test.dane[indeks].czas_wykonania;
            cout<<endl;
            cout<<"-->Process name: "<<lista_nazw[indeks]<<"      Execution time: "<<test.dane[indeks].czas_wykonania<<"s"<<endl;
            cout<<"Processing...";
            Sleep(test.dane[indeks].czas_wykonania*1000);
            dzialanie=dzialanie+test.dane[indeks].czas_wykonania;
            cout<<"End"<<endl;
            test.dane.erase(test.dane.begin()+indeks);
            lista_nazw.clear();
            lista_wykonanie.clear();
            h=-1;
        }
        else
        {
            cout<<endl;
            cout<<"Waiting for process..."<<test.dane[h].czas_przyjscia-g<<"s"<<endl;
            Sleep((test.dane[h].czas_przyjscia-g)*1000);
            czekanie=czekanie+test.dane[h].czas_przyjscia-g;
            g=test.dane[h].czas_przyjscia;
            h--;
        }
    }
    cout<<"Total time of served: "<<g<<"s"<<endl;
    cout<<"Average execution time per one process: "<<dzialanie/y<<"s"<<endl;
    cout<<"Average waiting time per one process: "<<czekanie/y<<"s"<<endl;
    ofstream wyniki;
    wyniki.open("wyniki_test1.txt",ios::out);
        wyniki<<"Total time of served: "<<g<<"s"<<endl;
        wyniki<<"Average execution time per one process: "<<dzialanie/y<<"s"<<endl;
        wyniki<<"Average waiting time per one process: "<<czekanie/y<<"s"<<endl;

    wyniki.close();
    return 0;
}
