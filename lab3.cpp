#include <iostream>




void f(int x) {
    unsigned int res = 1;
    int troiki = 1;
    int pyatorki = 1;
    int semerki = 1;

    while (res <= x) {
        while (res <= x) {
            while (res <= x) {
                std::cout << res << ' ';
                semerki *= 7;
                res = troiki * pyatorki * semerki;
            }
            semerki = 1;
            pyatorki *= 5;
            res = troiki * pyatorki * semerki;
        }
        pyatorki = 1;
        troiki *= 3;
        res = troiki * pyatorki * semerki;
    }
    std::cout << '\n';
}


int main() {
    f(1900000000);
}