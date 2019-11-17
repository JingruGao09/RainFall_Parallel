#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>





int main( char * argv, int argc ) {
  if ( argc != 6) {
    std::cout << "Usage: .rainfall <P> <M> <A> <N> <elevation_file>\n" << std::endl;
    exit(EIXT_FAILURE);
  }

  int thread_num = argv[1];
  int drops = argv[2];
  int absor = argv[3];
  int dim = argv[4];
  std::string file = argv[5];

  //initailize landscape

  // time and start simulation


  // end simulation

  // write into output file

  return EXIT_SUCCESS;
}
