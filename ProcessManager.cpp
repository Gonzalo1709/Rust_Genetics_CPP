#include "ProcessManager.h"
#include <iostream>
#include <filesystem>

ProcessManager::ProcessManager() {
    if (!std::filesystem::exists("saves")) {
        std::filesystem::create_directory("saves");
    }

    for(const auto& entry: std::filesystem::directory_iterator("saves")) {
        std::string filename = entry.path().filename().string();
        filename = filename.substr(0, filename.length()-4);
        CloneProcessor cloneProcessor(filename);
        cloneProcessors.push_back(cloneProcessor);
        IndexOfCloneProcessor[cloneProcessors.size() - 1] = filename;
    }
    mainLoop();
}

void ProcessManager::bucketSelection() {
    std::cout << "Select a clone bucket to load or create a new one." << std::endl;

    for(size_t i = 0; i < cloneProcessors.size(); i++) {
        std::cout << i+1 << ": " << IndexOfCloneProcessor[i] << std::endl;
    }
    std::cout << cloneProcessors.size()+1 << ": Create new clone bucket" << std::endl;
    std::cout << "Input: ";
    size_t input;
    std::cin >> input;
    while(input < 1 || input > cloneProcessors.size()+1) {
        std::cout << "Invalid input. Input again: ";
        std::cin >> input;
    }
    if (input == cloneProcessors.size()+1) {
        std::cout << "Input the name of the new clone bucket: ";
        std::string name;
        std::cin >> name;
        CloneProcessor cloneProcessor(name);
        cloneProcessors.push_back(cloneProcessor);
        IndexOfCloneProcessor[cloneProcessors.size() - 1] = name;
    }
    else {
        cloneProcessors[input-1].cloneManager.loadAllFromFile();
    }
    currentCloneProcessorIndex = input-1;
    std::cout << "Current clone bucket: " << IndexOfCloneProcessor[currentCloneProcessorIndex] << std::endl;
}

void ProcessManager::mainLoop() {
    bucketSelection();
    bool running = true;
    while(running) {
        std::cout << "----- Menu -----" << std::endl;
        std::cout << "Bucket: " << IndexOfCloneProcessor[currentCloneProcessorIndex] << std::endl;
        std::cout << "1: Add clones" << std::endl;
        std::cout << "2: View stored clones" << std::endl;
        std::cout << "3: Process clones" << std::endl;
        std::cout << "4: Change bucket" << std::endl;
        std::cout << "5: Delete bucket" << std::endl;
        std::cout << "6: Exit" << std::endl;
        std::cout << "Input: ";
        int input;
        std::cin >> input;
        while(input < 1 || input > 6) {
            std::cout << "Invalid input. Input again: ";
            std::cin >> input;
        }
        switch(input) {
            case 1:
                cloneProcessors[currentCloneProcessorIndex].cloneManager.requestClones();
                break;
            case 2:
                cloneProcessors[currentCloneProcessorIndex].cloneManager.printClones();
                break;
            case 3:
                cloneProcessors[currentCloneProcessorIndex].processCurrentClones();
                break;
            case 4:
                bucketSelection();
                break;
            case 5:
                std::cout << "Are you sure you want to delete this bucket? The bucket will be unrecoverable!" << std::endl;
                std::cout << "1: Yes" << std::endl;
                std::cout << "2: No" << std::endl;
                std::cout << "Input: ";
                int input_deletion_confirm;
                std::cin >> input_deletion_confirm;
                while(input_deletion_confirm < 1 || input_deletion_confirm > 2) {
                    std::cout << "Invalid input_deletion_confirm. Input again: ";
                    std::cin >> input_deletion_confirm;
                }
                if (input_deletion_confirm == 1) {
                    std::filesystem::remove("saves/" + IndexOfCloneProcessor[currentCloneProcessorIndex] + cloneProcessors[currentCloneProcessorIndex].cloneManager.definitions.extension);
                    cloneProcessors.erase(cloneProcessors.begin() + currentCloneProcessorIndex);
                    IndexOfCloneProcessor.erase(currentCloneProcessorIndex);
                    bucketSelection();
                }
                break;
            case 6:
                running = false;
                cloneProcessors[currentCloneProcessorIndex].cloneManager.unloadAndSaveToFile();
                break;
            default:
                break;
        }
    }
}


