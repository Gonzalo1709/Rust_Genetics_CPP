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
    Definitions definitions;
    CloneManager cloneManager;
    // Pass to private when done testing

    CloneProcessor(){
        cloneManager = CloneManager();
        definitions = Definitions();
    };
    std::pair<std::string, std::pair<bool, bool>> checkResult(std::deque<std::string> parents);
    // Return is <string result, <bool goalReached, bool contingency>>
    std::pair<bool, bool> checkResultWithParents(const std::deque<std::string>& parents);
    // Helper function for processCurrentClones
    void processCurrentClones();
};


#endif //RUSTGENETICS2_CLONEPROCESSOR_H
