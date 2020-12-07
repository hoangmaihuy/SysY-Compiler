#include <getopt.h>
#include <iostream>
#include <fstream>
#include "globals.hpp"
#include "front/tree.hpp"
#include "sysy.tab.hpp"
#include "front/util.hpp"

extern FILE* yyin;
extern NCompUnit* parse();

string in_file, out_file, file_prefix;

bool compileEeyore, compileTigger, compileRISCV;

void compileToEeyore()
{
    Context ctx;
    yyin = fopen(in_file.c_str(), "r");
    ofstream log_out(file_prefix + "log");
    ofstream eeyore_out;
    
    if (!compileTigger)
        eeyore_out.open(out_file);
    else
        eeyore_out.open(file_prefix + "eeyore");
    
    auto root = parse();
    root->print(0, false, log_out);
    log_out.close();
    root->generate_eeyore(ctx, 0);
    ctx.print_eeyore(eeyore_out);
    eeyore_out.close();

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
    file_prefix = get_file_prefix(in_file);
    if (compileEeyore) 
        compileToEeyore();
}