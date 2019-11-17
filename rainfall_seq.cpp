#include <bits/stdc++.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

void rainFallMatrix(vector<vector<int>> &rainFall, string elevation_file) {
  ifstream in(elevation_file.c_str());
  if (!in) {
    cerr << "Cannot open the File : " << elevation_file << endl;
    return;
  }
  string str;
  int i = 0;
  while (getline(in, str)) {
    stringstream ss(str);
    string drop;
    while (getline(ss, drop, ' ')) {
      rainFall[i].push_back(stoi(drop));
    }
    i++;
  }
}

bool isValidPos(int x, int y, int n) {
  if (x < 0 || x >= n || y < 0 || y >= n)
    return false;
  else
    return true;
}
void checkUpdate(int size, int x, int y, vector<vector<int>> &rainFallMatrix) {
  if (isValidPos(x, y, size))
    return;
  int cnt = 0;
  int minRain = rainFallMatrix[x][y];
  if (isValidPos(x - 1, y, size) &&
      rainFallMatrix[x][y] > rainFallMatrix[x - 1][y]) {
    if (minRain > rainFallMatrix[x - 1][y]) {
      minRain = rainFallMatrix[x - 1][y];
      cnt++;
    }
  }
  if (isValidPos(x + 1, y, size) &&
      rainFallMatrix[x][y] > rainFallMatrix[x - 1][y]) {
  }

  if (isValidPos(x, y - 1, size) &&
      rainFallMatrix[x][y] > rainFallMatrix[x - 1][y]) {
  }

  if (isValidPos(x, y + 1, size) &&
      rainFallMatrix[x][y] > rainFallMatrix[x - 1][y]) {
  }
}

struct hash_pair {
  // template <class T1, class T2>
  size_t operator()(const pair<int, int> &p) const {
    auto hash1 = hash<int>{}(p.first);
    auto hash2 = hash<int>{}(p.second);
    return hash1 ^ hash2;
  }
};
void minNeighbors(
    vector<vector<int>> &rainFall,
    unordered_map<pair<int, int>, vector<int>, hash_pair> &neighbors) {
  cout << "start" << endl;
  vector<vector<int>> dirs = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
  int n = rainFall.size();
  cout << n << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int minRain = rainFall[i][j];
      int cnt = 0;
      for (int d = 0; d < 4; d++) {
        int x = i + dirs[d][0];
        int y = j + dirs[d][1];
        if (x < 0 || x >= n || y < 0 || y >= n)
          continue;
        if (minRain < rainFall[x][y])
          continue;
        if (minRain > rainFall[x][y]) {
          minRain = rainFall[x][y];
          auto p = make_pair(i, j);
          neighbors[p].clear();
          neighbors[p].push_back(d);
          cnt = 1;
        } else if (minRain == rainFall[x][y]) {
          auto p = make_pair(i, j);
          neighbors[p].push_back(d);
          cnt++;
        }
      }
      if (cnt > 0 && minRain < rainFall[i][j]) {
        cout << "Division, i " << i << ", j " << j << ", cnt " << cnt << endl;
      } else {
        cout << " no Division" << endl;
        auto p = make_pair(i, j);
        // neighbors[p].clear();
        neighbors.erase(p);
        // no division
      }
    }
  }

  cout << "{{-1, 0}, {0, -1}, {1, 0}, {0, 1}}" << endl;

  for (auto it : neighbors) {
    cout << "i: " << it.first.first << " j: " << it.first.second
         << " my neighbors: ";
    for (auto i : it.second) {
      cout << i << " ";
    }
    cout << endl;
  }
}

void rainDropProcess(
    int &M, int &A, vector<vector<int>> &rainFall,
    unordered_map<pair<int, int>, vector<int>, hash_pair> &neighbors) {
  // calculate time
  // at each time step, add 1 drop, and calculate the absorb water
  // divide 1 drop to its neighbors
  // update its neighbors water
}

void rainFallSimulation(int &P, int &M, int &A, vector<vector<int>> &rainFall) {
  // M = 10, A = 0.25
  /*
    4 8 7 3
    5 4 3 2
    7 6 9 2
    1 2 3 8

    17.5     2.5     2.5       3
    2.5    3.75    5.75    42.5
    2.5     2.5     2.5      25
    37.25    5.25     2.5     2.5
  */
  unordered_map<pair<int, int>, vector<int>, hash_pair> neighbors;
  //  unordered_map<int, pair<int, vector<int>>>neighbors;
  //  unordered_map<pair<int, int>, vector<int>> neighbors;
  //  vector<vector<int>> neighbors(N);
  //  for (int i = 0; i < M; i++) {
  minNeighbors(rainFall, neighbors);
  rainDropProcess(M, A, rainFall, neighbors);
  //}
  cout << "end" << endl;
}

int main(int argc, char **argv) {
  if (argc < 5) {
    cerr << "Not enough commandline argument!\n" << endl;
    exit(EXIT_FAILURE);
  }

  int P = atoi(argv[1]); //# of parallel threads to use
  int M = atoi(argv[2]); //# of simulation time steps during which a rain drop
                         // will fall on each landscape point
  int A = atoi(argv[3]); // absorption rate
  int N = atoi(argv[4]); // dimension of the landscape

  cout << P << "," << M << "," << A << "," << N << endl;

  string elevation_file = argv[5];
  vector<vector<int>> rainFall(N);

  rainFallMatrix(rainFall, elevation_file);
  rainFallSimulation(P, M, A, rainFall);

  cout << "Done" << endl;
  for (auto line : rainFall) {
    for (auto n : line) {
      cout << n << " ";
    }
    cout << endl;
  }

  //./rainfall [P] 10 0.25 4 sample_4x4.in

  return 0;
}
