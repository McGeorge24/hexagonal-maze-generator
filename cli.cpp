#include "cli.h"

Custom_CLI::Custom_CLI(int argc, char *argv[])
{
    is_valid = true;
    if (argc < 2)
        TooLittleArguments();
    else if (argc > 8)
    {
        std::cout << "Too many arguments\n";
        PrintHelp();
    }

    HandleN(argv[1]);

    seed = time(0);
    filename = std::string("maze");

    std::string tag;
    for (int i = 2; i < argc; i += 2)
    {
        tag = std::string(argv[i]);
        if (tag == "-h")
            PrintHelp();
        else if (tag == "-s")
        {
            if (i + 1 < argc)
                HandleSeed(argv[i + 1]);
            else
                TooLittleArguments();
        }
        else if (tag == "-o")
        {
            if (i + 1 < argc)
                HandleFilename(argv[i + 1]);
            else
                TooLittleArguments();
        }
        else if (tag == "-f")
        {
            if (i + 1 < argc)
                HandleFormat(argv[i + 1]);
            else
                TooLittleArguments();
        }
    }
}

void Custom_CLI::PrintHelp()
{
    std::cout << "Use: ./maze <n> <tags> <arguments>\n";
    std::cout << "n must ALWAYS be specified. n must be an integer.\n";
    std::cout << "Tags:\n";
    std::cout << "-s      specifies seed, used to generate the maze, can be of type integer or string\n";
    std::cout << "        DEFAULT: random integer based on time\n";
    std::cout << "-o      specifies name of the output file without extension\n";
    std::cout << "        DEFAULT: maze\n";
    std::cout << "-f      specifies export format. Options: PNG, SVG";
    std::cout << "        DEFAULT: SVG\n";
    std::cout << "-h      help\n";
    is_valid = false;
}
void Custom_CLI::TooLittleArguments()
{
    std::cout << "Too litle arguments\n";
    PrintHelp();
}

void Custom_CLI::TooManyArguments()
{
    std::cout << "Too many arguments\n";
    PrintHelp();
}

void Custom_CLI::HandleFilename(char *_filename)
{
    filename = std::string(_filename);
}
void Custom_CLI::HandleSeed(char *_seed)
{
    std::string seed_str(_seed);
    try
    {
        seed = std::stoi(seed_str);
    }
    catch (const std::invalid_argument &e)
    {
        std::hash<std::string> hash_seed;
        seed = (int)hash_seed(seed_str);
    }
    catch (const std::out_of_range &e)
    {
        std::hash<std::string> hash_seed;
        seed = (int)hash_seed(seed_str);
    }
}

void Custom_CLI::HandleFormat(char *_format)
{
    return;
}

void Custom_CLI::HandleN(char *_n)
{
    std::string n_str(_n);
    try
    {
        n = std::stoi(n_str);
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << n_str << " is not an integer\n";
        std::cout << "n must ALWAYS be an integer\n";
        PrintHelp();
    }
}