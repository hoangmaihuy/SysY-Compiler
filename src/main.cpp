#include <getopt.h>
#include <iostream>
#include <fstream>
#include "globals.hpp"
#include "eeyore/sysy_tree.hpp"
#include "sysy.tab.hpp"
#include "util/util.hpp"
#include "tigger/context_tigger.hpp"

extern FILE* yyin;
extern NCompUnit* parse();

string in_file, out_file, file_prefix;
bool DEBUG = false;
bool compileEeyore, compileTigger, compileRISCV;
ContextEeyore ctx_eeyore;
ContextTigger ctx_tigger;
vector<string> riscv_list;

void compileToEeyore()
{
    yyin = fopen(in_file.c_str(), "r");
    ofstream eeyore_out;
    
    if (!compileTigger)
        eeyore_out.open(out_file);
    else
        eeyore_out.open(file_prefix + "eeyore");

    auto root = parse();
    if (DEBUG) 
    {
        cerr << "Done parse\n";
        root->print(0, false, cerr);
    }
    root->generate_eeyore(ctx_eeyore, 0);
    ctx_eeyore.fix_eeyore();
    ctx_eeyore.print_eeyore(eeyore_out);
    eeyore_out.close();
}

void compileToTigger()
{
    ofstream tigger_out;
    if (!compileRISCV)
        tigger_out.open(out_file);
    else
        tigger_out.open(file_prefix + "tigger");

    for (auto& eeyore_func : ctx_eeyore.eeyore_funcs)
    {
        ctx_tigger.generate_tigger_func(eeyore_func);
    }

    ctx_tigger.print_tigger(tigger_out);
    tigger_out.close();
}

void compileToRISCV()
{
    ofstream riscv_out;
    riscv_out.open(out_file);
    riscv_list.clear();
    for (const auto& func : ctx_tigger.tigger_funcs)
    {
        if (func.func_name != GLOB_NAME)
        {
            auto* func_def = new TFuncDef(func.func_name, func.args_num, func.stack_size);
            func_def->generate_riscv(riscv_list);
        }
        for (auto stmt : func.stmts)
            stmt->generate_riscv(riscv_list);
        if (func.func_name != GLOB_NAME)
        {
            auto* func_end = new TFuncEnd(func.func_name);
            func_end->generate_riscv(riscv_list);
        }
    }
    for (const auto& line : riscv_list)
        riscv_out << line << "\n";
    riscv_out.close();
}

int main(int argc, char * argv[]) 
{
    char opt;
    compileEeyore = compileTigger = compileRISCV = true;
    while ((opt = getopt(argc, argv, ":Sethdo:")) != -1)
    {
        switch (opt)
        {
            case 'h':
                printf("-S      : Compile SysY to RISC-V\n");
                printf("-S -e   : Compile SysY to Eeyore\n");
                printf("-S -t   : Compile Eeyore to Tigger\n");
                printf("-o      : Output file");
                printf("-d      : Print debug information");
                break;
            case 'S':
                break;
            case 'e':
                compileTigger = compileRISCV = false;
                break;
            case 't':
                compileRISCV = false;
                break;
            case 'o':
                out_file = optarg;
                break;
            case 'd':
                DEBUG = true;
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
    if (compileTigger)
        compileToTigger();
    if (compileRISCV)
        compileToRISCV();
}