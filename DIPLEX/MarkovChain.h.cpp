#ifndef MARKOV_CHAIN_H
#define MARKOV_CHAIN_H

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

class MarkovChain {
private:
    std::unordered_map<std::string, std::unordered_map<std::string, int>> transitions;
    
public:
    void train(const std::vector<std::string>& errorPatterns) {
        for (size_t i = 0; i < errorPatterns.size() - 1; ++i) {
            transitions[errorPatterns[i]][errorPatterns[i+1]]++;
        }
    }
    
    std::string predictError(const std::string& currentState) {
        if (transitions.find(currentState) == transitions.end()) {
            return "Unknown error";
        }

        auto& nextStates = transitions[currentState];
        std::string predictedError;
        int maxCount = 0;

        // Predict the next most likely error state
        for (const auto& state : nextStates) {
            if (state.second > maxCount) {
                predictedError = state.first;
                maxCount = state.second;
            }
        }
        
        return predictedError;
    }
};

#endif // MARKOV_CHAIN_H
