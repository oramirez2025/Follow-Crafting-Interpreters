#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>
#include <vector>

static bool hadError = false;

static void run(const std::string& src) {
    Scanner scanner(src);
    std::vector<Token> tokens = scanner.scanTokens();
    for (const Token& t: tokens) {
        std::cout << t << '\n';
    }
}

static void runFile(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        std::cout << "Could not load " << path << '\n';
        return;
    }
    std::stringstream buffer; 
    buffer << file.rdbuf();
    run(buffer.str());

    if (hadError) {
        std::exit(65);
    }
}

static void runPrompt() {
    std::string line; 
    while (true) {
        std::cout << "> ";
        
        if (!std::getline(std::cin, line)) {
            break;
        }
        run(line);
        hadError = false;
    }
}


static void error(int line, std::string& message) {
    report(line, "", message);
}

static void report(int line, std::string where, std::string& message) {
    std::cerr << "[Line " + std::to_string(line) + "] Error" + where + ": " + message + "\n";
    hadError = true;
}

int main(int argc, char* argv[]) {
    if (argc > 2) {
        std::cout << "Usage: clox [script]";
        std::exit(64);
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        runPrompt();
    }
}