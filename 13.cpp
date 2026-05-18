#include <iostream>
#include <cstring>

// =========================== Пункт a ===========================
// Шаблонный класс множество (Set) – хранит указатели на уникальные элементы
template<typename T>
class Set {
private:
    T** data;         // массив указателей на элементы
    int size;         // текущее количество элементов
    int capacity;     // выделенная ёмкость

    void resize(int new_cap) {
        T** new_data = new T*[new_cap];
        for (int i = 0; i < size; ++i)
            new_data[i] = data[i];
        delete[] data;
        data = new_data;
        capacity = new_cap;
    }

public:
    Set() : data(nullptr), size(0), capacity(0) {}

    // Конструктор копирования (глубокое копирование)
    Set(const Set& other) : data(nullptr), size(0), capacity(0) {
        for (int i = 0; i < other.size; ++i)
            add(*other.data[i]);
    }

    // Оператор присваивания
    Set& operator=(const Set& other) {
        if (this != &other) {
            Set tmp(other);
            swap(tmp);
        }
        return *this;
    }

    void swap(Set& other) {
        std::swap(data, other.data);
        std::swap(size, other.size);
        std::swap(capacity, other.capacity);
    }

    ~Set() {
        for (int i = 0; i < size; ++i)
            delete data[i];
        delete[] data;
    }

    // Добавление элемента (если ещё нет)
    void add(const T& elem) {
        if (contains(elem)) return;
        if (size == capacity) {
            int new_cap = (capacity == 0) ? 4 : capacity * 2;
            resize(new_cap);
        }
        data[size++] = new T(elem);
    }

    // Проверка принадлежности
    bool contains(const T& elem) const {
        for (int i = 0; i < size; ++i)
            if (*data[i] == elem)
                return true;
        return false;
    }

    int getSize() const { return size; }

    const T& operator[](int index) const { return *data[index]; }

    // Оператор > (элемент принадлежит множеству) – глобальный друг
    friend bool operator>(const T& elem, const Set<T>& set) {
        return set.contains(elem);
    }

    // Оператор * (пересечение множеств)
    friend Set<T> operator*(const Set<T>& a, const Set<T>& b) {
        Set<T> result;
        for (int i = 0; i < a.size; ++i) {
            if (b.contains(*a.data[i]))
                result.add(*a.data[i]);
        }
        return result;
    }

    // Оператор < (подмножество)
    friend bool operator<(const Set<T>& a, const Set<T>& b) {
        for (int i = 0; i < a.size; ++i)
            if (!b.contains(*a.data[i]))
                return false;
        return true;
    }

    void print() const {
        std::cout << "{ ";
        for (int i = 0; i < size; ++i) {
            std::cout << *data[i] << (i == size-1 ? " " : ", ");
        }
        std::cout << "}";
    }
};

// =========================== Пункт b ===========================
// Базовый абстрактный класс Matrix
class Matrix {
private:
    static int totalElements;
protected:
    int rows_, cols_;
public:
    Matrix(int r, int c) : rows_(r), cols_(c) {
        totalElements += rows_ * cols_;
    }
    virtual ~Matrix() {
        totalElements -= rows_ * cols_;
    }
    static int getTotalElements() { return totalElements; }

    // Чисто виртуальные функции (не менее двух)
    virtual void print() const = 0;
    virtual bool isEqual(const Matrix& other) const = 0;
    virtual Matrix* clone() const = 0;  // для копирования в Set

    int rows() const { return rows_; }
    int cols() const { return cols_; }
};
int Matrix::totalElements = 0;

// Квадратная матрица (хранит все элементы)
class SquareMatrix : public Matrix {
private:
    int** data;
public:
    // Конструктор по умолчанию (нужен для массивов в Set? – нет, мы используем указатели)
    // Но для удобства можно создать конструктор размером 1x1
    SquareMatrix() : Matrix(1,1) {
        data = new int*[1];
        data[0] = new int[1];
        data[0][0] = 0;
    }
    SquareMatrix(int n) : Matrix(n, n) {
        data = new int*[rows_];
        for (int i = 0; i < rows_; ++i) {
            data[i] = new int[cols_];
            for (int j = 0; j < cols_; ++j)
                data[i][j] = 0;
        }
    }
    SquareMatrix(int n, int init_val) : SquareMatrix(n) {
        for (int i = 0; i < rows_; ++i)
            for (int j = 0; j < cols_; ++j)
                data[i][j] = init_val;
    }
    SquareMatrix(const SquareMatrix& other) : Matrix(other.rows_, other.cols_) {
        data = new int*[rows_];
        for (int i = 0; i < rows_; ++i) {
            data[i] = new int[cols_];
            for (int j = 0; j < cols_; ++j)
                data[i][j] = other.data[i][j];
        }
    }
    ~SquareMatrix() {
        for (int i = 0; i < rows_; ++i)
            delete[] data[i];
        delete[] data;
    }

    void set(int i, int j, int val) { data[i][j] = val; }
    int get(int i, int j) const { return data[i][j]; }

    void print() const override {
        std::cout << "SquareMatrix " << rows_ << "x" << cols_ << ":\n";
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j)
                std::cout << data[i][j] << " ";
            std::cout << "\n";
        }
    }

    bool isEqual(const Matrix& other) const override {
        const SquareMatrix* p = dynamic_cast<const SquareMatrix*>(&other);
        if (!p) return false;
        if (rows_ != p->rows_ || cols_ != p->cols_) return false;
        for (int i = 0; i < rows_; ++i)
            for (int j = 0; j < cols_; ++j)
                if (data[i][j] != p->data[i][j]) return false;
        return true;
    }

    Matrix* clone() const override {
        return new SquareMatrix(*this);
    }

    // Для использования в Set нужен operator==
    bool operator==(const SquareMatrix& other) const {
        return isEqual(other);
    }
};

// Диагональная матрица
class DiagonalMatrix : public Matrix {
private:
    int* diag;
public:
    DiagonalMatrix() : Matrix(1,1) {
        diag = new int[1];
        diag[0] = 0;
    }
    DiagonalMatrix(int n) : Matrix(n, n) {
        diag = new int[rows_];
        for (int i = 0; i < rows_; ++i) diag[i] = 0;
    }
    DiagonalMatrix(int n, int init_val) : DiagonalMatrix(n) {
        for (int i = 0; i < rows_; ++i) diag[i] = init_val;
    }
    DiagonalMatrix(const DiagonalMatrix& other) : Matrix(other.rows_, other.cols_) {
        diag = new int[rows_];
        for (int i = 0; i < rows_; ++i) diag[i] = other.diag[i];
    }
    ~DiagonalMatrix() { delete[] diag; }

    void set(int i, int j, int val) { if (i == j) diag[i] = val; }
    int get(int i, int j) const { return (i == j) ? diag[i] : 0; }

    void print() const override {
        std::cout << "DiagonalMatrix " << rows_ << "x" << cols_ << ":\n";
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                if (i == j) std::cout << diag[i] << " ";
                else std::cout << "0 ";
            }
            std::cout << "\n";
        }
    }

    bool isEqual(const Matrix& other) const override {
        const DiagonalMatrix* p = dynamic_cast<const DiagonalMatrix*>(&other);
        if (!p) return false;
        if (rows_ != p->rows_) return false;
        for (int i = 0; i < rows_; ++i)
            if (diag[i] != p->diag[i]) return false;
        return true;
    }

    Matrix* clone() const override {
        return new DiagonalMatrix(*this);
    }

    bool operator==(const DiagonalMatrix& other) const {
        return isEqual(other);
    }
};

// Перегрузка оператора вывода для удобства (не обязательна, но помогает)
inline std::ostream& operator<<(std::ostream& os, const SquareMatrix& m) {
    m.print();
    return os;
}
inline std::ostream& operator<<(std::ostream& os, const DiagonalMatrix& m) {
    m.print();
    return os;
}
// Для int и char – стандартный вывод

// =========================== Пункт c ===========================
void demo_Set_int() {
    std::cout << "\n=== Демонстрация Set<int> ===\n";
    Set<int> A, B;
    A.add(1); A.add(2); A.add(3);
    B.add(2); B.add(3); B.add(4);

    std::cout << "A = "; A.print(); std::cout << "\n";
    std::cout << "B = "; B.print(); std::cout << "\n";

    std::cout << "2 > A? " << (2 > A) << "\n";
    std::cout << "5 > A? " << (5 > A) << "\n";

    Set<int> C = A * B;
    std::cout << "A * B = "; C.print(); std::cout << "\n";

    std::cout << "A < B? " << (A < B) << "\n";
    Set<int> D; D.add(2); D.add(3);
    std::cout << "D < A? " << (D < A) << "\n";
}

void demo_Set_Matrix() {
    std::cout << "\n=== Демонстрация Set<SquareMatrix> ===\n";
    SquareMatrix M1(2), M2(2), M3(2);
    M1.set(0,0,1); M1.set(0,1,2); M1.set(1,0,3); M1.set(1,1,4);
    M2.set(0,0,5); M2.set(0,1,6); M2.set(1,0,7); M2.set(1,1,8);
    M3.set(0,0,1); M3.set(0,1,2); M3.set(1,0,3); M3.set(1,1,4); // M3 == M1

    Set<SquareMatrix> setA, setB;
    setA.add(M1); setA.add(M2);
    setB.add(M2); setB.add(M3);

    std::cout << "setA (квадратные матрицы):\n";
    for (int i = 0; i < setA.getSize(); ++i) setA[i].print();
    std::cout << "setB:\n";
    for (int i = 0; i < setB.getSize(); ++i) setB[i].print();

    std::cout << "M1 > setA? " << (M1 > setA) << "\n";
    std::cout << "M3 > setA? " << (M3 > setA) << "\n";

    Set<SquareMatrix> inter = setA * setB;
    std::cout << "Пересечение setA и setB:\n";
    for (int i = 0; i < inter.getSize(); ++i) inter[i].print();

    Set<SquareMatrix> sub; sub.add(M2);
    std::cout << "sub < setA? " << (sub < setA) << "\n";
}

void demo_Set_char() {
    std::cout << "\n=== Демонстрация Set<char> (символы цифр) ===\n";
    Set<char> digits;
    digits.add('0'); digits.add('1'); digits.add('2'); digits.add('3'); digits.add('4');
    Set<char> evens;
    evens.add('0'); evens.add('2'); evens.add('4'); evens.add('6'); evens.add('8');

    std::cout << "digits = "; digits.print(); std::cout << "\n";
    std::cout << "evens = "; evens.print(); std::cout << "\n";

    std::cout << "'3' > digits? " << ('3' > digits) << "\n";
    std::cout << "'5' > digits? " << ('5' > digits) << "\n";

    Set<char> inter = digits * evens;
    std::cout << "digits * evens = "; inter.print(); std::cout << "\n";

    std::cout << "evens < digits? " << (evens < digits) << "\n";
    Set<char> some; some.add('0'); some.add('2');
    std::cout << "some < evens? " << (some < evens) << "\n";
}

int main() {
    // Пункты a и c
    demo_Set_int();
    demo_Set_Matrix();
    demo_Set_char();

    // Пункт b: статический счётчик
    std::cout << "\n=== Статический счётчик суммарного количества элементов матриц ===\n";
    {
        SquareMatrix sq(3);   // 3x3 = 9
        DiagonalMatrix diag(4); // 4x4 = 16
        std::cout << "После создания sq(3) и diag(4): totalElements = "
                  << Matrix::getTotalElements() << "\n";
        SquareMatrix sq2(2, 5); // 4 элемента
        std::cout << "После добавления sq2(2): totalElements = "
                  << Matrix::getTotalElements() << "\n";
    }
    std::cout << "После выхода из области видимости: totalElements = "
              << Matrix::getTotalElements() << "\n";

    return 0;
}
