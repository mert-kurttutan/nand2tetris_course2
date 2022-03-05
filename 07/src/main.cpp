#include <iostream>
#include <parser.hpp>
#include <codewriter.hpp>
#include <utils.hpp>
#include <iomanip>



void VMTranslator(string file_name, string output_name);

void print(std::vector <string> const &a) {
   std::cout << "The vector elements are : ";

   for(int i=0; i < int(a.size()); i++)
   std::cout << a.at(i) << "--";
   std::cout << "\n";
}


int main(int argc, char **argv){
    string file_name = argv[1];
    string output_name = file_name.substr(0,file_name.size()-2)+"asm";

    Parser my_parser = Parser(file_name);

    CodeWriter my_coder = CodeWriter(output_name);

    VMTranslator(file_name, output_name);

    return 0;
}


void VMTranslator(string file_name, string output_name){

    Parser my_parser = Parser(file_name);
    CodeWriter my_coder = CodeWriter(output_name);
    string current_command;

    while(my_parser.hasMoreCommands()){
        my_parser.advance();
        if (my_parser.commandType() == "C_ARITHMETIC"){
            my_coder.writeArithmetic(my_parser.arg1() );
        }
        else if(my_parser.commandType() == "C_PUSH" || my_parser.commandType() == "C_POP"){
            my_coder.writePushPop(my_parser.commandType(), my_parser.arg1(), my_parser.arg2());
        }
        else{
            std::cout << "oh no\n";
        }



    }
    my_parser.close();
    my_coder.close();
}