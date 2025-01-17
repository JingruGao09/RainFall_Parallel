#include "landscape.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/time.h>
#include <vector>

double calc_time(struct timeval start, struct timeval end) {
  double start_sec = (double)start.tv_sec * 1000000.0 + (double)start.tv_usec;
  double end_sec = (double)end.tv_sec * 1000000.0 + (double)end.tv_usec;

  if (end_sec < start_sec) {
    return 0;

  } else {
    return end_sec - start_sec;
  }
}
int main(int argc, char **argv) {
  if (argc < 6) {
    cerr << "Not enough commandline argument!\n" << endl;
    exit(EXIT_FAILURE);
  }

  int P = atoi(argv[1]); //# of parallel threads to use
  int M = atoi(argv[2]); //# of simulation time steps during which a rain drop
  // will fall on each landscape point
  string A_str(argv[3]); // absorption rate
  double A = stod(A_str);
  int N = atoi(argv[4]); // dimension of the landscape

  cout <<"P "<< P << ", M " << M << ", A " << A << ", N " << N << endl;

  string elevation_file = argv[5];
  Landscape *landscape = new Landscape(N, M, A, elevation_file);
  int timesteps = 0;

  
  struct timeval start_time, end_time;
  gettimeofday(&start_time, NULL);

  while (true) {
    landscape->getUpdates();
    landscape->updateDrops();
    timesteps++;
    if (landscape->isDry()) {
      //&& timesteps > M) {
      break;
    }
  }


  gettimeofday(&end_time, NULL);
  double elapsed_us = calc_time(start_time, end_time);
  double elapsed_ms = elapsed_us / 1000000.0;
  std::cout << "Time=" << elapsed_ms << " seconds" << std::endl;

  cout << "Rainfall simulation completed in " << timesteps << " time steps"
       << endl;

  cout << "The number of raindrops absorbed at each point: " << endl;
  landscape->getAbsorb();

  delete landscape;
  return EXIT_SUCCESS;
}
