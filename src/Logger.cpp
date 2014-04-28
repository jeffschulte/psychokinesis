#include "Logger.h"


void Logger::log(std::string text) {

    time_t now;

    time(&now);
    struct tm * timeinfo = localtime(&now);

    std::string temp = asctime(timeinfo);

    printf("[%s] DEBUG: %s\n", temp.substr(0, temp.size()-1).c_str(),
           text.c_str());
}
