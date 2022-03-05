#include "parser.hpp"
#include <iomanip>

vector<string> Parser::ar_ops = {"add", "sub", "neg", "eq", "gt", "lt", "and", "or", "not"};
vector<string> Parser::push_ops = {"push"};
vector<string> Parser::pop_ops = {"pop"};

const string C_ARITHMETIC = "C_ARITHMETIC";
const string C_POP = "C_POP";
const string C_PUSH = "C_PUSH";
const string C_RETURN = "C_RETURN";


Parser::Parser(string name_param){
    
    // Name of the file to be parserd
    file_name = name_param;
    
    // fstream object of this file
    input_file = ifstream(file_name);

    // Return error if it cannot be opened
    if (!input_file.is_open()) {
        std::cerr << "Could not open the file - '"
             << file_name << "'" << std::endl;
        exit(EXIT_FAILURE);
    }

    current_line = "";
    command_list = {};
    current_command_idx = -1;

}

void Parser::close(){
    input_file.close();
}



bool Parser::hasMoreCommands(){

    // If all the commands in the list is not loaded to current commands
    if ( current_command_idx < int(command_list.size()-1) ){
        return true;
    }


    // To check condition for eof or new valid command
    bool Flag1 = false;
    bool Flag2 = false;
    string next_command;

    while ( (!Flag1) and (!Flag2) ){
        // Stop at the end of file
        Flag1 = input_file.eof();

        // Get next line and turn into valid form
        getline(input_file, current_line);
        next_command = to_command(current_line);

        // Stop if there is a valid command
        Flag2 = next_command.size() != 0;
    }

    // The end of file -> no more command
    if (Flag1){
        return false;
    }
    
    //add the next command if it is non-empty command
    else{
        command_list.push_back(next_command);
        return true;
    }
}

bool Parser::advance(){
    
    // If the entire program is parsed, no more parsing is allowed
    if (this->hasMoreCommands()){
        current_command_idx += 1;
        return true;
    }

    // if no more commands, close the file
    else{

        std::cout << "Entire file is parsed\n";
        return false;
    }

}


string Parser::commandType(){


    // Error if not found command TYpe
    string command_type="ERROR";
    string current_command = command_list[current_command_idx];

    // If commandType is C_ARITHMETIC
    for(auto &operation: ar_ops ){
        if(current_command.find(operation) != string::npos){
            command_type = C_ARITHMETIC;
            return command_type;
        }
    }

    // If commandType is C_PUSH
    for (auto&operation: push_ops){
        if(current_command.find(operation) != string::npos){
            command_type = C_PUSH;
            return command_type;
        }
    }


    // If commandType is C_POP
    for (auto&operation: pop_ops){
        if(current_command.find(operation) != string::npos){
            command_type = C_POP;
            return command_type;
        }
    }

    return command_type;

}


string Parser::arg1(){

    string current_command = command_list[current_command_idx];
    vector<string> words = split_by(current_command, ' ');

    // Should not be called if C_RETURN
    if (commandType() == C_RETURN){
        return "ERROR";
    }
    else if (commandType() == C_ARITHMETIC){
        return words[0];
    }

    else if(commandType() == C_POP || commandType() == C_PUSH ){
        return words[1];
    }

    return "ERROR";

}

int Parser::arg2(){

    string current_command = command_list[current_command_idx];
    vector<string> words = split_by(current_command, ' ');

    if (commandType() == C_POP || commandType() == C_PUSH){
        return stoi(words[2]);
    }
    // If not C_POP or C_PUSH, return error
    return -1;
}
