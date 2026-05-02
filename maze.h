#pragma once
#include <iostream> // za debug
#include <fstream>  //za pisanje v .svg file
#include <vector>   //za graf
#include <cstdlib>  //za rand()
#include <ctime>    //za seme za rand()
#include <set>      //za algoritem (preveri vse smeri ene celice)
#include <string>

// približek pitagorejski trojici za trikotnik 30-60-90, da nerabm uporabit decimalk
#define A 15
#define B 26
#define C 30

struct Prehod
{
    int vodi_do;
    bool odprt;
    bool obdelan;
};

struct vec2
{
    int x, y;
};

struct Celica
{
    int id;
    vec2 polozaj;
    bool explored;
    bool rob;
    Prehod prehodi[6];
};



class Maze
{
public:
    Maze(int p_n, int seed);
    Maze(int p_n, std::string &seed);

    void ExportSVG(std::string filename);
    void ExportPNG();
    void GenerirajLabirint();

private:
    std::vector<Celica> polje;
    int seme;
    int n;
    std::ofstream maze_svg;

    void NarisiLabirint(std::string filename);
    void NarisiCelico(Celica &celica);
    void NarisiRob(Celica &celica, int id_roba);
    std::pair<vec2, vec2> PolozajRoba(vec2 &polozaj_celice, int id_roba);
    vec2 PolozajOgljisca(vec2 &polozaj_celice, int id_ogljisca);

    void GenerirajPolje();
    void GenerirajLabirintRekurzivno(int zacetek, int prisel_iz_smeri);
};
