#include "CloneProcessor.h"
#include "deque"
#include <unordered_map>
#include <iostream>

// Extracted from https://stackoverflow.com/questions/9330915/number-of-combinations-n-choose-r-in-c
unsigned nChoosek( unsigned n, unsigned k )
{
    if (k > n) return 0;
    if (n==k) return 1;
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1;

    int result = n;
    for( int i = 2; i <= k; ++i ) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}

std::pair<bool, bool> CloneProcessor::checkResultWithParents(const std::deque<std::string>& parents){
    // return is <goalReached, contingency>
    std::pair<std::string, std::pair<bool, bool>> currentResult = checkResult(parents);
    if (currentResult.second.first){
        if(currentResult.second.second){
            return std::make_pair(true, true);
        }
        std::cout << "Goal reached without contingency!" << std::endl;
        std::cout << "Parent(s): " << std::endl;
        for(auto& parent: parents){
            std::cout << parent << std::endl;
        }
        std::cout << std::endl;
        std::cout << "Result: " << currentResult.first << std::endl;

        return std::make_pair(true, false);
    }
    return std::make_pair(false, false);
};

void CloneProcessor::processCurrentClones() {
    std::deque<Clone> clones;
    for (auto& clone: cloneManager.clones) {
        clones.push_back(clone);
    }
    int amountOfClones = clones.size();
    std::cout << "Amount of clones: " << amountOfClones << std::endl;
    std::cout << "Amount of combinations: ";
    int amountOfCombinations = 0;

    for(int i = 1; i <= 5; i++){
        amountOfCombinations += nChoosek(amountOfClones, i);
    }
    std::cout << amountOfCombinations << std::endl;
    std::cout << "Processing..." << std::endl;

    std::deque<std::deque<std::string>> contingentResults;
    std::pair<bool, bool> currentResult;
    for(int c1 = 0; c1 < clones.size(); c1++){
        currentResult = checkResultWithParents({clones[c1].genes});
        if(currentResult.first){
            if(currentResult.second){
                contingentResults.emplace_back(std::deque<std::string>({clones[c1].genes}));
            }
            else{
                return;
            }
        }
        for(int c2 = c1+1; c2 < clones.size(); c2++){
            currentResult = checkResultWithParents({clones[c1].genes, clones[c2].genes});
            if(currentResult.first){
                if(currentResult.second){
                    contingentResults.emplace_back(std::deque<std::string>({clones[c1].genes, clones[c2].genes}));
                }
                else{
                    return;
                }
            }
            for(int c3 = c2+1; c3 < clones.size(); c3++){
                currentResult = checkResultWithParents({clones[c1].genes, clones[c2].genes, clones[c3].genes});
                if(currentResult.first){
                    if(currentResult.second){
                        contingentResults.emplace_back(std::deque<std::string>({clones[c1].genes, clones[c2].genes, clones[c3].genes}));
                    }
                    else{
                        return;
                    }
                }
                for(int c4 = c3+1; c4 < clones.size(); c4++){
                    currentResult = checkResultWithParents({clones[c1].genes, clones[c2].genes, clones[c3].genes, clones[c4].genes});
                    if(currentResult.first){
                        if(currentResult.second){
                            contingentResults.emplace_back(std::deque<std::string>({clones[c1].genes, clones[c2].genes, clones[c3].genes, clones[c4].genes}));
                        }
                        else{
                            return;
                        }
                    }
                    for(int c5 = c4+1; c5 < clones.size(); c5++){
                        currentResult = checkResultWithParents({clones[c1].genes, clones[c2].genes, clones[c3].genes, clones[c4].genes, clones[c5].genes});
                        if(currentResult.first){
                            if(currentResult.second){
                                contingentResults.emplace_back(std::deque<std::string>({clones[c1].genes, clones[c2].genes, clones[c3].genes, clones[c4].genes, clones[c5].genes}));
                            }
                            else{
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
    if(!contingentResults.empty()){
        std::cout << "No non-contingent results found." << std::endl;
        std::cout << "Displaying a contingent result: " << std::endl;
        std::cout << "Parent(s): " << std::endl;
        for(auto& parent: contingentResults[0]){
            std::cout << parent << std::endl;
        }
        std::cout << "You might have to crossbreed these parents multiple times to get desired result." << std::endl;
        std::cout << "Result: " << std::endl;
        std::cout << checkResult(contingentResults[0]).first << std::endl;
    }
    std::cout << "No result found." << std::endl;

}

std::pair<std::string, std::pair<bool, bool>> CloneProcessor::checkResult(std::deque<std::string> parents) {
    std::string resultReturn;
    std::deque<std::string> possibleResults;
    possibleResults.emplace_back("");
    bool contingencyBigScope = false;
    for (int i = 0; i < 6; i ++){
        bool contingency = false;
        std::unordered_map<char, int> currentGeneWeights;
        for (auto& parent: parents) {
            currentGeneWeights[parent[i]] += cloneManager.definitions.geneTypes[parent[i]];
        }
        int maxWeight = 0;
        std::string maxGenes;
        for (auto& geneWeight: currentGeneWeights) {
            std::string gene(1, geneWeight.first);
            if (geneWeight.second > maxWeight) {
                maxWeight = geneWeight.second;
                maxGenes = gene;
                contingency = false;
            }
            else if (geneWeight.second == maxWeight && !maxGenes.empty()) {
                if(cloneManager.definitions.genesInGoal.find(gene) != std::string::npos){
                    contingency = true;
                    maxGenes += gene;
                }
            }
        }
        if (!contingency){
            for(auto &possibleResult: possibleResults){
                possibleResult += maxGenes;
            }
        }
        else{
            contingencyBigScope = true;
            std::deque<std::string> newPossibleResults;
            for(auto maxGene: maxGenes){
                for(auto &possibleResult: possibleResults){
                    newPossibleResults.push_back(possibleResult + maxGene);
                }
            }
            possibleResults = newPossibleResults;
        }
    }

    bool goalReached = false;
    for(auto& possibleResult: possibleResults){
        std::unordered_map<char, int> currentGeneAmounts;
        bool found = true;
        for(auto& gene: possibleResult){
            currentGeneAmounts[gene]++;
        }
        for(auto& goalGene: cloneManager.definitions.goal){
            if(currentGeneAmounts[goalGene.first] != goalGene.second){
                found = false;
            }
        }
        if(!found){
            continue;
        }
        goalReached = true;
        resultReturn = possibleResult;
        break;

    }

    return std::make_pair(resultReturn, std::make_pair(goalReached, contingencyBigScope));
}