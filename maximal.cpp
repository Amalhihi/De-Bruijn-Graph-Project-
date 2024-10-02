#include <iostream>
#include <vector>
#include <set>
#include <random>

using namespace std;

// generate a random number between 0 and 1
double generateRandomNumber() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    double randomNum = dis(gen);
    return randomNum;
}

// Random-priority parallel algorithm for maximal independent set
set<int> find_Maximal_Independent_Set(const vector<vector<int>>& graph) {
    int numNodes = graph.size();
    set<int> independentSet;
    set<int> remainingNodes;

    // Initialize remainingNodes set with all nodes
    for (int i = 0; i < numNodes; i++) {
        remainingNodes.insert(i);
    }

    // Main algorithm loop
    while (!remainingNodes.empty()) {
        int v = *remainingNodes.begin(); // Select a node v

        double rv = generateRandomNumber(); // Generate random number for v

        bool smallestInComponent = true;
        for (int neighbor : graph[v]) {
            double rn = 0.5; // Generate random number for neighbor

            if (rn < rv) {
                smallestInComponent = false;
                break;
            }
        }

        if (smallestInComponent) {
            independentSet.insert(v);
            remainingNodes.erase(v);

            // Inform neighbors about inclusion in the independent set
            for (int neighbor : graph[v]) {
                remainingNodes.erase(neighbor);
            }
        }
        else {
            remainingNodes.erase(v);
        }
    }

    return independentSet;
}
