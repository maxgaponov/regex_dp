#include <solver.h>
#include <iostream>

void run(std::istream& in, std::ostream& out) {
    std::string rpn_regex;
    char x;
    int k;
    in >> rpn_regex >> x >> k;
    out << solve(rpn_regex, x, k) << std::endl;
}

int main() {
    run(std::cin, std::cout);
}
