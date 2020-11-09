#include <dynamic.h>
#include <dynamic_manip.h>
#include <string>
#include <stack>
#include <stdexcept>
#include <functional>

size_t solve(const std::string& rpn_regex, char x, int k) {
    std::stack<DynamicState> states;
    for (char c : rpn_regex) {
        if (isalpha(c)) {
            states.push(DynamicState(x, k, c));
        } else {
            if (c == '.') {
                DynamicState rhs = states.top();
                states.pop();
                DynamicState lhs = states.top();
                states.pop();
                states.push(concat(lhs, rhs));
            } else if (c == '+') {
                DynamicState rhs = states.top();
                states.pop();
                DynamicState lhs = states.top();
                states.pop();
                states.push(sum(lhs, rhs));
            } else if (c == '*') {
                DynamicState ds = states.top();
                states.pop();
                states.push(iteration(ds));
            } else {
                throw std::invalid_argument("bad symbol in regex");
            }
        }
    }
    if (states.size() != 1) {
        throw std::invalid_argument("bad regex");
    }
    return states.top().get_min_word_len(k);
}
