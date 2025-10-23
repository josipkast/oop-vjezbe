//1.
#include <iostream>
#include <iomanip>
int main()
{
    bool flag;
    std::cout << "unesi " << true << " - " << false << std::endl;
    std::cin >> flag;
    std::cout << std::boolalpha << flag << std::endl;
    int a = 255;
    std::cout << "hex " << std::hex << a << std::endl;
    std::cout << "dec " << std::dec << a << std::endl;
    std::cout << "oct " << std::oct << a << std::endl;
    double pi = 3.141592;
    std::cout << "pi = " << std::scientific << std::uppercase;
    std::cout << std::setprecision(7) << std::setw(20);
    std::cout << std::setfill('0');
    std::cout << pi << std::endl;
}

//2.
#include <iostream>

int limit(int value, int low = 0, int high = 100) {
    if (value < low) return low;
    if (value > high) return high;
    return value;
}

double limit(double value, double low = 0.0, double high = 100.0) {
    if (value < low) return low;
    if (value > high) return high;
    return value;
}

int main() {
    std::cout << limit(120) << std::endl;
    std::cout << limit(-5) << std::endl;
    std::cout << limit(2.5) << std::endl;

}
//3.
#include <iostream>
#include <string>
#include <cctype>

int main() {
    std::string string;
    std::cout << "Unesi string: ";
    std::getline(std::cin, string);

    for (char& znak : string) {
        if (std::isalpha(znak))
            znak = std::toupper(znak);
        else if (std::isdigit(znak))
            znak = '*';
        else if (znak == ' ' || znak == '\t')
            znak = '_';
    }

    std::cout << "Rezultat: " << string << std::endl;
}
//4.
#include <iostream>

int& at(int niz[], int i) {
    return niz[i];
}

int main() {
    int niz[] = { 1,2,3,4,5,6 };
    int i = 2;

    at(niz, i) = at(niz, i) + 1;

    std::cout << "Element na indeksu " << i << " sada je: " << niz[i] << std::endl;
    return 0;
}