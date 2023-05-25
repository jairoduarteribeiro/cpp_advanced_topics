// incr-decr.cpp by Bill Weinman [bw.org]
// as of 2022-10-21
#include <format>

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

class num {
    int value{};
public:
    num(int x = 0) : value{ x } {}
    int getvalue() const { return value; }
    void setvalue(int x) { value = x; }
    operator int() { return value; }
    num& operator++ ();
    num operator++ (int);
    num& operator-- ();
    num operator-- (int);
};


// pre-increment
num& num::operator++ () {
    print("pre-increment: ");
    value += 1;
    return *this;
}

// post-increment
num num::operator++ (int) {
    print("post-increment: ");
    auto temp = *this;
    value += 1;
    return temp;
}

// pre-decrement
num& num::operator-- () {
    print("pre-decrement: ");
    value -= 1;
    return *this;
}

// post-decrement
num num::operator-- (int) {
    print("post-decrement: ");
    auto temp = *this;
    value -= 1;
    return temp;
}

// formatter specialization
template<>
struct std::formatter<num> : std::formatter<unsigned> {
    template<typename FormatContext>
    auto format(const num& o, FormatContext& ctx) {
        return format_to(ctx.out(), "{}", o.getvalue());
    }
};

int main() {
    num n(42);
    print("value is: {}\n", n);
    print("value is: {}\n", ++n);
    print("value is: {}\n", n);

    return 0;
}
