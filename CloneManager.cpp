#include "CloneManager.h"
#include <iostream>
#include <fstream>

void CloneManager::requestClones() {
    std::cout << "How many clones do you want to add?" << std::endl;
    int amount;
    std::cout << "Amount: ";
    std::cin >> amount;

    std::cout << "Input clones as 6 letters ie. GGYYYY" << std::endl;
    std::cout << "If you want to finish clone input early. Input 'E'." << std::endl;
    for (int i = 0; i < amount; i++) {
        std::string clone;
        std::cout << "Clone " << i+1 << ": ";
        std::cin >> clone;

        for (auto& c: clone) {
            c = char(::toupper((unsigned char)c));
        }

        if (clone == "E") {
            std::cout << "Ending clone input early." << std::endl;
            break;
        }
        bool valid = true;
        if (clone.length() != 6) {
            std::cout << "Invalid length: " << clone.length() << std::endl;
            std::cout << "Clones must be 6 genes long" << std::endl;
            std::cout << "Input clone " << i << " again: ";
            valid = false;
        }
        else {
            for (auto c: clone) {
                if (definitions.geneTypes.find(c) == definitions.geneTypes.end()) {
                    std::cout << "Invalid gene type: " << c << std::endl;
                    std::cout << "Valid gene types: X, W, Y, G, H" << std::endl;
                    std::cout << "Input clone" << i << " again: ";
                    valid = false;
                    break;
                }
            }
        }
        if (!valid) {
            i--;
            continue;
        }
        clones.insert(Clone(clone));
    }

}

void CloneManager::printClones() {
    for(const auto& clone: clones) {
        std::cout << clone.genes << std::endl;
    }
}

void CloneManager::loadAllFromFile() {
    std::ifstream file;
    std::string path = "saves/"+definitions.filename+definitions.extension;
    file.open(path);
    if (!file) {
        std::cout << "Save file not found. Creating new file." << std::endl;
        std::ofstream newFile;
        newFile.open(definitions.filename);
        newFile.close();
        return;
    }
    std::string clone;
    while (std::getline(file, clone)) {
        clones.insert(Clone(clone));
    }
    file.close();
}


void CloneManager::saveToFile() {
    std::ofstream file;
    std::string path = "saves/"+definitions.filename+definitions.extension;
    file.open(path);
    for (const auto& clone: clones) {
        file << clone.genes << std::endl;
    }
    file.close();
}

CloneManager::CloneManager(std::string filename) {
    definitions.filename = std::move(filename);
    loadAllFromFile();
}

void CloneManager::unloadAndSaveToFile() {
    saveToFile();
    clones.clear();
}
