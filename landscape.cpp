#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

class Landscape {
private:
  int dimention;
  int abs_rate;
  int drops;
  std::string elevation_file;

  std::vector<std::vector<int>> land_matrix;
  std::unordered_map<> adjList;
  std::vector<std::vector<int>> land_drops;
  std::vector<std::vector<int>> update_matrix;
  std::vector<std::vector<int>> land_absorb;

public:
  landscape() {}
  landscaoe(int d, int abs, int d, int f)
      : dimention(d), abs_rate(abs), drops(d), elevation_file(f) {
    getMatrix();
    getAdjList
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
}
