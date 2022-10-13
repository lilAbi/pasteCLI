#include "HTTPClient.h"

size_t WriteMemoryCallback(void *src, size_t size, size_t numElem, void *userData){
    //get total size of data we are going to write to the output stream
    auto actualSize = size * numElem;

    //convert user data pointer
    auto* memoryChunk = reinterpret_cast<MemoryChunk*>(userData);

    //realloc to bigger size to accommodate new data
    void* ptr = realloc(memoryChunk->data, memoryChunk->size + actualSize + 1);

    //replace old address to new address
    memoryChunk->data = static_cast<char*>(ptr);
    //start copying from end of the buffer
    std::memcpy(&(memoryChunk->data[memoryChunk->size]), src, actualSize);
    //update total data size
    memoryChunk->size += actualSize;
    //set last data member
    memoryChunk->data[memoryChunk->size] = 0;

    return actualSize;
}

HTTPClient::HTTPClient() {
    //initialize curl globally
    curl_global_init(CURL_GLOBAL_ALL);
    //create a handle
    handle = curl_easy_init();
}

HTTPClient::~HTTPClient() {
    //clean up curl after we dont need it anymore
    curl_global_cleanup();
}

std::string HTTPClient::Post(std::string const& header) {
    //object to store a pointer to an array of data and the size of that data length
    MemoryChunk memoryChunk{nullptr, 0};

    if(handle){
        //set up curl options for POST request
        curl_easy_setopt(handle, CURLOPT_URL, "https://pastebin.com/api/api_post.php");
        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&memoryChunk);
        curl_easy_setopt(handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        curl_easy_setopt(handle, CURLOPT_POSTFIELDS, header.c_str());
        curl_easy_setopt(handle, CURLOPT_POSTFIELDSIZE, header.size());

        if(auto result{curl_easy_perform(handle)}; result != CURLE_OK){
            std::cout << "POST REQUEST FAILED\n";
        }
        curl_easy_cleanup(handle);
    }

    if(memoryChunk.data){
        return std::string{memoryChunk.data};
    } else {
        return std::string{};
    }

}
