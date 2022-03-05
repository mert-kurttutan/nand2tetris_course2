#ifndef PARSERR_HPP
#define PARSER_HPP
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "../utils/utils.hpp"

using std::vector;
using std::string;
using std::ifstream;
using std::iostream;
using std::string;



class Parser{
    private:
        string file_name;
        ifstream input_file;
        string current_line;
        vector<string> command_list;
        int current_command_idx;
        static vector<string> ar_ops, push_ops, pop_ops;
    public:
        Parser(string name_param);
        bool hasMoreCommands();
        void close();
        bool advance();
        string commandType();
        string arg1();
        int arg2();


};


#endif 