function fibonacci(n: number): bigint {
  if (n <= 1) return BigInt(n);
  return fibonacci(n - 1) + fibonacci(n - 2);
}

function printFibonacci(count: number): void {
  for (let i = 0; i < count; i++) {
    console.log(`Fibonacci(${i}) = ${fibonacci(i)}`);
  }
}

// Print the first 100 Fibonacci numbers
printFibonacci(100);
