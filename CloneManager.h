#ifndef RUSTGENETICS2_CLONEMANAGER_H
#define RUSTGENETICS2_CLONEMANAGER_H

#include "definitions.h"
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <utility>


struct Clone{
    int generation;
    std::string genes;
    std::deque<std::string> parents;
    Clone(int generation, std::string genes, std::deque<std::string> parents) : generation(generation), genes(std::move(genes)), parents(std::move(parents)) {}
    explicit Clone(std::string genes) : generation(0), genes(std::move(genes)), parents() {}
    bool operator==(const Clone& other) const {
        return genes == other.genes;
    }
    bool operator!=(const Clone& other) const {
        return genes != other.genes;
    }
};

class CloneHash {
public:
    std::size_t operator()(const Clone& clone) const {
        return std::hash<std::string>()(clone.genes);
    }
};

class CloneManager {
public:
    Definitions definitions;
    std::unordered_set<Clone, CloneHash> clones;
    explicit CloneManager(std::string filename);
    void requestClones();
    void printClones();

    void loadAllFromFile();
    void saveToFile();
    void unloadAndSaveToFile();
};


#endif //RUSTGENETICS2_CLONEMANAGER_H
