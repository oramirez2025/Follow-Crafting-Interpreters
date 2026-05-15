#include <iostream>
#include <string>


static void run();
static void runFile(const string& path);
static void runPrompt();


int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::cout << "Usage: clox [script]";
        std::exit(64);
    } else if (argc == 1) {
        runFile(argv[0]);
    } else {
        runPrompt();
    }
}