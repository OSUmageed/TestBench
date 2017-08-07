#include <unordered_map>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <omp.h>
#include <sched.h>

#ifdef _WIN32
  #define ENVP(x) _putenv(x)
#elif __linux__
  #define ENVP(x) putenv(x)
#else
  #define ENVP(x) _putenv(x)
#endif

// g++ -o ../bin/ompchk(.exe) ompcheck.cpp -lm -fopenmp -std=c++11

using namespace std;

int main(int argc, char *argv[])
{
  unordered_map<unsigned, string> map{
    {200505,"2.5"},{200805,"3.0"},{201107,"3.1"},{201307,"4.0"},{201511,"4.5"}};
  printf("We have OpenMP %s.\n", map.at(_OPENMP).c_str());
  int threadLimit = omp_get_thread_limit();
  printf("Number of possible threads on this processor: %d.\n", threadLimit);
  int procLimit = omp_get_num_procs(); 
  char ompenv[]="OMP_PLACES=sockets(1)";
  putenv(ompenv);

  printf("Number of available processors: %i.\n", procLimit);

  int nt = atoi(argv[1]); 

  cout << "Threads requested: " << nt << endl;

  #pragma omp parallel for num_threads(nt)
  for (int n=0; n<nt; n++)
  {
    double tm = omp_get_wtime();
    int tid = omp_get_thread_num();
    int cid = sched_getcpu();
    printf("Thread: %i -- on CPU: %i --- Time %.9f.\n", tid, cid, tm);
    sleep(5);
    fflush(stdout); 
  }

  return 0;
}

