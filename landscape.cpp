#include "landscape.h"
using namespace std;

Landscape::Landscape(int dim, int d, double abs, string f)
    : dimention(dim), drops(d), abs_rate(abs), elevation_file(f),
      wet_points(dim * dim), rainFall(dim),
      land_drops(dim, vector<double>(dim, 0)),
      update_matrix(dim, vector<double>(dim, 0)),
      land_absorb(dim, vector<double>(dim, 0)) {
  getMatrix();
  getAdjList();
}

Landscape::~Landscape() {}

void Landscape::getMatrix() {
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
      rainFall[i].push_back(stod(drop));
    }
    i++;
  }

  // read from the file and put into vector<vector> matrix
}

void Landscape::getAdjList() {
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
        if (x < 0 || x >= n || y < 0 || y >= n) {
          continue;
        }
        if (minRain < rainFall[x][y]) {
          continue;
        }
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

void Landscape::getAbsorb() {
  // print std, final result
  for (size_t i = 0; i < dimention; i++) {
    for (size_t j = 0; j < dimention; j++) {
      cout << land_absorb[i][j] << " ";
    }
    cout << endl;
  }
}

void Landscape::getUpdates() {
  // for each iteration, generate the update matrix for each point
  for (size_t i = 0; i < dimention; i++) {
    for (size_t j = 0; j < dimention; j++) {
      // if raining, get rain
      if (isRaining()) {
        land_drops[i][j] += 1;
        drops--;
      }
      // absorb by land -> update abs matrix
      if (land_drops[i][j] > abs_rate) {
        land_drops[i][j] -= abs_rate;
        land_absorb[i][j] += abs_rate;
      } else if (land_drops[i][j] > 0) {
        land_absorb[i][j] += land_drops[i][j];
        land_drops[i][j] = 0;
        wet_points--;
        if (wet_points == 0) {
          return;
        }
      } else {
        continue;
      }

      // if remaining > 1 && has low neighbor, tickle to the min neighbor
      // update the update_matrix
      if (land_drops[i][j] >= 1) {
        pair<int, int> curr = make_pair(i, j);
        if (neighbors.find(curr) != neighbors.end()) {
          double trickle_drop = 1 / neighbors[curr].size();
          const vector<int> &curr_neighbor = neighbors[curr];
          for (size_t n = 0; n < curr_neighbor.size(); n++) {
            update_matrix[curr_neighbor[0]][curr_neighbor[1]] += trickle_drop;
          }
          land_drops[i][j] -= 1;
        } // if has neighbor
      }
      // if could trickle
    } // j
  }   // i
}

void Landscape::updateDrops() {
  // update each point for land_drops from update_matrix;
  for (size_t i = 0; i < dimention; i++) {
    for (size_t j = 0; j < dimention; j++) {
      /*
      if (land_drops[i][j] >= 1) {
        pair<int, int> curr = make_pair(i, j);
        if (neighbors.find(curr) != neighbors.end()) {
          double trickle_drop = 1 / neighbors[curr].size();
          const vector<int> &curr_neighbor = neighbors[curr];
          for (size_t n = 0; n < curr_neighbor.size(); n++) {
            update_matrix[curr_neighbor[0]][curr_neighbor[1]] += trickle_drop;
            land_drops[curr_neighbor[0]][curr_neighbor[1]] += trickle_drop;
          }
          land_drops[i][j] -= 1;

        } // if has neighbor
      }

      */
      land_drops[i][j] += update_matrix[i][j];
      update_matrix[i][j] = 0;
    }
  }
}

bool Landscape::isRaining() {
  // check whether has raining
  return drops != 0;
}

bool Landscape::isDry() {
  // check whether all the drops are absorbed
  cout << "wet_points " << wet_points << endl;
  // return true;
  return wet_points == 0;
}

void Landscape::printRainfall() {
  for (size_t i = 0; i < dimention; i++) {
    for (size_t j = 0; j < dimention; j++) {
      cout << rainFall[i][j] << " ";
    }
    cout << endl;
  }
}

void Landscape::printLandDrops() {
  for (size_t i = 0; i < dimention; i++) {
    for (size_t j = 0; j < dimention; j++) {
      cout << land_drops[i][j] << " ";
    }
    cout << endl;
  }
}

void Landscape::printUpdateMatrix() {
  for (size_t i = 0; i < dimention; i++) {
    for (size_t j = 0; j < dimention; j++) {
      cout << update_matrix[i][j] << " ";
    }
    cout << endl;
  }
}
