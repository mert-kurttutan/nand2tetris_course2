#ifndef CODEWRITER_HPP
#define CODEWRITER_HPP
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "../utils/utils.hpp"
#include <sstream>
#include <map>

using std::vector;
using std::string;
using std::ofstream;
using std::iostream;
using std::string;
using std::stringstream;

class CodeWriter{
    
    private:
        string file_name;
        ofstream output_file;
        string current_line;
        vector<string> command_list;
        int current_command_idx;
        int label_count;
        static vector<string> bin_ops, una_ops, comp_ops;

    public:
        CodeWriter(string name_param);
        string unaryOp(string operation);
        string binaryOp(string operation);
        void writeArithmetic(string command);
        void writePushPop(string command, string segment, int index);
        string compare(string operation);
        string stack_push();
        string loadIndex(int index);
        string stack_pop(string command, string segment, int index);
        void close();

};


#endif 