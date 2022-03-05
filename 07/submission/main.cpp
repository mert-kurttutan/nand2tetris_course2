#include <string>

using std::string;



string convertToString(char* a)
{
    string s(a);
 
    // we cannot use this technique again
    // to store something in s
    // because we use constructors
    // which are only called
    // when the string is declared.
 
    // Remove commented portion
    // to see for yourself
 
    /*
    char demo[] = "gfg";
    s(demo); // compilation error
    */
 
    return s;
}


int main(int argc, char **argv){

    string command = "./my_VMTranslator " + string(argv[1]);

    system(command.c_str());

    return 0;
}
