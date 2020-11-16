#include <getopt.h>
#include "sysy2eeyore/globals.hpp"
#include "sysy2eeyore/tree.hpp"
#include "source.tab.hpp"

extern FILE* yyin;
extern NCompUnit* parse();

string in_file;
string out_file;

bool compileEeyore, compileTigger, compileRISCV;

void compileToEeyore()
{
    yyin = fopen(in_file.c_str(), "r");
    auto root = parse();
    root->print();
    return;
}

int main(int argc, char * argv[]) 
{
    char opt;
    while ((opt = getopt(argc, argv, ":Setho:")) != -1)
    {
        switch (opt)
        {
            case 'h':
                printf("-S      : Compile SysY to RISC-V\n");
                printf("-S -e   : Compile SysY to Eeyore\n");
                printf("-S -t   : Compile Eeyore to Tigger\n");
                printf("-o      : Output file");
                break;
            case 'S':        
                compileEeyore = compileTigger = compileRISCV = true;
            case 'e':
                compileTigger = compileRISCV = false;
                break;
            case 't':
                compileRISCV = false;
                break;
            case 'o':
                out_file = optarg;
                break;
            case '?':
                printf("Unknown option: %c\n", optopt);
                break;
            default:
                break;
        }
    }
    in_file = argv[optind];
    if (compileEeyore) 
        compileToEeyore();
}