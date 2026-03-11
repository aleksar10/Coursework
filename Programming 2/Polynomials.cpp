#include <iostream>
#include <cstdarg>
using namespace std;

class POLYNOMIAL {
    struct Fraction {
        long long numerator;
        long long denominator;
    };
    int degree;
    int* coefficients;
    struct Fraction* fractionCoeffs;

    static long long calcGCD(long long a, long long b) {
        while (b != 0) {
            long long tmp = b;
            b = a % b;
            a = tmp;
        }
        return a;
    }
    long long findCoefficientsGCD() const {
        if (degree == 0) {
            return coefficients[0];
        }
        long long result = coefficients[0];
        for (int i = 1; i <= degree; ++i) {
            result = calcGCD(result, coefficients[i]);
            if (result == 1) {
                return 1;
            }
        }
        return result;
    }
    void applyGCD(POLYNOMIAL* poly) const {
        long long gcdValue = polyAbs(poly->findCoefficientsGCD());
        if (gcdValue != 0 && gcdValue != 1) {
            for (int i = 0; i <= poly->degree; ++i) {
                poly->coefficients[i] /= gcdValue;
            }
        }
        while (poly->degree > 0 && poly->coefficients[poly->degree] == 0) {
            --poly->degree;
        }
    }
    static long long calcLCM(long long a, long long b) {
        if (a < 0) a = -a;
        if (b < 0) b = -b;

        return (a / calcGCD(a, b)) * b;
    }
    long long findLCM() {
        if (degree == 0) {
            return fractionCoeffs[0].denominator;
        }
        long long result = fractionCoeffs[0].denominator;
        for (int i = 1; i <= degree; i++) {
            result = calcLCM(result, fractionCoeffs[i].denominator);
        }
        return result;        
    }
    static long long polyAbs(long long input) {
        if (input < 0)
            return -input;
        return input;
    }
    static void reduceFraction(struct Fraction& fraction) {
        long long localGCD = calcGCD(fraction.numerator, fraction.denominator);
        fraction.numerator /= localGCD;
        fraction.denominator /= localGCD;
        if (fraction.denominator < 0) {
            fraction.numerator = -fraction.numerator;
            fraction.denominator = -fraction.denominator;
        }
    }
    POLYNOMIAL polyMultiplication(const POLYNOMIAL& left, const POLYNOMIAL& right) const {
        struct Fraction helper;
        POLYNOMIAL result(helper, left.degree + right.degree);

        for (int i = 0; i <= left.degree; i++) {
            for (int j = 0; j <= right.degree; j++) {
                result.fractionCoeffs[i + j] = addFractions(result.fractionCoeffs[i + j],
                    multiplyFractions(left.fractionCoeffs[i], right.fractionCoeffs[j]));
                reduceFraction(result.fractionCoeffs[i + j]);
            }
        }
        return result;
    }
    POLYNOMIAL polySubtract(const POLYNOMIAL& left, const POLYNOMIAL& right) const {
        int maxDegree = max(left.degree, right.degree);
        struct Fraction helper;
        POLYNOMIAL result(helper, maxDegree);
        struct Fraction coeff1, coeff2;

        for (int i = 0; i <= maxDegree; i++) {
            if (i <= left.degree)
                coeff1 = left.fractionCoeffs[i];
            else {
                coeff1.numerator = 0;
                coeff1.denominator = 1;
            }
            if (i <= right.degree)
                coeff2 = right.fractionCoeffs[i];
            else {
                coeff2.numerator = 0;
                coeff2.denominator = 1;
            }
            result.fractionCoeffs[i].denominator = calcLCM(coeff1.denominator, coeff2.denominator);
            result.fractionCoeffs[i].numerator =
                        (result.fractionCoeffs[i].denominator / coeff1.denominator) * coeff1.numerator -
                        (result.fractionCoeffs[i].denominator / coeff2.denominator) * coeff2.numerator;
            reduceFraction(result.fractionCoeffs[i]);
        }
        return result;
    }
    static struct Fraction addFractions(struct Fraction left, struct Fraction right) {
        struct Fraction result;
        result.denominator = calcLCM(left.denominator, right.denominator);
        result.numerator = ((result.denominator / left.denominator) * left.numerator) +
                           ((result.denominator / right.denominator) * right.numerator);
        reduceFraction(result);
        return result;
    }
    static struct Fraction divideFractions(struct Fraction left, struct Fraction right) {
        struct Fraction result;
        result.numerator = left.numerator * right.denominator;
        result.denominator = left.denominator * right.numerator;
        if (result.denominator < 0) {
            result.numerator = -result.numerator;
            result.denominator = -result.denominator;
        }
        reduceFraction(result);
        return result;
    }
    static struct Fraction multiplyFractions(struct Fraction left, struct Fraction right) {
        struct Fraction result;
        result.numerator = left.numerator * right.numerator;
        result.denominator = left.denominator * right.denominator;
        reduceFraction(result);
        return result;
    }
public:
    static int overloaded;

    POLYNOMIAL() : degree(0), coefficients(new int[1]()), fractionCoeffs(NULL) {}
    POLYNOMIAL(const POLYNOMIAL& source) : degree(source.degree),
                                           coefficients(new int[degree + 1]),
                                           fractionCoeffs(NULL) {
        for (int i = 0; i <= degree; i++) {
            coefficients[i] = source.coefficients[i];
        }
        if (source.fractionCoeffs != NULL) {
            fractionCoeffs = new struct Fraction [degree + 1];
            for (int i = 0; i <= degree; i++) {
                fractionCoeffs[i].numerator = source.fractionCoeffs[i].numerator;
                fractionCoeffs[i].denominator = source.fractionCoeffs[i].denominator;
            }
        }
    }
    POLYNOMIAL(long polydegree) : degree(polydegree),
                                  coefficients(new int[degree + 1]()),
                                  fractionCoeffs(NULL) {}
    POLYNOMIAL(int polydegree, ...) : degree(polydegree),
                                      coefficients(new int[polydegree + 1]),
                                      fractionCoeffs(NULL) {
        va_list vl;
        va_start(vl, polydegree);
        for (int i = 0; i <= polydegree; i++) {
            coefficients[i] = va_arg(vl, int);
        }
        va_end(vl);
        applyGCD(this);
    }
    POLYNOMIAL(struct Fraction fraction, int polydegree) : degree(polydegree),
                                         coefficients(new int[degree + 1]()),
                                         fractionCoeffs(new struct Fraction[degree + 1]) {
        fraction = fraction;
        for (int i = 0; i <= degree; i++) {
            fractionCoeffs[i].numerator = 0;
            fractionCoeffs[i].denominator = 1;
        }
    }
    ~POLYNOMIAL() {
        if (coefficients != NULL) {
            delete[] coefficients;
            coefficients = NULL;
        }
        if (fractionCoeffs != NULL) {
            delete[] fractionCoeffs;
            fractionCoeffs = NULL;
        }
    }
    POLYNOMIAL& operator=(const POLYNOMIAL& source) {
        if (coefficients != NULL)
            delete[] coefficients;
        if (fractionCoeffs != NULL) {
            delete[] fractionCoeffs;
            fractionCoeffs = NULL;
        }
        degree = source.degree;
        coefficients = new int[degree + 1];
        for (int i = 0; i <= degree; i++) {
            coefficients[i] = source.coefficients[i];
        }
        if (source.fractionCoeffs != NULL) {
            fractionCoeffs = new struct Fraction[degree + 1];
            for (int i = 0; i <= degree; i++) {
                fractionCoeffs[i].numerator = source.fractionCoeffs[i].numerator;
                fractionCoeffs[i].denominator = source.fractionCoeffs[i].denominator;
            }
        }
        return *this;
    }
    POLYNOMIAL operator+(const POLYNOMIAL& other) {
        int maxDegree = max(degree, other.degree);
        POLYNOMIAL result((long)maxDegree);
        int coeff1, coeff2;

        for (int i = 0; i <= maxDegree; ++i) {
            if (i <= degree)
                coeff1 = coefficients[i];
            else
                coeff1 = 0;
            if (i <= other.degree)
                coeff2 = other.coefficients[i];
            else
                coeff2 = 0;
            result.coefficients[i] = coeff1 + coeff2;
        }
        applyGCD(&result);
        return result;
    }
    POLYNOMIAL& operator+=(const POLYNOMIAL& other) {
        *this = *this + other;
        return *this;
    }
    POLYNOMIAL operator-(const POLYNOMIAL& other) {
        int maxDegree = max(degree, other.degree);
        POLYNOMIAL result((long)maxDegree);
        int coeff1, coeff2;

        for (int i = 0; i <= maxDegree; ++i) {
            if (i <= degree)
                coeff1 = coefficients[i];
            else
                coeff1 = 0;
            if (i <= other.degree)
                coeff2 = other.coefficients[i];
            else
                coeff2 = 0;

            result.coefficients[i] = coeff1 - coeff2;
        }
        applyGCD(&result);

        return result;
    }
    POLYNOMIAL& operator-=(const POLYNOMIAL& other) {
        *this = *this - other;
        return *this;
    }
    POLYNOMIAL operator*(const POLYNOMIAL& other) {
        int resultDegree = degree + other.degree;
        POLYNOMIAL result((long)resultDegree);

        for (int i = 0; i <= degree; ++i) {
            for (int j = 0; j <= other.degree; ++j) {
                result.coefficients[i + j] += coefficients[i] * other.coefficients[j];
            }
        }
        applyGCD(&result);
        return result;
    }
    POLYNOMIAL& operator*=(const POLYNOMIAL& other) {
        *this = *this * other;
        return *this;
    }
    POLYNOMIAL operator-() {
        POLYNOMIAL result(*this);
        for (int i = 0; i <= result.degree; ++i) {
            result.coefficients[i] = -result.coefficients[i];
        }
        applyGCD(&result);
        return result;
    }
    POLYNOMIAL operator/(const POLYNOMIAL& inputDivisor) const {
        if ((inputDivisor.degree == 0 && inputDivisor.coefficients[0] == 0) ||
            (inputDivisor.degree > degree)) {
            return POLYNOMIAL();
        }
        int resultDegree = degree - inputDivisor.degree;
        struct Fraction helper;
        POLYNOMIAL quotient(helper, resultDegree);
        POLYNOMIAL divident(*this);
        POLYNOMIAL divisor(inputDivisor);

        divident.fractionCoeffs = new struct Fraction[divident.degree + 1];
        for (int i = 0; i <= divident.degree; i++) {
            divident.fractionCoeffs[i].numerator = divident.coefficients[i];
            divident.fractionCoeffs[i].denominator = 1;
        }
        divisor.fractionCoeffs = new struct Fraction[divisor.degree + 1];
        for (int i = 0; i <= divisor.degree; i++) {
            divisor.fractionCoeffs[i].numerator = divisor.coefficients[i];
            divisor.fractionCoeffs[i].denominator = 1;
        }
        for (int i = resultDegree; i >= 0; i--) {
            POLYNOMIAL monomial(helper, divident.degree - divisor.degree);
            quotient.fractionCoeffs[i] = monomial.fractionCoeffs[monomial.degree] =
                divideFractions(divident.fractionCoeffs[divident.degree], divisor.fractionCoeffs[divisor.degree]);
            POLYNOMIAL intermediary(helper, divident.degree);
            intermediary = polyMultiplication(monomial, divisor);
            divident = polySubtract(divident, intermediary);
            int decrease = 0;
            while (divident.degree > 0 && divident.fractionCoeffs[divident.degree].numerator == 0) {
                --divident.degree;
                ++decrease;
            }
            if (decrease > 1)
                i -= (decrease - 1);
            if ((divident.degree == 0) && (divident.fractionCoeffs[0].numerator == 0))
                break;
        }
        long long resultLCM = quotient.findLCM();
        for (int i = 0; i <= quotient.degree; i++) {
            quotient.coefficients[i] = (resultLCM / quotient.fractionCoeffs[i].denominator) *
                                        quotient.fractionCoeffs[i].numerator;
        }
        applyGCD(&quotient);
        return quotient;
    }
    POLYNOMIAL& operator/=(POLYNOMIAL& divisor) {
        *this = *this / divisor;
        return *this;
    }
    POLYNOMIAL operator%(const POLYNOMIAL& inputDivisor) {
        if ((inputDivisor.degree == 0 && inputDivisor.coefficients[0] == 0) ||
            (inputDivisor.degree > degree))
            return *this;
        int resultDegree = degree - inputDivisor.degree;
        struct Fraction helper;
        POLYNOMIAL quotient(helper, resultDegree);
        POLYNOMIAL divident(*this);
        POLYNOMIAL divisor(inputDivisor);

        divident.fractionCoeffs = new struct Fraction[divident.degree + 1];
        for (int i = 0; i <= divident.degree; i++) {
            divident.fractionCoeffs[i].numerator = divident.coefficients[i];
            divident.fractionCoeffs[i].denominator = 1;
        }
        divisor.fractionCoeffs = new struct Fraction[divisor.degree + 1];
        for (int i = 0; i <= divisor.degree; i++) {
            divisor.fractionCoeffs[i].numerator = divisor.coefficients[i];
            divisor.fractionCoeffs[i].denominator = 1;
        }
        for (int i = resultDegree; i >= 0; i--) {
            POLYNOMIAL monomial(helper, divident.degree - divisor.degree);
            quotient.fractionCoeffs[i] = monomial.fractionCoeffs[monomial.degree] =
                divideFractions(divident.fractionCoeffs[divident.degree], divisor.fractionCoeffs[divisor.degree]);
            POLYNOMIAL intermediary(helper, divident.degree);
            intermediary = polyMultiplication(monomial, divisor);
            divident = polySubtract(divident, intermediary);
            int decrease = 0;
            while (divident.degree > 0 && divident.fractionCoeffs[divident.degree].numerator == 0) {
                --divident.degree;
                ++decrease;
            }
            if (decrease > 1)
                i -= (decrease - 1);
            if ((divident.degree == 0) && (divident.fractionCoeffs[0].numerator == 0))
                break;
        }
        long long resultLCM = divident.findLCM();
        for (int i = 0; i <= divident.degree; i++) {
            divident.coefficients[i] = (resultLCM / divident.fractionCoeffs[i].denominator) *
                                        divident.fractionCoeffs[i].numerator;
        }
        applyGCD(&divident);
        return divident;
    }
    POLYNOMIAL& operator%=(const POLYNOMIAL& divisor) {
        *this = *this % divisor;
        return *this;
    }
    POLYNOMIAL operator>>(int shift) const {
        if (shift < 0) {
            return POLYNOMIAL();
        }
        if ((degree > 0) || (coefficients[0] != 0)) {
            POLYNOMIAL result((long)(degree + shift));
            for (int i = 0; i <= degree; ++i) {
                result.coefficients[i + shift] = coefficients[i];
            }
            return result;
        }
        return *this;
    }
    POLYNOMIAL& operator>>=(int shift) {
        if (shift < 0) {
            degree = 0;
            if (coefficients != NULL)
                delete[] coefficients;
            coefficients = new int[1]();
            return *this;
        }
        if ((degree > 0) || (coefficients[0] != 0)) {
            int newDegree = degree + shift;
            int* newCoefficients = new int[newDegree + 1]();
            for (int i = 0; i <= degree; ++i) {
                newCoefficients[i + shift] = coefficients[i];
            }
            delete[] coefficients;
            degree = newDegree;
            coefficients = newCoefficients;
        }
        return *this;
    }
    POLYNOMIAL operator<<(int shift) {
        if ((shift > degree) || (shift < 0)) {
            return POLYNOMIAL();
        }
        POLYNOMIAL result((long)(degree - shift));
        for (int i = 0; i <= result.degree; ++i) {
            result.coefficients[i] = coefficients[i + shift];
        }
        applyGCD(&result);
        return result;
    }
    POLYNOMIAL& operator<<=(int shift) {
        if ((shift > degree) || (shift < 0)) {
            degree = 0;
            if (coefficients != NULL)
                delete[] coefficients;
            coefficients = new int[1]();
            return *this;
        }
        degree -= shift;
        int* newCoefficients = new int[degree + 1];
        for (int i = 0; i <= degree; ++i) {
            newCoefficients[i] = coefficients[i + shift];
        }
        delete[] coefficients;
        coefficients = newCoefficients;
        applyGCD(this);
        return *this;
    }
    POLYNOMIAL& operator++() {
        for (int i = degree; i >= 0; i--) {
            coefficients[i]++;
        }
        applyGCD(this);
        return *this;
    }
    POLYNOMIAL operator++(int) {
        POLYNOMIAL temp = *this;

        for (int i = degree; i >= 0; i--) {
            coefficients[i]++;
        }
        applyGCD(this);
        return temp;
    }
    POLYNOMIAL& operator--() {
        for (int i = 0; i <= degree; ++i) {
            --coefficients[i];
        }
        applyGCD(this);
        return *this;
    }
    POLYNOMIAL operator--(int) {
        POLYNOMIAL temp(*this);

        for (int i = 0; i <= degree; ++i) {
            --coefficients[i];
        }
        applyGCD(this);
        return temp;
    }
    void* operator new(size_t size) {
        overloaded++;
        return ::operator new(size);
    }
    void operator delete(void* ptr) {
        overloaded--;
        ::operator delete(ptr);
    }
    friend ostream& operator<<(ostream&, const POLYNOMIAL&);
    friend istream& operator>>(istream&, POLYNOMIAL&);
    friend bool operator<(const POLYNOMIAL&, const POLYNOMIAL&);
    friend bool operator<=(const POLYNOMIAL&, const POLYNOMIAL&);
    friend bool operator>(const POLYNOMIAL&, const POLYNOMIAL&);
    friend bool operator>=(const POLYNOMIAL&, const POLYNOMIAL&);
    friend bool operator==(const POLYNOMIAL&, const POLYNOMIAL&);
    friend bool operator!=(const POLYNOMIAL&, const POLYNOMIAL&);
};

ostream& operator<<(ostream& os, const POLYNOMIAL& pn) {
    os << "( ";
    if (pn.coefficients != NULL) {
        for (int i = 0; i <= pn.degree; i++) {
            os << pn.coefficients[i];
            if (i < pn.degree)
                os << ", ";
        }
    }
    os << " )";
    return os;
}

istream& operator>>(istream&is, POLYNOMIAL& pn) {
    if (pn.coefficients != NULL) {
        delete[] pn.coefficients;
    }
    is >> pn.degree;
    pn.coefficients = new int[pn.degree + 1];
    for (int i = 0; i <= pn.degree; i++) {
        is >> pn.coefficients[i];
    }
    pn.applyGCD(&pn);
    return is;
}
bool operator<(const POLYNOMIAL& lhs, const POLYNOMIAL& rhs) {
    if (lhs.degree != rhs.degree) {
        return lhs.degree < rhs.degree;
    }
    for (int i = lhs.degree; i >= 0; --i) {
        if (lhs.coefficients[i] != rhs.coefficients[i]) {
            return lhs.coefficients[i] < rhs.coefficients[i];
        }
    }
    return false;
}
bool operator<=(const POLYNOMIAL& lhs, const POLYNOMIAL& rhs) {
    if (lhs.degree != rhs.degree) {
        return lhs.degree < rhs.degree;
    }
    for (int i = lhs.degree; i >= 0; --i) {
        if (lhs.coefficients[i] != rhs.coefficients[i]) {
            return lhs.coefficients[i] < rhs.coefficients[i];
        }
    }
    return true;
}
bool operator>(const POLYNOMIAL& lhs, const POLYNOMIAL& rhs) {
    return !(lhs <= rhs);
}
bool operator>=(const POLYNOMIAL& lhs, const POLYNOMIAL& rhs) {
    return !(lhs < rhs);
}
bool operator==(const POLYNOMIAL& lhs, const POLYNOMIAL& rhs) {
    if (lhs.degree != rhs.degree) {
        return false;
    }
    for (int i = lhs.degree; i >= 0; --i) {
        if (lhs.coefficients[i] != rhs.coefficients[i]) {
            return false;
        }
    }
    return true;
}
bool operator!=(const POLYNOMIAL& lhs, const POLYNOMIAL& rhs) {
    return !(lhs == rhs);
}