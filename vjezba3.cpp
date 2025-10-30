// OOP vjezba 3 - sve u jednom .cpp
// Compile: MSVC /std:c++17 ili novije

#include <iostream>
#include <string>
#include <cstddef>
#include <algorithm> // std::swap

// ---------- 1) sort za int s pokazivaèem na usporedbu ----------
inline bool ascending(int a, int b) { return a < b; }
inline bool descending(int a, int b) { return a > b; }

// jednostavan bubble sort radi jasnoæe zadatka
void sort(int arr[], std::size_t n, bool (*cmp)(int, int)) {
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j + 1 < n - i; ++j) {
            if (!cmp(arr[j], arr[j + 1])) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// ---------- 2) template sorta s generièkim tipom ----------
template <typename T>
inline bool ascendingT(T a, T b) { return a < b; }

template <typename T>
inline bool descendingT(T a, T b) { return a > b; }

template <typename T>
void sortT(T arr[], std::size_t n, bool (*cmp)(T, T)) {
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j + 1 < n - i; ++j) {
            if (!cmp(arr[j], arr[j + 1])) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// ---------- 3) “lambda zadaci” pretvoreni u èiste funkcije nad nizom ----------
void prepravi_parne_neparne(int arr[], std::size_t n) {
    for (std::size_t i = 0; i < n; ++i) {
        if (arr[i] % 2 == 0) arr[i] /= 2;  // parne prepolovi
        else                 arr[i] *= 2;  // neparne udvostruèi
    }
}

void suma_i_produkt(int arr[], std::size_t n, int& s, int& p) {
    s = 0; p = 1;
    for (std::size_t i = 0; i < n; ++i) {
        s += arr[i];
        p *= arr[i];
    }
}

int suma_vecih_od_praga(int arr[], std::size_t n, int prag) {
    int s = 0;
    for (std::size_t i = 0; i < n; ++i) if (arr[i] > prag) s += arr[i];
    return s;
}

// ---------- 4) Student + generièko filtriranje ----------
struct Student {
    std::string ime;
    std::string jmbag;
    int godina;   // godina studija
    int ects;     // položeni ECTS u tekuæoj godini
    double prosjek;
};

// Filtriraj i izvrši akciju
void filtar_students(Student arr[], std::size_t n,
    void (*akcija)(Student&),
    bool (*filtar)(Student&)) {
    for (std::size_t i = 0; i < n; ++i)
        if (filtar(arr[i])) akcija(arr[i]);
}

// Akcije ispisa
void ispis(Student& s) {
    std::cout << s.ime << " (" << s.jmbag << "), god: " << s.godina
        << ", ECTS: " << s.ects << ", prosjek: " << s.prosjek << "\n";
}
void ispis_prosjek(Student& s) {
    std::cout << "[PROSJEK > 3.5] "; ispis(s);
}
void ispis_ects(Student& s) {
    std::cout << "[ECTS >= 45] ";    ispis(s);
}

// ---------- MAIN: demonstracija svega ----------
int main() {
    // 1) sort(int) s cmp pokazivaèem
    int niz[] = { 5, 2, 9, 1, 7 };
    std::size_t n = sizeof(niz) / sizeof(niz[0]);

    sort(niz, n, ascending);
    std::cout << "Uzlazno (int): ";
    for (auto x : niz) std::cout << x << ' ';
    std::cout << "\n";

    sort(niz, n, descending);
    std::cout << "Silazno (int):  ";
    for (auto x : niz) std::cout << x << ' ';
    std::cout << "\n\n";

    // 2) template sort za double
    double nizD[] = { 3.3, -1.2, 4.4, 0.0 };
    sortT(nizD, 4, ascendingT<double>);
    std::cout << "Uzlazno (double): ";
    for (double d : nizD) std::cout << d << ' ';
    std::cout << "\n\n";

    // 3) “lambda” zadaci nad nizom
    int arr2[] = { 1, 2, 3, 4, 5, 20 };
    std::size_t n2 = sizeof(arr2) / sizeof(arr2[0]);

    prepravi_parne_neparne(arr2, n2);
    std::cout << "Parni/Neparni prepravljeni: ";
    for (int x : arr2) std::cout << x << ' ';
    std::cout << "\n";

    int s, p;
    suma_i_produkt(arr2, n2, s, p);
    std::cout << "Suma: " << s << ", produkt: " << p << "\n";
    std::cout << "Suma vecih od 10: " << suma_vecih_od_praga(arr2, n2, 10) << "\n\n";

    // 4) studenti + filtriranja
    Student studenti[] = {
        {"Ana",  "001", 1,  30, 3.8},
        {"Marko","002", 2,  48, 4.1},
        {"Iva",  "003", 1,   0, 2.9},
        {"Luka", "004", 3,  60, 3.2},
    };
    std::size_t br = sizeof(studenti) / sizeof(studenti[0]);

    // Uvjeti kao funkcijski pokazivaèi (pomoæu statièkih lambdi)
    auto uvjet_prva_godina_polozio = [](Student& s) -> bool {
        return s.godina == 1 && s.ects > 0;
        };
    auto uvjet_prosjek_35 = [](Student& s) -> bool {
        return s.prosjek > 3.5;
        };
    auto uvjet_ects_45 = [](Student& s) -> bool {
        return s.ects >= 45;
        };

    std::cout << "Studenti 1. godina, polozili barem 1 ispit:\n";
    filtar_students(studenti, br, ispis, +uvjet_prva_godina_polozio);
    std::cout << "\n";

    std::cout << "Studenti s prosjekom > 3.5:\n";
    filtar_students(studenti, br, ispis_prosjek, +uvjet_prosjek_35);
    std::cout << "\n";

    std::cout << "Studenti s >= 45 ECTS:\n";
    filtar_students(studenti, br, ispis_ects, +uvjet_ects_45);
    std::cout << "\n";

    
}
