#include "codewriter.hpp"


vector<string> CodeWriter::bin_ops = {"add", "sub", "and", "or"};
vector<string> CodeWriter::una_ops = {"not", "neg"};
vector<string> CodeWriter::comp_ops = {"eq", "gt", "lt"};


std::map<string, string> bins_map = {
                                    { "add", "+" },
                                    { "sub", "-" },
                                    { "and", "&" },
                                    { "or",  "|"},
                                };
std::map<string, string> unas_map = {
                                    { "not", "!" },
                                    { "neg", "-" },
                                };

std::map<string, string> comps_map = {
                                    { "eq", "JEQ" },
                                    { "gt", "JGT" },
                                    { "lt", "JLT" },
                                };

std::map<string, string> segment_dict = {
                                            {"local", "LCL"},
                                            {"argument", "ARG"},
                                            {"this", "THIS"},
                                            {"that", "THAT"},
                                            {"pointer", "3"},
                                            {"temp", "5"},
                                        };

CodeWriter::CodeWriter(string name_param){
    
    // Name of the file to be written
    this->file_name = name_param;

    // fstream object of this file
    output_file = ofstream(file_name);

    // Return error if it cannot be opened
    if (!output_file.is_open()) {
        std::cerr << "Could not open the file - '"
             << file_name << "'" << std::endl;
        exit(EXIT_FAILURE);
    }

    label_count = 0;
    current_line = "";
    command_list = {};
    current_command_idx = -1;
}


void CodeWriter::close(){
    output_file.close();
}

string CodeWriter::unaryOp(string operation){
    
    // Use stringstream to add with the convenient form below
    stringstream machine_command;
    machine_command << "@SP" << "\n" 
                    << "M=M-1" << "\n"
                    << "A=M" << "\n"
                    << "M=" << operation << "M" << "\n"
                    << "@SP" <<"\n"
                    << "M=M+1" << "\n";

    // return string content of stringstream object
    return machine_command.str();
}



string CodeWriter::binaryOp(string operation){

    // Use stringstream to add with the convenient form below
    stringstream machine_command;

    machine_command << "@SP" << "\n"
                    << "M=M-1" << "\n"
                    << "A=M" << "\n"
                    << "D=M" << "\n"
                    << "@SP" << "\n"
                    << "M=M-1" << "\n"
                    << "A=M" << "\n"
                    << "M=M" << operation << "D" << "\n"
                    << "@SP" << "\n"
                    << "M=M+1" <<"\n";

    // string content
    return machine_command.str();
}


string CodeWriter::compare(string operation){
    label_count++;

    // Use stringstream to add with the convenient form below
    stringstream machine_command;

    // to give unique label
    string label_jump = "label_jump" + std::to_string(label_count);

    machine_command << "@SP" << "\n"         // SP--; D=*SP
                    << "M=M-1" << "\n"    
                    << "A=M" << "\n"     
                    << "D=M" << "\n"        
                    << "@SP" << "\n"         // SP--; D=D-*SP
                    << "M=M-1" << "\n"
                    << "A=M" << "\n"
                    << "D=M-D" << "\n"
                    << "M=-1" << "\n"         // *SP = -1
                    << "@" << label_jump << "\n"          // jump to label_jump
                    << "D;" << operation << "\n"
                    << "@SP" << "\n"            // *SP-- ie. *SP=-1 -> *SP=0
                    << "A=M" << "\n"
                    << "M=M+1" << "\n"
                    << "(" << label_jump << ") \n"        //label jump branch
                    << "@SP" << "\n"
                    << "M=M+1" << "\n";
    
    // string content
    return machine_command.str();
}



void CodeWriter::writeArithmetic(string param_line){

    string assembly_code;
    string op_symbol;

    // Translate the command to assembly
    if (std::find(bin_ops.begin(), bin_ops.end(), param_line) != bin_ops.end()){
        op_symbol = bins_map.at(param_line);
        assembly_code = binaryOp(op_symbol);
    }

    else if (std::find(una_ops.begin(), una_ops.end(), param_line) != una_ops.end()){
        op_symbol = unas_map.at(param_line);
        assembly_code = unaryOp(op_symbol);
    }

    else if (std::find(comp_ops.begin(), comp_ops.end(), param_line) != comp_ops.end()){
        op_symbol = comps_map.at(param_line);
        assembly_code = compare(op_symbol);
    }

    // Write assembly code to output file
    output_file << assembly_code;

}



/// ---------- Push and POP ------------///

string CodeWriter::loadIndex(int index){

    // stringstream object to add string in the below convenient form
    stringstream machine_command;
    machine_command << "@" << std::to_string(index) << "\n"
                    << "D=A" << "\n";

    return machine_command.str();
}


string CodeWriter::stack_push(){

    // stringstream object to add string in the below convenient form
    stringstream machine_command;
    machine_command << "@SP" << "\n" 
                    << "A=M" << "\n"
                    << "M=D" << "\n"
                    << "@SP" <<"\n"
                    << "M=M+1" << "\n";

    return machine_command.str();
}


string CodeWriter::stack_pop(string command, string segment, int index){

    // stringstream object to add string in the below convenient form
    stringstream machine_command;

    if (segment=="static"){
        string name_main = to_name(file_name);

        machine_command << "@SP" << "\n"
                        << "M=M-1" << "\n"
                        << "A=M" << "\n"
                        << "D=M" << "\n"
                        << "@" << name_main << "." << index << "\n"
                        << "M=D" << "\n";
    }

    else{
        machine_command << loadIndex(index)
                        << "@" << segment_dict.at(segment) << "\n";
        if (segment=="this" || segment=="that" || segment=="local" || segment=="argument"){
            machine_command << "A=M" << "\n";
        }

        machine_command << "D=A+D" << "\n"
                        << "@R13" << "\n"
                        << "M=D" << "\n"
                        << "@SP" << "\n"
                        << "M=M-1" << "\n"
                        << "A=M" << "\n"
                        << "D=M" << "\n"
                        << "@R13" << "\n"
                        << "A=M" << "\n"
                        << "M=D" << "\n";
    }

    return machine_command.str();
}


void CodeWriter::writePushPop(string command, string segment, int index){

    stringstream machine_command;

    if (command == "C_PUSH"){

        if (segment=="this" || segment=="that" || segment=="local" || segment=="argument"){
            
            machine_command << loadIndex(index)
                            << "@" << segment_dict.at(segment) << "\n"
                            << "A=M+D" << "\n"
                            << "D=M" << "\n"
                            << stack_push();
        }

        else if (segment=="temp" || segment=="pointer"){
            machine_command << loadIndex(index)
                            << "@" << segment_dict.at(segment) << "\n"
                            << "A=A+D" << "\n"
                            << "D=M" << "\n"
                            << stack_push();
        }

        else if (segment=="constant"){
            machine_command << loadIndex(index)
                            << stack_push();        
        }

        else if (segment=="static"){

            string name_main = to_name(file_name);
            machine_command << "@" << name_main << "." << std::to_string(index) << "\n"
                            << "D=M" << "\n"
                            << stack_push();
        }
    }

    else{
        machine_command << stack_pop(command, segment, index);
    }

    // Write assembly code to output file
    output_file << machine_command.str();

}



