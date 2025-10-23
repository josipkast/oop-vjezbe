#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

// -------------------- 1) Fibonacci niz --------------------
int* fib_array(int n) {
    if (n <= 0) return nullptr;
    int* a = new int[n];
    a[0] = 1;
    if (n > 1) a[1] = 1;
    for (int i = 2; i < n; ++i) a[i] = a[i-1] + a[i-2];
    return a;
}

// -------------------- 2) “Vektor” bez std::vector --------------------
struct Vector {
    int* data;
    int  size;      // logièka velièina
    int  capacity;  // fizièka velièina
};

// kreira novi vektor s poèetnim kapacitetom
Vector vector_new(int initial_capacity = 4) {
    if (initial_capacity < 1) initial_capacity = 1;
    Vector v;
    v.data = new int[initial_capacity];
    v.size = 0;
    v.capacity = initial_capacity;
    return v;
}

// oslobaða memoriju vektora
void vector_delete(Vector& v) {
    delete[] v.data;
    v.data = nullptr;
    v.size = 0;
    v.capacity = 0;
}

// interno: realokacija na duplo
void vector_grow(Vector& v) {
    int new_cap = v.capacity * 2;
    int* nd = new int[new_cap];
    for (int i = 0; i < v.size; ++i) nd[i] = v.data[i];
    delete[] v.data;
    v.data = nd;
    v.capacity = new_cap;
}

// dodaje element na kraj (po potrebi alocira duplo)
void vector_push_back(Vector& v, int value) {
    if (v.size >= v.capacity) vector_grow(v);
    v.data[v.size++] = value;
}

// uklanja element s kraja
void vector_pop_back(Vector& v) {
    if (v.size > 0) v.size--;
}

// vraæa prvi element
int vector_front(const Vector& v) {
    if (v.size == 0) { std::cerr << "Prazan vektor\n"; return 0; }
    return v.data[0];
}

// vraæa zadnji element
int vector_back(const Vector& v) {
    if (v.size == 0) { std::cerr << "Prazan vektor\n"; return 0; }
    return v.data[v.size - 1];
}

// vraæa logièku velièinu
int vector_size(const Vector& v) { return v.size; }

// -------------------- 3) Matrica na heapu --------------------
struct Matrix {
    int rows, cols;
    double* a; // èuvamo u 1D, indeks (r,c) -> r*cols + c
};

Matrix mat_new(int r, int c) {
    Matrix m{r, c, nullptr};
    if (r > 0 && c > 0) m.a = new double[r * c]{};
    return m;
}

void mat_delete(Matrix& m) {
    delete[] m.a;
    m.a = nullptr;
    m.rows = m.cols = 0;
}

double& MAT(Matrix& m, int r, int c) { return m.a[r * m.cols + c]; }
double  MATC(const Matrix& m, int r, int c) { return m.a[r * m.cols + c]; }

// unos matrice mxn
void mat_input(Matrix& m) {
    for (int i = 0; i < m.rows; ++i)
        for (int j = 0; j < m.cols; ++j) {
            std::cout << "A[" << i << "][" << j << "] = ";
            std::cin >> MAT(m, i, j);
        }
}

// generiranje u rasponu [lo, hi]
void mat_generate(Matrix& m, double lo, double hi) {
    for (int i = 0; i < m.rows; ++i)
        for (int j = 0; j < m.cols; ++j) {
            double u = std::rand() / double(RAND_MAX); // [0,1]
            MAT(m, i, j) = lo + (hi - lo) * u;
        }
}

// zbrajanje
Matrix mat_add(const Matrix& A, const Matrix& B) {
    if (A.rows != B.rows || A.cols != B.cols) {
        std::cerr << "Dimenzije za zbrajanje ne odgovaraju.\n";
        return Matrix{0,0,nullptr};
    }
    Matrix C = mat_new(A.rows, A.cols);
    for (int i = 0; i < A.rows; ++i)
        for (int j = 0; j < A.cols; ++j)
            C.a[i*A.cols + j] = A.a[i*A.cols + j] + B.a[i*B.cols + j];
    return C;
}

// oduzimanje
Matrix mat_sub(const Matrix& A, const Matrix& B) {
    if (A.rows != B.rows || A.cols != B.cols) {
        std::cerr << "Dimenzije za oduzimanje ne odgovaraju.\n";
        return Matrix{0,0,nullptr};
    }
    Matrix C = mat_new(A.rows, A.cols);
    for (int i = 0; i < A.rows; ++i)
        for (int j = 0; j < A.cols; ++j)
            C.a[i*A.cols + j] = A.a[i*A.cols + j] - B.a[i*B.cols + j];
    return C;
}

// množenje
Matrix mat_mul(const Matrix& A, const Matrix& B) {
    if (A.cols != B.rows) {
        std::cerr << "Dimenzije za mnozenje ne odgovaraju.\n";
        return Matrix{0,0,nullptr};
    }
    Matrix C = mat_new(A.rows, B.cols);
    for (int i = 0; i < A.rows; ++i)
        for (int k = 0; k < A.cols; ++k) {
            double aik = A.a[i*A.cols + k];
            for (int j = 0; j < B.cols; ++j)
                C.a[i*C.cols + j] += aik * B.a[k*B.cols + j];
        }
    return C;
}

// transponiranje
Matrix mat_transpose(const Matrix& A) {
    Matrix T = mat_new(A.cols, A.rows);
    for (int i = 0; i < A.rows; ++i)
        for (int j = 0; j < A.cols; ++j)
            T.a[j*T.cols + i] = A.a[i*A.cols + j];
    return T;
}

// ispis na 4 decimale, poravnato udesno
void mat_print(const Matrix& m) {
    std::cout << std::fixed << std::setprecision(4);
    for (int i = 0; i < m.rows; ++i) {
        for (int j = 0; j < m.cols; ++j)
            std::cout << std::setw(12) << MATC(m, i, j);
        std::cout << '\n';
    }
}

// -------------------- Demo u main --------------------
int main() {
    std::srand(unsigned(std::time(nullptr)));

    // 1) Fibonacci
    std::cout << "Fibonacci niz (n=10):\n";
    int n = 10;
    int* fib = fib_array(n);
    for (int i = 0; i < n; ++i) std::cout << fib[i] << (i+1<n ? ' ' : '\n');
    delete[] fib;

    // 2) “Vektor”
    std::cout << "\nTest vektora:\n";
    Vector v = vector_new(2);
    vector_push_back(v, 5);
    vector_push_back(v, 7);
    vector_push_back(v, 9); // prisilit ce realokaciju
    std::cout << "size=" << vector_size(v)
              << " front=" << vector_front(v)
              << " back=" << vector_back(v) << "\n";
    vector_pop_back(v);
    std::cout << "nakon pop_back, size=" << vector_size(v)
              << " back=" << vector_back(v) << "\n";
    vector_delete(v);

    // 3) Matrice
    std::cout << "\nMatrice A(2x3) i B(3x2) generirane u [0,1]:\n";
    Matrix A = mat_new(2,3);
    Matrix B = mat_new(3,2);
    mat_generate(A, 0.0, 1.0);
    mat_generate(B, 0.0, 1.0);

    std::cout << "A:\n"; mat_print(A);
    std::cout << "B:\n"; mat_print(B);

    Matrix AT = mat_transpose(A);
    std::cout << "A^T:\n"; mat_print(AT);

    Matrix C = mat_mul(A, B);
    std::cout << "C = A * B:\n"; mat_print(C);

    // primjer zbrajanja/oduzimanja: napravimo D istih dimenzija kao A
    Matrix D = mat_new(2,3);
    mat_generate(D, -1.0, 1.0);

    Matrix S = mat_add(A, D);
    Matrix M = mat_sub(A, D);
    std::cout << "S = A + D:\n"; mat_print(S);
    std::cout << "M = A - D:\n"; mat_print(M);

    // èišæenje
    mat_delete(A);
    mat_delete(B);
    mat_delete(AT);
    mat_delete(C);
    mat_delete(D);
    mat_delete(S);
    mat_delete(M);

    return 0;
}
