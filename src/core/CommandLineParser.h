
#ifndef PASTECLI_COMMANDLINEPARSER_H
#define PASTECLI_COMMANDLINEPARSER_H

#include "boost/program_options.hpp"
#include <iostream>
#include <vector>
#include <string>

//set up all the parsing options
class CommandLineParser {
public:
    CommandLineParser(int argc, char* argv[]);
    ~CommandLineParser() = default;

    boost::program_options::variables_map& getVarMap() {return variablesMap;}
    boost::program_options::options_description& getOptionDescription() {return description;}


public:
    //container for arguments
    boost::program_options::variables_map variablesMap{};
    boost::program_options::options_description description{"Allowed options"};
};


#endif //PASTECLI_COMMANDLINEPARSER_H
