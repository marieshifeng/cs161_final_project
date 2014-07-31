#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

unsigned long GetRandomNumber(int max) {
  return (unsigned long) (( (double)(max) / RAND_MAX ) * rand() + 1);
}

void MakeRandomGraph(unsigned long n, unsigned long m, const char *outputFile) {
	FILE *out = fopen(outputFile, "w");
	if (out == NULL) {
    	fprintf(stderr, "Couldn't open output file %s!\n", outputFile);
    	exit(1);
  }
	fprintf(out, "%lu\n%lu\n", n, m);
  for (int i = 0; i < m; ++i) {
		unsigned long u = GetRandomNumber(n);
		unsigned long v = GetRandomNumber(n);
    assert(u > 0);
    assert(v > 0);
    assert(u < n + 1);
    assert(v < n + 1);
		fprintf(out, "%lu %lu", u, v);
		if (i < m - 1) fprintf(out, "\n");
  }
  fclose(out);
}

int main(int argc, char **argv){
  srand(time(NULL));
  assert(argc == 4);
  unsigned long n = strtoul(argv[1], NULL, 0);
  unsigned long m = strtoul(argv[2], NULL, 0);
  char *outputFile = argv[3];
  MakeRandomGraph(n, m, outputFile);
  return 0;
}