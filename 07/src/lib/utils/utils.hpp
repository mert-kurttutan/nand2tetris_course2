#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>

using std::vector;
using std::stringstream;
using std::string;
using std::iostream;

string to_command(string statement);
vector<string> split_by(string statement, char delimiter);
string to_name(string full_name);