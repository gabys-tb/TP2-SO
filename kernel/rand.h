#ifndef _RAND_H_
#define _RAND_H_

static unsigned long next = 1;

void srandom(unsigned long seed) {
  next = seed;
}

long random(void) {
  next = next * 1103515245 + 12345;
  return (unsigned int)(next / 65536) % 32768;
}

#endif // _RAND_H_
