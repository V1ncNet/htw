#include <stdio.h>
#include <stdlib.h>

int fibonacci(int);

int main(int argc, char **argv)
{
  int n = atoi(argv[1]), c, i = 0;

  // scanf("%d", &n);

  printf("Fibonacci-Folge ist:\n");

  for (c = 1; c <= n; c++)
  {
    printf("%d\n", fibonacci(i));
    i++;
  }

  return 0;
}

int fibonacci(int n)
{
  if (n == 0 || n == 1) return n;
  else return (fibonacci(n-1)+fibonacci(n-2));
}
