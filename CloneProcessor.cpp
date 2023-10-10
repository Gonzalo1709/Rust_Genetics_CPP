#include "CloneProcessor.h"
#include "deque"
#include <unordered_map>
#include <iostream>

void CloneProcessor::setUpThreads() {
    // pass the stored clones to a Deque to be able to work with indices
    std::deque<Clone> clones;
    for (auto& clone: cloneManager.clones) {
        clones.push_back(clone);
    }
    std::deque<std::deque<std::string>> parentCombinations;
    for(int c1 = 0; c1 < clones.size(); c1++){
        parentCombinations.push_back({clones[c1].genes});
        for(int c2 = c1; c2 < clones.size(); c2++){ // Omitting the +1 here to allow for a two parent repetition
            parentCombinations.push_back({clones[c1].genes, clones[c2].genes});
            for(int c3 = c2+1; c3 < clones.size(); c3++){
                parentCombinations.push_back({clones[c1].genes, clones[c2].genes, clones[c3].genes});
                for(int c4 = c3+1; c4 < clones.size(); c4++){
                    parentCombinations.push_back({clones[c1].genes, clones[c2].genes, clones[c3].genes, clones[c4].genes});
                    for(int c5 = c4+1; c5 < clones.size(); c5++){
                        parentCombinations.push_back({clones[c1].genes, clones[c2].genes, clones[c3].genes, clones[c4].genes, clones[c5].genes});
                    }
                }
            }
        }
    }



    int i = 1;
    for (auto& parentCombination: parentCombinations) {
        std::cout << "Combination " << i << std::endl;
        for (auto& parent: parentCombination) {
            std::cout << parent << std::endl;
        }
        std::cout << std::endl;
        i++;
    }
}

std::string CloneProcessor::checkResult(std::deque<std::string> parents) {
    std::string result;
    for (int i = 0; i < 6; i ++){
        std::unordered_map<char, int> currentGeneWeights;
        for (auto& parent: parents) {
            currentGeneWeights[parent[i]] += definitions.geneTypes[parent[i]];
        }
        int maxWeight = 0;
        char maxGene = ' ';
        for (auto& geneWeight: currentGeneWeights) {
            if (geneWeight.second > maxWeight) {
                maxWeight = geneWeight.second;
                maxGene = geneWeight.first;
            }
        }
        result += maxGene;
    }
    return result;
}