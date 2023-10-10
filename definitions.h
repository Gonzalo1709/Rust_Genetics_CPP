#ifndef RUSTGENETICS2_DEFINITIONS_H
#define RUSTGENETICS2_DEFINITIONS_H

#include <unordered_map>
#include <string>

struct Definitions {
    std::unordered_map<char, char> geneTypes;
    std::unordered_map<char, int> goal;
    float rWeight = 0.9;
    float gWeight = 0.5;
    std::string filename = "clones";
    std::string extension = ".txt";

    Definitions() {
        // Defining gene types
        geneTypes['X'] = 'R';
        geneTypes['W'] = 'R';
        geneTypes['Y'] = 'G';
        geneTypes['G'] = 'G';
        geneTypes['H'] = 'G';

        // Defining goal
        goal['X'] = 0;
        goal['W'] = 0;
        goal['Y'] = 4;
        goal['G'] = 2;
        goal['H'] = 0;
    }

};

#endif //RUSTGENETICS2_DEFINITIONS_H