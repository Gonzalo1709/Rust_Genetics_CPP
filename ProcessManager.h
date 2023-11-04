#ifndef RUSTGENETICS2_PROCESSMANAGER_H
#define RUSTGENETICS2_PROCESSMANAGER_H

#include "CloneProcessor.h"
#include <vector>
#include <unordered_map>

class ProcessManager {
std::vector<CloneProcessor> cloneProcessors;
std::unordered_map<size_t, std::string> IndexOfCloneProcessor;
size_t currentCloneProcessorIndex = 0;
public:
    ProcessManager();
    void bucketSelection();
    void mainLoop();
};


#endif //RUSTGENETICS2_PROCESSMANAGER_H
