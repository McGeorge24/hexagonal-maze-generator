#include "maze.h"

/*
| šestkotnik (vrednosti stranic): (v resnici je zarotirano za 30° v levo)
|    0->  __
|   1->  /  \  <-5
|   2->  \__/  <-4
|         3^
*/

// relativne koordinate ogljisca
vec2 ogljisce_relativno[6] = {{0, -C}, {-B, -A}, {-B, A}, {0, C}, {B, A}, {B, -A}};

vec2 Maze::PolozajOgljisca(vec2 &polozaj_celice, int id_ogljisca)
{
    int x = polozaj_celice.x + ogljisce_relativno[id_ogljisca].x;
    int y = polozaj_celice.y + ogljisce_relativno[id_ogljisca].y;
    return {x, y};
}

std::pair<vec2, vec2> Maze::PolozajRoba(vec2 &polozaj_celice, int id_roba)
{
    vec2 zacetek = PolozajOgljisca(polozaj_celice, id_roba);
    vec2 konec = PolozajOgljisca(polozaj_celice, (id_roba + 1) % 6);
    return std::make_pair(zacetek, konec);
}

void Maze::NarisiRob(Celica &celica, int id_roba)
{

    std::pair rob = PolozajRoba(celica.polozaj, id_roba);

    maze_svg << "<line x1=\"" << rob.first.x << "\" x2=\"" << rob.second.x << "\" ";
    maze_svg << "y1=\"" << rob.first.y << "\" y2=\"" << rob.second.y << "\" ";
    maze_svg << "stroke=\"black\" stroke-width=\"5\" stroke-linecap=\"round\"/>\n";
}

void Maze::NarisiCelico(Celica &celica)
{
    for (int i = 0; i < 6; i++)
    {
        if ((celica.prehodi[i].obdelan == false) && (celica.prehodi[i].odprt == false))
        {
            NarisiRob(celica, i);
            // da ne narisem robov 2x, potem je tudi datoteka 2x manjsa
            polje[celica.prehodi[i].vodi_do].prehodi[(3 + i) % 6].obdelan = true;
        }
    }
}

void Maze::NarisiLabirint(std::string filename)
{
    int width = 100 + (2 * n - 1) * B * 2;
    int height = 100 + (2 * n - 1) * A * 3 + A;

    maze_svg = std::ofstream(filename, std::fstream::trunc);

    // specifikacije SVG slike
    maze_svg << "<svg version=\"1.1\" width=\"" << width << "\" ";
    maze_svg << "height=\"" << height << "\" ";
    maze_svg << "xmlns=\"http://www.w3.org/2000/svg\">\n";

    // ozadje
    maze_svg << "<rect width=\"100%\" height=\"100%\" fill=\"white\"/>\n";

    for (int i = 0; i < polje.size(); i++)
    {
        if (polje[i].rob == false)
            NarisiCelico(polje[i]);
    }

    maze_svg << "</svg>";
    maze_svg.close();
}

void Maze::ExportSVG(std::string filename)
{
    NarisiLabirint(filename);
}

void Maze::GenerirajPolje()
{
    // rob okrog, ki nam pove da je konec labirinta
    n += 1;
    // maksimalna širina vrstice in število stolpcev
    int premer = 2 * n - 1;

    // koordinata celice (vrstica, stolpec, zaporedno število)
    int i, j;
    int k = 0;

    // p,q: koordinati začetnega polja;
    int p = 50 + (n - 2) * B; // n-2 zaradi roba
    int q = 50 - A;           // spet C-3A (ali -A) zaradi roba
    // x,y: koordinati prvega polja v vrstici
    int x, y;

    // velikost vrstice
    int vrstica = n;
    // sprememba dolzine vrstice (lahko +1/-1)
    int delta = 1;
    int w = 0; // ekvivalentno vodoravnemu zamiku prvega lika v vrstici

    // id prve celice v (trenutni, prejsnji, naslednji)
    // (pomembno za dolocanje sosedov)
    int prva = 0;
    int prva_prej = 0;
    int prva_sledi = 0;

    Celica temp_celica;
    temp_celica.explored = false;
    Prehod temp_prehod;
    temp_prehod.obdelan = false;
    temp_prehod.odprt = false;
    temp_prehod.vodi_do = 0;
    for (i = 0; i < premer; i++)
    {
        x = p - w * B;
        y = q + i * 3 * A;
        prva_prej = prva;
        prva = prva_sledi;
        prva_sledi = k + vrstica;
        for (j = 0; j < vrstica; j++)
        {
            temp_celica.id = k;
            temp_celica.polozaj.x = x + j * 2 * B;
            temp_celica.polozaj.y = y;

            // dolocanje_roba
            if ((i == 0) || (i == premer - 1) || (j == 0) || (j == vrstica - 1))
                temp_celica.rob = true;
            else
                temp_celica.rob = false;

            if (temp_celica.rob == false)
            {
                // zgornja soseda
                if (delta == 1)
                    temp_prehod.vodi_do = prva_prej + j - 1;
                else
                    temp_prehod.vodi_do = prva_prej + j;
                // zgornja soseda
                temp_celica.prehodi[0] = temp_prehod;
                temp_prehod.vodi_do += 1;
                temp_celica.prehodi[5] = temp_prehod;

                // soseda v isti vrstici
                temp_prehod.vodi_do = k - 1;
                temp_celica.prehodi[1] = temp_prehod;
                temp_prehod.vodi_do = k + 1;
                temp_celica.prehodi[4] = temp_prehod;

                // spodnja soseda
                if (i >= n - 1)
                    temp_prehod.vodi_do = prva_sledi + j - 1;
                else
                    temp_prehod.vodi_do = prva_sledi + j;
                temp_celica.prehodi[2] = temp_prehod;
                temp_prehod.vodi_do += 1;
                temp_celica.prehodi[3] = temp_prehod;
            }
            else
            {
                temp_prehod.vodi_do = 0;
                for (int l = 0; l < 6; l++)
                    temp_celica.prehodi[l] = temp_prehod;
            }
            polje.push_back(temp_celica);
            k++;
        }
        if (i >= n - 1)
            delta = -1;
        vrstica += delta;
        w += delta;
    }

    n -= 1;
}

void Maze::GenerirajLabirintRekurzivno(int zacetek, int prisel_iz_smeri)
{
    int smer;
    int nov_zacetek;
    std::set<int> raziskane_poti;
    polje[zacetek].explored = true;
    polje[zacetek].prehodi[prisel_iz_smeri].odprt = true;

    while (raziskane_poti.size() < 6)
    {
        smer = rand() % 6;
        raziskane_poti.insert(smer);
        nov_zacetek = polje[zacetek].prehodi[smer].vodi_do;
        if ((polje[nov_zacetek].rob == false) && (polje[nov_zacetek].explored == false))
        {
            polje[zacetek].prehodi[smer].odprt = true;
            GenerirajLabirintRekurzivno(nov_zacetek, (3 + smer) % 6);
        }
    }
}

void Maze::GenerirajLabirint()
{
    srand(seme);
    GenerirajLabirintRekurzivno(n + 2, 0);
}

Maze::Maze(int p_n, int seed)
{
    n = p_n;
    seme = seed;
    GenerirajPolje();
}

int main()
{
    int n = 9;
    int seme = time(0);
    // polje[polje.size() - n - 3].prehodi[3].odprt = true;
    Maze labirint(n, seme);
    labirint.GenerirajLabirint();
    labirint.ExportSVG("nov_labirint.svg");

    return 0;
}