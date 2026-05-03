#pragma once
#include <string>
#include <functional>
#include <iostream>
#include <ctime>

class Custom_CLI
{
public:
    int n;
    int seed;
    std::string filename;
    int is_valid;
    Custom_CLI(int argc, char *argv[]);

private:
    void HandleArguments();
    void ConvertSeed(std::string seed);
    void PrintHelp();
    void HandleSeed(char *_seed);
    void HandleFilename(char *_filename);
    void HandleFormat(char *_format);
    void TooLittleArguments();
    void TooManyArguments();
    void HandleN(char *_n);
};