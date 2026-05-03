#include "cli.h"
#include "maze.h"

int main(int argc, char *argv[])
{
    Custom_CLI cli(argc, argv);
    if (cli.is_valid)
    {
        Maze labirint(cli.n, cli.seed);
        labirint.GenerirajLabirint();
        labirint.ExportSVG(cli.filename);
    }

    return 0;
}