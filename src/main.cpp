// main.cpp

#include <systemc.h>
#include "tests.h"

using namespace std;

int sc_main(int argc, char * argv[])
{
  test_pe();

  return EXIT_SUCCESS;
}
