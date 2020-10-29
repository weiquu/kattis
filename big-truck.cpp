#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

pair<int, bool> nodeSearch(int nodeFrom, int nodeTo, map<int, pair<int, vector<vector<int> > > > &paths, vector<vector<int> > &roads, vector<pair<int, int> > &nextNodeSearch, set<pair<int, int> > &roadChecker) {
    int newDist = paths[nodeFrom].first + roads[nodeFrom][nodeTo];
    int longestPath = 0;
    bool check = false;
    if (newDist < paths[nodeTo].first) {
        paths[nodeTo].first = newDist;
        paths[nodeTo].second = paths[nodeFrom].second;
        for (int i=0; i<paths[nodeTo].second.size(); i++) {
            paths[nodeTo].second[i].push_back(nodeTo);
            int length = paths[nodeTo].second[i].size();
            longestPath = max(longestPath, length);
        }
        check = true;
    }
    else if (newDist == paths[nodeTo].first) {
        int j = paths[nodeTo].second.size();
        for (int i=0; i<paths[nodeFrom].second.size(); i++) {
            paths[nodeTo].second.push_back(paths[nodeFrom].second[i]);
        }
        for (j=j; j<paths[nodeTo].second.size(); j++) {
            paths[nodeTo].second[j].push_back(nodeTo);
            int length = paths[nodeTo].second[j].size();
            longestPath = max(longestPath, length);
        }
        check = true;
    }

    if (check) {
        for (int i=0; i<roads[0].size(); i++) {
            if (roads[nodeTo][i] != -1 && i!=nodeFrom) {
                //added later on
                int roadCheck = roadChecker.size();
                roadChecker.emplace(make_pair(nodeTo, i));
                if (roadCheck < roadChecker.size()) {
                    nextNodeSearch.push_back(make_pair(nodeTo, i));
                }
            }
        }
    }

    return make_pair(longestPath, check);
}

bool nodeSearchSecond(int nodeFrom, int nodeTo, map<int, pair<int, vector<vector<int> > > > &paths, vector<vector<int> > &roads, vector<pair<int, int> > &nextNodeSearch) {
    int newDist = paths[nodeFrom].first + roads[nodeFrom][nodeTo];
    bool anythingChanged = false;
    if (newDist < paths[nodeTo].first) {
        anythingChanged = true;
        paths[nodeTo].first = newDist;
        paths[nodeTo].second = paths[nodeFrom].second;
        for (int i=0; i<paths[nodeTo].second.size(); i++) {
            paths[nodeTo].second[i].push_back(nodeTo);
        }
    }
    else if (newDist == paths[nodeTo].first) {
        anythingChanged = true;
        int j = paths[nodeTo].second.size();
        for (int i=0; i<paths[nodeFrom].second.size(); i++) {
            paths[nodeTo].second.push_back(paths[nodeFrom].second[i]);
        }
        for (j=j; j<paths[nodeTo].second.size(); j++) {
            paths[nodeTo].second[j].push_back(nodeTo);
        }
    }

    return anythingChanged;
}

int main() {
    int numLocations, numRoads;
    cin >> numLocations;

    map<int, pair<int, vector<vector<int> > > > paths;
    vector<int> items(numLocations);
    for (int i=0; i<numLocations; i++) {
        paths[i].first = 100000;
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

    paths[0].first = 0;
    paths[0].second.push_back({ 0 });
    vector<pair<int, int> > nextNodeSearch;
    set<pair<int, int> > roadChecker;
    for (int i=1; i<numLocations; i++) {
        if (roads[0][i] != -1) {
            nextNodeSearch.push_back(make_pair(0, i));
            roadChecker.emplace(make_pair(0, i));
        }
    }

    int i = 0;
    int longestPath = 0;
    pair<int, bool> vals;
    while (i<nextNodeSearch.size()) {
        vals = nodeSearch(nextNodeSearch[i].first, nextNodeSearch[i].second, paths, roads, nextNodeSearch, roadChecker);
        if (!vals.second) {
            nextNodeSearch.erase(nextNodeSearch.begin()+i);
        }
        else {
            longestPath = max(longestPath, vals.first);
            i++;
        }
    }

    if (paths[numLocations-1].first == 100000) {
        cout << "impossible\n";
    }
    else {
        //propogate changes
        for (int j=1; j<longestPath; j++) {
            i = 0;
            bool changes = false;
            while (i<nextNodeSearch.size()) {
                bool changesTemp = nodeSearchSecond(nextNodeSearch[i].first, nextNodeSearch[i].second, paths, roads, nextNodeSearch);
                if (changesTemp) {
                    changes = true;
                }
                i++;
            }
            if (!changes) {
                break;
            }
        }

        cout << paths[numLocations-1].first << " ";
        int itemsFinal = 0;
        for (int j=0; j<paths[numLocations-1].second.size(); j++) {
            int count = 0;
            for (int k=0; k<paths[numLocations-1].second[j].size(); k++) {
                count += items[paths[numLocations-1].second[j][k]];
            }
            itemsFinal = max(itemsFinal, count);
        }
        cout << itemsFinal << "\n";
    }
}