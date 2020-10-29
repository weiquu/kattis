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

bool getPaths(set<int> &theSet, vector<int> &theVec, vector<vector<int> > &roads, int numLocations, vector<pair<set<int>, vector<int> > > &paths) {
    int currNode = theVec[theVec.size()-1];
    if (currNode == numLocations-1) {
        return true;
    }

    for (int i=0; i<numLocations; i++) {
        if (roads[currNode][i] != -1) {
            set<int> tempSet = theSet;
            tempSet.emplace(i);
            if (tempSet.size()>theSet.size()) {
                vector<int> tempVec = theVec;
                tempVec.push_back(i);
                paths.push_back(make_pair(tempSet, tempVec));
            }
        }
    }

    return false;
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

    vector<pair<set<int>, vector<int> > > paths;
    set<int> tempSet;
    tempSet.emplace(0);
    vector<int> tempVec;
    tempVec.push_back(0);
    paths.push_back(make_pair(tempSet, tempVec));

    int distance = 100000;
    int itemsCollected = -1;
    int i=0;
    while (i<paths.size()) {
        bool reached = getPaths(paths[i].first, paths[i].second, roads, numLocations, paths);
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

    cout << distance << " " << itemsCollected << "\n";
}