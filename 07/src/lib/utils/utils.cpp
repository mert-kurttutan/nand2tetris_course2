#include "utils.hpp"


string to_command(string statement){

    string comment_ch = "//";
    
    // Ignore the next line character and comments
    statement = statement.substr(0, statement.size()-1);
    size_t found = statement.find(comment_ch);
    string before_comment = statement.substr(0, found);

    return before_comment;
}


vector<string> split_by(string statement, char delimiter){

    stringstream ss(statement);
    string tmp;
    vector<string> words;
    
    while(getline(ss, tmp, delimiter)){
        words.push_back(tmp);
    }
    
    return words;
}



string to_name(string full_name){

    // file name without extension : my_file.txt -> my_file,
    int idx1 = full_name.rfind('/');
    std::string f_name = full_name.substr(idx1+1);
    int idx2 = f_name.rfind('.');

    return f_name.substr(0, idx2);
}