/*
a) Разработайте абстрактный тип данных множество set. Дополнительно
перегрузить следующие операции:
> проверка на принадлежность (типа операции in множественного типа);
*  пересечение множеств;
<  проверка на подмножество
b) Разработайте иерархию классов матричные структуры (приватные
члены сконструировать самостоятельно). Добавьте статические члены по
подсчету суммарного количества элементов. Разработайте не менее 2-х
виртуальных функций.
c) Создайте шаблонный класс множества матриц различных видов,
множества символов чисел. Продемонстрируйте работу класса и все его
операции. 
*/


#include <iostream>
#include <cstring>

using namespace std;

template<typename T>
class Set {
private:
    T** data;
    int size;
    int capacity;

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

    void add(const T& elem) {
        if (contains(elem)) return;
        if (size == capacity) {
            int new_cap = (capacity == 0) ? 4 : capacity * 2;
            resize(new_cap);
        }
        data[size++] = new T(elem);
    }

    bool contains(const T& elem) const {
        for (int i = 0; i < size; ++i)
            if (*data[i] == elem)
                return true;
        return false;
    }

    int getSize() const { return size; }

    const T& operator[](int index) const { return *data[index]; }

    friend bool operator>(const T& elem, const Set<T>& set) {
        return set.contains(elem);
    }
    
    friend Set<T> operator*(const Set<T>& a, const Set<T>& b) {
        Set<T> result;
        for (int i = 0; i < a.size; ++i) {
            if (b.contains(*a.data[i]))
                result.add(*a.data[i]);
        }
        return result;
    }

    friend bool operator<(const Set<T>& a, const Set<T>& b) {
        for (int i = 0; i < a.size; ++i)
            if (!b.contains(*a.data[i]))
                return false;
        return true;
    }

    void print() const {
        cout << "{ ";
        for (int i = 0; i < size; ++i) {
            cout << *data[i] << (i == size-1 ? " " : ", ");
        }
        cout << "}";
    }
};

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

    virtual void print() const = 0;
    virtual bool isEqual(const Matrix& other) const = 0;
    virtual Matrix* clone() const = 0;

    int rows() const { return rows_; }
    int cols() const { return cols_; }
};
int Matrix::totalElements = 0;

class SquareMatrix : public Matrix {
private:
    int** data;
public:

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
        cout << "SquareMatrix " << rows_ << "x" << cols_ << ":\n";
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j)
                cout << data[i][j] << " ";
            cout << "\n";
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

    bool operator==(const SquareMatrix& other) const {
        return isEqual(other);
    }
};

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
        cout << "DiagonalMatrix " << rows_ << "x" << cols_ << ":\n";
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                if (i == j) cout << diag[i] << " ";
                else cout << "0 ";
            }
            cout << "\n";
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

ostream& operator<<(ostream& os, const SquareMatrix& m) {
    m.print();
    return os;
}
ostream& operator<<(ostream& os, const DiagonalMatrix& m) {
    m.print();
    return os;
}

void demo_Set_int() {
    cout << "\nДемонстрация Set<int>\n";
    Set<int> A, B;
    A.add(1); A.add(2); A.add(3);
    B.add(2); B.add(3); B.add(4);

    cout << "A = "; A.print(); cout << "\n";
    cout << "B = "; B.print(); cout << "\n";

    cout << "2 > A? " << (2 > A) << "\n";
    cout << "5 > A? " << (5 > A) << "\n";

    Set<int> C = A * B;
    cout << "A * B = "; C.print(); cout << "\n";

    cout << "A < B? " << (A < B) << "\n";
    Set<int> D; D.add(2); D.add(3);
    cout << "D < A? " << (D < A) << "\n";
}

void demo_Set_Matrix() {
    cout << "\nДемонстрация Set<SquareMatrix>\n";
    SquareMatrix M1(2), M2(2), M3(2);
    M1.set(0,0,1); M1.set(0,1,2); M1.set(1,0,3); M1.set(1,1,4);
    M2.set(0,0,5); M2.set(0,1,6); M2.set(1,0,7); M2.set(1,1,8);
    M3.set(0,0,1); M3.set(0,1,2); M3.set(1,0,3); M3.set(1,1,4);

    Set<SquareMatrix> setA, setB;
    setA.add(M1); setA.add(M2);
    setB.add(M2); setB.add(M3);

    cout << "setA (квадратные матрицы):\n";
    for (int i = 0; i < setA.getSize(); ++i) setA[i].print();
    cout << "setB:\n";
    for (int i = 0; i < setB.getSize(); ++i) setB[i].print();

    cout << "M1 > setA? " << (M1 > setA) << "\n";
    cout << "M3 > setA? " << (M3 > setA) << "\n";

    Set<SquareMatrix> inter = setA * setB;
    cout << "Пересечение setA и setB:\n";
    for (int i = 0; i < inter.getSize(); ++i) inter[i].print();

    Set<SquareMatrix> sub; sub.add(M2);
    cout << "sub < setA? " << (sub < setA) << "\n";
}

void demo_Set_char() {
    cout << "\nДемонстрация Set<char> (символы цифр)\n";
    Set<char> digits;
    digits.add('0'); digits.add('1'); digits.add('2'); digits.add('3'); digits.add('4');
    Set<char> evens;
    evens.add('0'); evens.add('2'); evens.add('4'); evens.add('6'); evens.add('8');

    cout << "digits = "; digits.print(); cout << "\n";
    cout << "evens = "; evens.print(); cout << "\n";

    cout << "'3' > digits? " << ('3' > digits) << "\n";
    cout << "'5' > digits? " << ('5' > digits) << "\n";

    Set<char> inter = digits * evens;
    cout << "digits * evens = "; inter.print(); cout << "\n";

    cout << "evens < digits? " << (evens < digits) << "\n";
    Set<char> some; some.add('0'); some.add('2');
    cout << "some < evens? " << (some < evens) << "\n";
}

int main() {
    demo_Set_int();
    demo_Set_Matrix();
    demo_Set_char();
 
    cout << "\nСтатический счётчик суммарного количества элементов матриц\n";
    {
        SquareMatrix sq(3);
        DiagonalMatrix diag(4);
        cout << "После создания sq(3) и diag(4): totalElements = "
             << Matrix::getTotalElements() << "\n";
        SquareMatrix sq2(2);
        cout << "После добавления sq2(2): totalElements = "
             << Matrix::getTotalElements() << "\n";
    }
    cout << "После выхода из области видимости: totalElements = "
         << Matrix::getTotalElements() << "\n";

    return 0;
}
