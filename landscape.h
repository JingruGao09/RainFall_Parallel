#ifndef __LANDSCAPE_H__
#define __LANDSCAPE_H__

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
class Landscape {
private:
  size_t dimention;
  int drops;
  double abs_rate;
  string elevation_file;
  int wet_points; // N * N

  struct hash_pair {
    size_t operator()(const pair<int, int> &p) const {
      auto hash1 = hash<int>{}(p.first);
      auto hash2 = hash<int>{}(p.second);
      return hash1 ^ hash2;
    }
  };

  vector<vector<double>> rainFall; // matrix to record the height of each point
  unordered_map<pair<int, int>, vector<int>, hash_pair>
      neighbors; // adjecency list to record each point's min neighbors
  vector<vector<double>>
      land_drops; // matrix to record current drops value on each point
  vector<vector<double>> update_matrix; // matrix to record the value that
                                        // needed to update to each point
  vector<vector<double>>
      land_absorb; // matrix to record the value of obsorbtion for each point

public:
  Landscape();
  Landscape(int dim, int d, double abs, string f);

  void getMatrix();
  // read from file and construct lancscape matrix

  void getAdjList();
  // update min neighbors

  void getAbsorb();
  // print std, final result

  void getUpdates();
  // for each iteration, generate the update matrix for each point

  void updateDrops();
  // update each point for land_drops from update_matrix

  bool isRaining();
  // check whether has raining

  bool isDry();
  // check whether all the drops are absorbed

  void printRainfall();

  void printLandDrops();

  void printUpdateMatrix();

  ~Landscape();
};

#endif
