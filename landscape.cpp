#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
class Landscape {
private:
  int dimention;
  int abs_rate;
  int drops;
  string elevation_file;

  vector<vector<int>> rainFall;
  unordered_map<pair<int, int>, vector<int>, hash_pair> neighbors;
  vector<vector<int>> land_drops;
  vector<vector<int>> update_matrix;
  vector<vector<int>> land_absorb;

public:
  landscape() {}
  landscaoe(int d, int abs, int d, int f)
      : dimention(d), abs_rate(abs), drops(d), elevation_file(f) {
    getMatrix();
    getAdjList();
  }

  void getMatrix() {
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
    // read from the file and put into vector<vector> matrix
  }

  void getAdjList() {
    // from matrix get all higher point's lowest neighbor
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

  void getAbsorb() {
    // print std, final result
  }

  void getUpdates() {
    // for each iteration, generate the update matrix for each point
  }

  void updateDrops() {
    // update each point for land_drops from update_matrix;
  }

  bool isRaining() {
    // check whether has raining
    return drops != 0;
  }

  bool isDry() {
    // check whether all the drops are absorbed
  }
};
