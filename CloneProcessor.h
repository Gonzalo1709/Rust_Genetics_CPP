#ifndef RUSTGENETICS2_CLONEPROCESSOR_H
#define RUSTGENETICS2_CLONEPROCESSOR_H

#include "definitions.h"
#include "CloneManager.h"
#include <string>
#include <deque>
#include <thread>
#include <mutex>

class CloneProcessor {
public:
    std::deque<std::thread> threads;
    Definitions definitions;
    CloneManager cloneManager;
    // Pass to private when done testing

    CloneProcessor(){
        cloneManager = CloneManager();
        definitions = Definitions();
    };
    std::string checkResult(std::deque<std::string> parents);
    void setUpThreads();
    void processClones();
};


#endif //RUSTGENETICS2_CLONEPROCESSOR_H
