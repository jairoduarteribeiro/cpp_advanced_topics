// rational2.cpp by Bill Weinman [bw.org]
// updated 2022-10-24
#include <format>
#include <string>

using std::string;

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

const std::string nanstr {"[NAN]"};

class Rational {
    int n{ 0 };
    int d{ 1 };
public:
    Rational(int numerator = 0, int denominator = 1) : n(numerator), d(denominator) {}
    Rational(const Rational& rhs) : n(rhs.n), d(rhs.d) {}    // copy constructor
    ~Rational();
    int numerator() const { return n; };
    int denominator() const { return d; };
    Rational reduce() const;        // reduce fraction
    std::string str() const;        // return a formatted STL string
    std::string raw_str() const;    // return a non-reduced STL string
    Rational& operator = (const Rational&);  // assignment
    operator string() { return str(); }
};

Rational Rational::reduce() const {
    if (n == 0 || d <= 3) return *this;
    for (auto div = d - 1; div; --div) {
        if (n % div == 0 && d % div == 0) {
            return Rational(n / div, d / div);
        }
    }
    return *this;
}

std::string Rational::str() const {
    if (d == 0) return nanstr;
    if (d == 1 || n == 0) return std::to_string(n);

    auto abs_n = abs(n);     // absolute value
    if (abs_n > d) {
        auto whole = n / d;
        auto remainder = abs_n % d;
        if (remainder) return std::to_string(whole) + " " + Rational(remainder, d).str();
        else return std::to_string(whole);
    }
    else {
        return reduce().raw_str();
    }
}

std::string Rational::raw_str() const {
    return std::to_string(n) + "/" + std::to_string(d);
}

Rational& Rational::operator = (const Rational& rhs) {
    if (this != &rhs) {
        n = rhs.numerator();
        d = rhs.denominator();
    }
    return *this;
}

Rational operator + (const Rational& lhs, const Rational& rhs) {
    return Rational((lhs.numerator() * rhs.denominator()) + (lhs.denominator() * rhs.numerator()),
        lhs.denominator() * rhs.denominator());
}

Rational operator - (const Rational& lhs, const Rational& rhs) {
    return Rational((lhs.numerator() * rhs.denominator()) - (lhs.denominator() * rhs.numerator()),
        lhs.denominator() * rhs.denominator());
}

Rational operator * (const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
}

Rational operator / (const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.numerator() * rhs.denominator(), lhs.denominator() * rhs.numerator());
}

Rational::~Rational() {
    n = 0; d = 1;
}

// formatter specialization
template<>
struct std::formatter<Rational> : std::formatter<unsigned> {
    template<typename FormatContext>
    auto format(const Rational& o, FormatContext& ctx) {
        return format_to(ctx.out(), "{}", o.str());
    }
};

void p(const string& s) {
    print("The string is {}\n", s);
}

int main() {
    Rational a{ 4, 3 };  // 1 1/3

    print("a + 20 = {}\n", a + 20);
    print("a + 20 = {}\n", a - 20);
    print("a + 20 = {}\n", a * 20);
    print("a + 20 = {}\n", a / 20);

    print("\n");

    print("20 + a = {}\n", 20 + a);
    print("20 - a = {}\n", 20 - a);
    print("20 * a = {}\n", 20 * a);
    print("20 / a = {}\n", 20 / a);

    string s{"Rational is "};
    s += a;
    print("{}\n", s);

    p(a);
}
