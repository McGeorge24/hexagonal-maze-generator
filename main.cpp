#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>

#define A 15
#define B 26
#define C 30

/*
| šestkotnik (vrednosti stranic): (v resnici je zarotirano za 30° v levo)
|    0->  __
|   1->  /  \  <-5
|   2->  \__/  <-4
|         3^
*/

void Stena(int p, int q, int stranica, std::ostream &maze)
{
    int x1, x2, y1, y2;
    switch (stranica)
    {
    case 0:
        x1 = p;
        y1 = q - C;
        x2 = p - B;
        y2 = q - A;
        break;
    case 1:
        x1 = p - B;
        y1 = q - A;
        x2 = p - B;
        y2 = q + A;
        break;
    case 2:
        x1 = p - B;
        y1 = q + A;
        x2 = p;
        y2 = q + C;
        break;
    case 3:
        x1 = p;
        y1 = q + C;
        x2 = p + B;
        y2 = q + A;
        break;
    case 4:
        x1 = p + B;
        y1 = q + A;
        x2 = p + B;
        y2 = q - A;
        break;
    case 5:
        x1 = p + B;
        y1 = q - A;
        x2 = p;
        y2 = q - C;
        break;
    default:
        std::cout << "[NAPAKA]: Neveljavna vrednost stranice, mora biti med 0 in 5\n";
        break;
    }

    maze << "<line x1=\"" << x1 << "\" x2=\"" << x2 << "\" y1=\"" << y1 << "\" y2=\"" << y2 << "\" ";
    maze << "stroke=\"black\" stroke-width=\"2\"/>";
}

struct Prehod
{
    int vodi_do;
    bool odprt;
    bool obdelan;
};

struct Celica
{
    int id;
    int x, y;
    bool explored;
    bool rob;
    Prehod prehodi[6];
};

void GenerirajPolje(int n, std::vector<Celica> &polje)
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
            temp_celica.x = x + j * 2 * B;
            temp_celica.y = y;

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
                temp_celica.prehodi[0] = temp_prehod;
                temp_celica.prehodi[1] = temp_prehod;
                temp_celica.prehodi[2] = temp_prehod;
                temp_celica.prehodi[3] = temp_prehod;
                temp_celica.prehodi[4] = temp_prehod;
                temp_celica.prehodi[5] = temp_prehod;
            }
            polje.push_back(temp_celica);
            k++;
        }
        if (i >= n - 1)
            delta = -1;
        vrstica += delta;
        w += delta;
    }
}

void GenerirajLabirint(int zacetek, std::vector<Celica> &polje)
{
    int smer;
    int nov_zacetek;
    bool najdeno_polje = false;
    std::cout << "celica: " << zacetek << std::endl;
    std::set<int> raziskane_poti;
    while (raziskane_poti.size() < 6)
    {
        smer = rand() % 6;
        raziskane_poti.insert(smer);
        nov_zacetek = polje[zacetek].prehodi[smer].vodi_do;
        std::cout << "\tsmer: " << smer << std::endl;
        std::cout << "\tvodi do: " << nov_zacetek << std::endl;
        std::cout << "\t\trob=" << polje[nov_zacetek].rob << ", explored=" << polje[nov_zacetek].explored << std::endl;
        if ((polje[nov_zacetek].rob == false) && (polje[nov_zacetek].explored == false))
        {
            polje[zacetek].prehodi[smer].odprt = true;
            polje[nov_zacetek].explored = true;
            polje[nov_zacetek].prehodi[(3 + smer) % 6].odprt = true;
            najdeno_polje = true;
            std::cout << "naslednja!" << std::endl;
            GenerirajLabirint(nov_zacetek, polje);
        }
    }
}

int main()
{
    int n = 10;

    std::vector<Celica> polje;
    GenerirajPolje(n, polje);

    int width = 100 + (2 * n - 1) * B * 2;
    int height = 100 + (2 * n - 1) * A * 3 + A;
    // int r = 25 + (2 * n - 1) * B;

    std::ofstream maze_svg("maze.svg", std::fstream::trunc);
    // specifikacije SVG slike
    maze_svg << "<svg version=\"1.1\" width=\"" << width << "\" height=\"" << height << "\" xmlns=\"http://www.w3.org/2000/svg\">";
    // ozadje
    maze_svg << "<rect width=\"100%\" height=\"100%\" fill=\"white\"/>";
    // maze_svg << "<circle cx=\"" << width / 2 << "\" cy=\"" << height / 2 << "\" r=\"" << r << "\" fill=\"white\"/>";

    srand(time(0));
    polje[n + 1].explored = true;
    polje[n + 1].prehodi[0].odprt = true;
    polje[polje.size() - n - 1].prehodi[4].odprt = true;
    GenerirajLabirint(n + 2, polje);
    for (int i = 0; i < polje.size(); i++)
    {
        std::cout << "celica: " << i << ":: ";
        for (int j = 0; j < 6; j++)
        {
            std::cout << polje[i].prehodi[j].vodi_do << " ";
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < polje.size(); i++)
    {
        if (polje[i].rob)
            continue;
        for (int j = 0; j < 6; j++)
        {
            if (polje[i].prehodi[j].odprt == false)
                Stena(polje[i].x, polje[i].y, j, maze_svg);
        }
    }

    maze_svg << "</svg>";
    maze_svg.close();

    return 0;
}