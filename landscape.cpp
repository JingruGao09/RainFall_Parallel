#include "landscape.h"
using namespace std;

Landscape::Landscape(int dim, int d, double abs, string f)
    : dimension(dim), drops(d), abs_rate(abs), elevation_file(f),
      wet_points(dim * dim), count(1), rainFall(dim, vector<double>(dim, 0)),
      land_drops(dim, vector<double>(dim, 0)),
      update_matrix(dim, vector<double>(dim, 0)),
      land_absorb(dim, vector<double>(dim, 0)),
      comp_empty(dim, vector<double>(dim, 0)) {
  getMatrix();
  getAdjList();
}

void Landscape::printInitValue() {
  cout << "dim: " << dimension << ", "
       << "drops: " << drops << ", absRate: " << abs_rate << endl;
}

Landscape::~Landscape() {}

void Landscape::getMatrix() {
  ifstream in(elevation_file.c_str());
  if (!in) {
    cerr << "Cannot open the File : " << elevation_file << endl;
    return;
  }
  for (int i = 0; i < dimension; i++) {
    for (int j = 0; j < dimension; j++) {
      in >> rainFall[i][j];
    }
  }
}

int Landscape::getMinNeighbors(int& i, int& j, int& minRain) {
  int cnt = 0;
  vector<int> dirs = {-1, 0, 1, 0, -1};
  for (int d = 0; d < 4; d++) {
    int x = i + dirs[d];
    int y = j + dirs[d + 1];
    if (x < 0 || x >= dimension || y < 0 || y >= dimension) {
      continue;
    }
    if (minRain < rainFall[x][y]) {
      continue;
    }
    if (minRain > rainFall[x][y]) {
      minRain = rainFall[x][y];
      auto p = make_pair(i, j);
      neighbors[p].clear();
      neighbors[p].push_back(make_pair(x, y));
      cnt = 1;
    } else if (minRain == rainFall[x][y]) {
      auto p = make_pair(i, j);
      neighbors[p].push_back(make_pair(x, y));
      cnt++;
    }
  }
  return cnt;
}

// from matrix get all higher point's lowest neighbor
void Landscape::getAdjList() {
  for (int i = 0; i < dimension; i++) {
    for (int j = 0; j < dimension; j++) {
      int minRain = rainFall[i][j];
      int cnt = getMinNeighbors(i, j, minRain);
      if (cnt > 0 && minRain < rainFall[i][j]) {
        continue;
      } else {
        auto p = make_pair(i, j);
	neighbors.erase(p);
      }
    }
  }
}

void Landscape::getAbsorb() {
  for (int i = 0; i < dimension; i++) {
    for (int j = 0; j < dimension; j++) {
      cout << land_absorb[i][j] << " ";
    }
    cout << endl;
  }
}

int Landscape::getRainingTimes() { return count; }

void Landscape::absorbRainDrop(int& i, int& j) {
  if (land_drops[i][j] >= abs_rate) {
    land_drops[i][j] -= abs_rate;
    land_absorb[i][j] += abs_rate;
  } else if (land_drops[i][j] > 0) {
    land_absorb[i][j] += land_drops[i][j];
    land_drops[i][j] = 0;
  }
}

void Landscape::trickleNeighbors(const pair<int, int>& curr) {
  
  int size = neighbors[curr].size();
  double trickle_drop = min(1.0, land_drops[curr.first][curr.second]) / (double)size;
  for (auto k : neighbors[curr]) {
    int x = k.first;
    int y = k.second;
    update_matrix[x][y] += trickle_drop;
  }
  land_drops[curr.first][curr.second] -= min(1.0, land_drops[curr.first][curr.second]);  
}

// for each iteration, generate the update matrix for each point
void Landscape::getUpdates() {
  for (int i = 0; i < dimension; i++) {
    for (int j = 0; j < dimension; j++) {
      if (isRaining()) {
	land_drops[i][j] += 1.0;
      }
      absorbRainDrop(i, j);
      const auto curr = make_pair(i, j);
      if (neighbors.count(curr)) {
	trickleNeighbors(curr);
      }
    }
  }
  if (isRaining()) {
    drops--;
  }
}

// update each point for land_drops from update_matrix;
void Landscape::updateDrops() {
  for (int i = 0; i < dimension; i++) {
    for (int j = 0; j < dimension; j++) {
      if (update_matrix[i][j] == 0) {
	continue;
      }
      land_drops[i][j] += update_matrix[i][j];
      update_matrix[i][j] = 0;
    }
  }
}

bool Landscape::isRaining() {
  return drops != 0;
}

bool Landscape::isDry() {
  if (land_drops == comp_empty) {
    return true;
  } else {
    return false;
  }
}

void Landscape::printRainfall() {
  for (int i = 0; i < dimension; i++) {
    for (int j = 0; j < dimension; j++) {
      cout << rainFall[i][j] << " ";
    }
    cout << endl;
  }
}

void Landscape::printLandDrops() {
  for (int i = 0; i < dimension; i++) {
    for (int j = 0; j < dimension; j++) {
      cout << land_drops[i][j] << " ";
    }
    cout << endl;
  }
}

void Landscape::printUpdateMatrix() {
  for (int i = 0; i < dimension; i++) {
    for (int j = 0; j < dimension; j++) {
      cout << update_matrix[i][j] << " ";
    }
    cout << endl;
  }
}
void Landscape::printAbsorbMatrix() {
  for (int i = 0; i < dimension; i++) {
    for (int j = 0; j < dimension; j++) {
      cout << land_absorb[i][j] << " ";
    }
    cout << endl;
  }
}
