#include <unordered_map>
#include <cstdio>
#include <stdlib.h>
#include <omp.h>

using namespace std;

int main(int argc, char *argv[])
{
  unordered_map<unsigned, string> map{
    {200505,"2.5"},{200805,"3.0"},{201107,"3.1"},{201307,"4.0"},{201511,"4.5"}};
  printf("We have OpenMP %s.\n", map.at(_OPENMP).c_str());
  int threadLimit = omp_get_thread_limit();
  printf("Number of possible threads on this processor: %d.\n", threadLimit);
  int procLimit = omp_get_num_procs();
	char ompenv[]="OMP_DISPLAY_ENV=VERBOSE";
	putenv(ompenv);
  printf("Number of available processors: %i.\n", procLimit);

  return 0;
}

