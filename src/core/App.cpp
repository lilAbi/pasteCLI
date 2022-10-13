
#include "App.h"

App::App(boost::program_options::variables_map& variablesMap, boost::program_options::options_description& desc) : vMap(std::move(variablesMap)), description(std::move(desc)){
    //file object
    std::fstream initFile;


    //does this argument value exist
    if(vMap.contains("key")){
        //get key from container
        key = vMap["key"].as<std::string>();

        //keep cache of key in file
        //open file in output mode and clear the old file
        initFile.open("../src/init.txt",std::ios::out | std::ios::trunc);
        //write the output file in it
        initFile << key << std::endl;

    } else {
        //get
        initFile.open("../src/init.txt", std::ios::in);
        initFile >> key;
    }

    //close the file
    initFile.close();

    //is the key available
    (key.empty()) ? keyAvailable = false : keyAvailable = true;
}

void App::Execute() {

    if(vMap.count("help")){
        std::cout << description << "\n";
    } else {
        if(keyAvailable){
            //send the request
            HTTPClient httpClient;

            //construct a post message
            std::string postRequest = std::move(BuildPostRequest());

            //execute the post message & print the message
            std::cout << httpClient.Post(postRequest) << std::endl;
        }
    }
}

std::string App::BuildPostRequest() {
    //lambda function that will return a string of two strings with a space between
    auto pred = [](const std::string &a, const std::string &b) -> std::string{ return a + " " + b;};

    std::string str{"api_option=paste&"};
    str += ("api_dev_key=" + key +"&");

    if(vMap.count("mode")){
        str += ("api_paste_private=" + vMap["mode"].as<std::string>() +"&");
    }

    if(vMap.count("title")){
        auto vecOfStr = vMap["title"].as<std::vector<std::string>>();
        std::string title = std::accumulate(vecOfStr.begin(), vecOfStr.end(), std::string{}, pred);
        str += ("api_paste_name=" + title +"&");
    }

    if(vMap.count("expire")){
        str += ("api_paste_expire_date=" + vMap["expire"].as<std::string>() +"&");
    }

    if(vMap.count("expire")){
        str += ("api_paste_expire_date=" + vMap["expire"].as<std::string>() +"&");
    }

    if(vMap.count("format")){
        str += ("api_paste_format=" + vMap["format"].as<std::string>() +"&");
    }

    if(vMap.count("text")){
        auto vecOfStr = vMap["text"].as<std::vector<std::string>>();
        std::string text = std::accumulate(vecOfStr.begin(), vecOfStr.end(), std::string{}, pred);
        str += ("api_paste_code=" + text);
    }

    return str;
}

