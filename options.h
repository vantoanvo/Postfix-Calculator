//Van Toan Vo: 5550006156
#ifndef MESA_CISC187_PROJECT2_OPTIONS_H
#define MESA_CISC187_PROJECT2_OPTIONS_H
#include <string>
#include <vector>
namespace mesa{
  struct option{
    bool is_verbose = false; 
    void use_input(int argc, char** argv); 
  };
}//end of mesa namespace
void help();
bool isOperator(const char& char_);
std::vector<std::string> converted(const std::string& new_string);
#endif
