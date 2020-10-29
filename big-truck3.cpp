#include <iostream>
#include <set>
#include <vector>

using namespace std;

pair<int, int> calc(vector<int> &theVec, vector<vector<int> > &roads, int numLocations, vector<int> &items) {
    int prevNode, nextNode, i, distance, itemsCollected;
    prevNode = theVec[0];
    i = 1;
    distance = 0;
    itemsCollected = items[prevNode];
    while (i<theVec.size()) {
        nextNode = theVec[i];
        itemsCollected += items[nextNode];
        distance += roads[prevNode][nextNode];
        prevNode = nextNode;
        i++;
    }

    return make_pair(distance, itemsCollected);
}

pair<bool, int> getPaths(set<int> &theSet, vector<int> &theVec, vector<vector<int> > &roads, int numLocations, vector<pair<set<int>, vector<int> > > &paths, int numPaths) {
    int currNode = theVec[theVec.size()-1];
    if (currNode == numLocations-1) {
        return make_pair(true, numPaths);
    }

    for (int i=0; i<numLocations; i++) {
        if (roads[currNode][i] != -1) {
            set<int> tempSet = theSet;
            tempSet.emplace(i);
            if (tempSet.size()>theSet.size()) {
                vector<int> tempVec = theVec;
                tempVec.push_back(i);
                paths[numPaths] = make_pair(tempSet, tempVec);
                numPaths++;
            }
        }
    }

    return make_pair(false, numPaths);
}

int main() {
    int numLocations, numRoads;
    cin >> numLocations;

    vector<int> items(numLocations);
    for (int i=0; i<numLocations; i++) {
        int item;
        cin >> item;
        items[i] = item;
    }

    cin >> numRoads;
    vector<vector<int> > roads(numLocations, vector<int>(numLocations, -1));
    for (int i=0; i<numRoads; i++) {
        int distance, x, y;
        cin >> x >> y >> distance;
        roads[x-1][y-1] = distance;
        roads[y-1][x-1] = distance;
    }

    vector<pair<set<int>, vector<int> > > paths(1000000);
    set<int> tempSet;
    tempSet.emplace(0);
    vector<int> tempVec;
    tempVec.push_back(0);
    paths[0] = make_pair(tempSet, tempVec);
    int numPaths = 1;
    int distance = 100000;
    int itemsCollected = -1;
    int i=0;
    while (i<numPaths) {
        pair<bool, int> reachedPaths;
        reachedPaths = getPaths(paths[i].first, paths[i].second, roads, numLocations, paths, numPaths);
        bool reached = reachedPaths.first;
        numPaths = reachedPaths.second;
        if (reached) {
            //calc distance and items
            pair<int, int> distItems;
            distItems = calc(paths[i].second, roads, numLocations, items);
            if (distItems.first < distance) {
                distance = distItems.first;
                itemsCollected = distItems.second;
            }
            else if (distItems.first == distance) {
                itemsCollected = max(itemsCollected, distItems.second);
            }
        }
        i++;
    }

    if (itemsCollected == -1) {
        cout << "impossible\n";
    }
    else {
        cout << distance << " " << itemsCollected << "\n";
    }
}