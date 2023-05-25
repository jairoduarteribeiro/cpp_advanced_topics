// functor.cpp by Bill Weinman [bw.org]
// updated 2022-10-21
#include <format>

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

class MultBy {
    int mult{};
public:
    MultBy(int n = 1) : mult(n) {}
    int operator () (int n) const { return mult * n; }
};

int main() {
    const MultBy times4(4);
    const MultBy times10(10);

    const auto times15 = [](int n) { return n * 15; };

    print("times4(5) is {}\n", times4(5));
    print("times4(15) is {}\n", times4(15));
    print("times10(5) is {}\n", times10(5));
    print("times10(15) is {}\n", times10(15));
    print("times15(5) is {}\n", times15(5));
    print("times15(15) is {}\n", times15(15));
}
