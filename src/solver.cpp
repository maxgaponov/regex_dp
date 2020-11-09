#include <dynamic.h>
#include <string>
#include <stack>
#include <stdexcept>

size_t solve(const std::string rpn_regex, char x, int k) {
    std::stack<DynamicState> states;
    for (char c : rpn_regex) {
        if (isalpha(c)) {
            states.push(DynamicState(x, k, c));
        } else if (c == '.') {

        } else if (c == '+') {

        } else if (c == '*') {

        } else {
            throw std::invalid_argument("bad symbol in regex");
        }
    }
}
