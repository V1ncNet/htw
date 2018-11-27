class Fibonacci {
  int n;
  int i = 0;

  Fibonacci(int n) {
    this.n = n;

    for (int c = 0; c <= n; c++) {
      System.out.println(f(i));
      i++;
    }
  }
  
  public static void main(String args[]) {
    System.out.println("Fibonacci Folge ist:");

    Fibonacci fib = new Fibonacci(50);
  }

  private int f(int n) {
    if (n == 0 || n == 1) {
      return n;
    } else {
      return (f(n-1)+f(n-2));
    }
  }
}
