// Van Toan Vo: 5550006156
#include "options.h"
#include "BigInt.h"
#include <iostream>
#include <cstring>
#include <string>
#include <stack>
#include <vector>
#include <sstream>

void help(){
std::cout<<"Usage: ./calc [-h] [-v] \n"
        <<"to run the program interactively. To run using standard input:\n"
        <<"echo 'equation' | ./calc \n"
        <<"where 'equation' is a postfix notation equation, i.e. '2 2 +'\n"
        <<"or:\n"
        <<"  ./calc < input_file.txt\n"
        <<"where 'input_file.txt' contains postfix notation equations, one per line\n\n"
        <<"Options:\n"
        <<" -h   Show this text\n"
        <<" -v   Set a verbose output flag.  Default = false.\n\n"
        <<"Running with no input from standard in enters 'interactive mode'.\n"
        <<"Equations can be entered one per line.\n"
        <<"The program runs until 'quit' is the first word on a line or EOF is reached.\n";
}

void mesa::option::use_input(int argc, char** argv){
    std::string line, new_str;
    bool quit = false;
    for(unsigned i = 1; i<argc; ++i){
      if(std::strncmp(argv[i],"-h", 2)==0){
          help();
          exit(0);
      } 
      if(std::strncmp(argv[i],"-v", 2)==0){
          mesa::option::is_verbose = true;
      }
    }
    while(getline(std::cin, line)){
      if(line == "quit"){
        quit = true; 
        break;
      }
      if(!line.empty()&&line[0]!='#'){
        //This loop creates a new string with spaces
        //to tolerate the case the user does not separate the operands and operators.
        for(unsigned i = 0; i<line.length(); ++i){
            new_str += line[i];
            if(isOperator(line[i])||isOperator(line[i+1])){
                new_str += ' ';
            }
        }
        if(mesa::option::is_verbose == true){std::cout<<new_str<<" = ";}
        std::vector<std::string> input = converted(new_str);
        //Chain of responsibility
        std::vector<Handler*> chain = {new Add,new Multiply,new Power,new OperandPusher};
        std::stack<BigInt> container;
        for(const auto& str: input){
            for(const auto& it: chain){
                auto it_is_calculated = it->handle(container, str);
                if(it_is_calculated){
                   break;
                }
            }
        }
        //print the result
        if(container.size()==1){
            std::cout<<container.top()<<'\n';  
        }else if(container.size()>1){
            unsigned i = 0;
            std::cout<<"Error: could not produce a result.\n  Too few operators in problem.\n  Operands still on problem stack:\n";   
            while(!container.empty()){
              std::cout<<"  "<<(i+1)<<": "<<container.top()<<'\n';
              container.pop();
              ++i;
            }
        }else{
              std::cout<<"Invalid input!\n";
        }
        new_str.clear();
    } 
    line.clear();
  }
    if(mesa::option::is_verbose && quit == false){std::cout<<"\ndone.\n";}
}

/* Extract the input string into a vector of separate tokens,
 * eliminate leading and trailing spaces to put them into
 * BigInt numbers, ready to work with the Chain of responsibility.
 */
std::vector<std::string> converted(const std::string& new_string){ 
      std::vector<std::string> temp_vector;
      std::string temp;
      std::stringstream ss(new_string);
      while(std::getline(ss,temp,' ')){
          if(!temp.empty()){
            temp_vector.push_back(temp);
          }
      }
  return temp_vector;
}

bool isOperator(const char& char_){
  if(char_=='+'||char_=='*'||char_=='^'){
      return true;
  }
    return false;
}
