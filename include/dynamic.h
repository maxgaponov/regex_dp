#pragma once
#include <vector>

class DynamicState {
public:
    DynamicState(char x, int k);
    DynamicState(char x, int k, char a);
    void update_min_word_len(int count, size_t value);
    void update_xword_in_l(int len);
    size_t get_min_word_len(int count) const;
    bool is_xword_in_l(int len) const;
    char get_x() const;
    int get_k() const;
    static const size_t INF;
private:
    char x_;
    int k_;
    std::vector<size_t> min_word_len_;
    std::vector<bool> xword_in_l_;
};

