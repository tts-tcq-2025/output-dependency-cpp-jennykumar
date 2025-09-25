#include <iostream>

// Function pointer type for output behavior
typedef void (*OutputFunc)(int);

// Production function that uses injected output logic
int add(int x, int y, OutputFunc output) {
    int sum = x + y;
    output(sum);  // depends on abstraction
    return sum;
}

// Concrete output: print to console
void print_to_console(int value) {
    std::cout << value << std::endl;
}

// Test collector: store value in buffer
struct OutputCollector {
    int* values;
    int count;
};

// Global test output buffer
OutputCollector collector = { nullptr, 0 };

// Test output function
void collect_output(int value) {
    // 'collector' is global
    collector.values[collector.count++] = value;
}

// Test function
void run_test() {
    // Initialize buffer
    collector.values = new int[10];  // space for 10 values
    collector.count = 0;

    // Call add with test output function
    int result = add(-3.5, 4, collect_output);

    // Assertions
    if (result == 0.5 && collector.count == 1 && collector.values[0] == 0.5) {
        std::cout << "✓ Test passed" << std::endl;
    } else {
        std::cout << "✗ Test failed" << std::endl;
    }

    delete[] collector.values;
}

int main() {
    // Use real console output
    add(-3.5, 4, print_to_console);

    // Run the test
    run_test();

    return 0;
}
