#ifndef RUSTGENETICS2_CLONEPROCESSOR_H
#define RUSTGENETICS2_CLONEPROCESSOR_H

#include "definitions.h"
#include "CloneManager.h"
#include <string>
#include <deque>
#include <thread>
#include <mutex>
#include <utility>

class CloneProcessor {
public:
    CloneManager cloneManager;
    explicit CloneProcessor(const std::string& filename): cloneManager(filename){
    };
    std::pair<std::string, std::pair<bool, bool>> checkResult(std::deque<std::string> parents);
    // Return is <string result, <bool goalReached, bool contingency>>
    std::pair<bool, bool> checkResultWithParents(const std::deque<std::string>& parents);
    // Helper function for processCurrentClones
    void processCurrentClones();
};


#endif //RUSTGENETICS2_CLONEPROCESSOR_H
