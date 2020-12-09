
#ifndef SYSY_COMPILER_CONTEXT_TIGGER_HPP
#define SYSY_COMPILER_CONTEXT_TIGGER_HPP

class TiggerList {
public:
    string func_name;
    int args_num;
    int stack_size;
    TiggerList(string func_name, int args_num);

};

class ContextTigger {
public:
    vector<TiggerList> tigger_lists;
    void generate_tigger(const EeyoreList& eeyore_list);
};


#endif //SYSY_COMPILER_CONTEXT_TIGGER_HPP
