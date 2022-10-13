
#ifndef PASTECLI_HTTPCLIENT_H
#define PASTECLI_HTTPCLIENT_H

#include "curl/curl.h"
#include <format>
#include <string>
#include <iostream>

size_t WriteMemoryCallback(void *src, size_t size, size_t numElem, void *userData);

struct MemoryChunk{
    char* data;
    std::size_t size;
};

class HTTPClient {
public:
    HTTPClient();
    ~HTTPClient();

    std::string Post(const std::string& header);

public:
    CURL* handle{nullptr};
};


#endif //PASTECLI_HTTPCLIENT_H
