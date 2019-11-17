#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "landscape.h"


int main(int argc, char **argv) {
  if (argc < 6) {
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
  Landscape *landscape = new Landscape(N, A, M, elevation_file);
  int timesteps = 0;

  // start timpstamp
  while ( !landscape->isDry() ) {
    landscape->getUpdates();
    landscape->updateDrops();
    timesteps++;
  }
 
  // end timpstamp

  // print output

  cout << " " << endl;
  landscape->getAbsorb();
  
   /*
  cout << "Done" << endl;
  for (auto line : rainFall) {
    for (auto n : line) {
      cout << n << " ";
    }
    cout << endl;
  }
  */
  //./rainfall [P] 10 0.25 4 sample_4x4.in

  return EXIT_SUCCESS;
}
