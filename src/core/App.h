#ifndef PASTECLI_APP_H
#define PASTECLI_APP_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include "boost/program_options.hpp"
#include "HTTPClient.h"

class App {
public:
    explicit App(boost::program_options::variables_map& variablesMap, boost::program_options::options_description& desc);
    ~App() = default;

    //build a request and send it with the bodies
    void Execute();

private:
    std::string BuildPostRequest();

private:
    boost::program_options::variables_map vMap;
    boost::program_options::options_description description;
    std::string key{};
    bool keyAvailable{false};
};


#endif //PASTECLI_APP_H
