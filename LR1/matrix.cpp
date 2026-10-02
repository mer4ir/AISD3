#include "matrix.h"
#include <iostream>
#include <complex>

using namespace std;

int main()
{
    try
    {
        cout << " Integer Matrices " << "\n";
        Matrix<int> intA(2, 2, 1);
        Matrix<int> intB(2, 2, 2);

        intA(0, 0) = 1;
        intA(0, 1) = 2;
        intA(1, 0) = 3;
        intA(1, 1) = 4;

        intB(0, 0) = 5;
        intB(0, 1) = 6;
        intB(1, 0) = 7;
        intB(1, 1) = 8;

        cout << "Matrix A:\n"
             << intA << "\n\n";
        cout << "Matrix B:\n"
             << intB << "\n\n";
        intA = intA;
        cout << "Matrix A after self-assignment:\n";
        cout << intA << "\n\n";
        cout << "A + B:\n"
             << (intA + intB) << "\n\n";
        cout << "A * B:\n"
             << (intA * intB) << "\n\n";
        cout << "A * 3:\n"
             << (intA * 3) << "\n\n";
        cout << "Trace of A: " << intA.trace() << "\n\n";

        cout << " Double Matrices " << "\n";
        Matrix<double> doubleA(3, 3, 1.5);
        Matrix<double> doubleB(3, 3, 2.5);

        cout << "Double Matrix A:\n"
             << doubleA << "\n\n";
        cout << "Double Matrix B:\n"
             << doubleB << "\n\n";
        cout << "A - B:\n"
             << (doubleA - doubleB) << "\n\n";
        cout << "A / 2.0:\n"
             << (doubleA / 2.0) << "\n\n";

        cout << " Float Matrices " << "\n";
        Matrix<float> floatA(3, 3, 3.52);
        Matrix<float> floatB(3, 3, 4.3);

        cout << "Float Matrix A:\n"
             << floatA << "\n\n";
        cout << "Float Matrix B:\n"
             << floatB << "\n\n";
        cout << "A - B:\n"
             << (floatA - floatB) << "\n\n";
        cout << "A / 2.0:\n"
             << (doubleA / 2.0) << "\n\n";

        cout << " Random Matrices " << "\n";
        Matrix<int> randomInt(2, 2, 1, 10);
        Matrix<double> randomDouble(2, 2, 0.0, 1.0);
        Matrix<float> randomFloat(2, 2, 0.0, 2.0);
        Matrix<complex<double>> randomComplex(2, 2, complex<double>(1.0, 1.0), complex<double>(5.0, 5.0));
        cout << "Random complex double matrix:\n"
             << randomComplex << "\n\n";

        cout << "Random integer matrix:\n"
             << randomInt << "\n\n";
        cout << "Random double matrix:\n"
             << randomDouble << "\n\n";
        cout << "Random Float matrix:\n"
             << randomFloat << "\n\n";

        cout << " Complex Matrices " << "\n";
        Matrix<complex<double>> complexA(2, 2, complex<double>(1.0, 0.0));
        Matrix<complex<double>> complexB(2, 2, complex<double>(0.0, 1.0));

        complexA(0, 0) = complex<double>(1, 2);
        complexA(0, 1) = complex<double>(3, 4);
        complexA(1, 0) = complex<double>(5, 6);
        complexA(1, 1) = complex<double>(7, 8);

        cout << "Complex Matrix A:\n"
             << complexA << "\n\n";
        cout << "Complex Matrix B:\n"
             << complexB << "\n\n";
        cout << "A + B:\n"
             << (complexA + complexB) << "\n\n";
        cout << "A * (2.0 + 1.0i):\n"
             << (complexA * complex<double>(2.0, 1.0)) << "\n\n";

        cout << " Inverse Matrix Calculation " << "\n";
        Matrix<double> mat3x3(3, 3);

        mat3x3(0, 0) = 2;
        mat3x3(0, 1) = -1;
        mat3x3(0, 2) = 0;
        mat3x3(1, 0) = -1;
        mat3x3(1, 1) = 2;
        mat3x3(1, 2) = -1;
        mat3x3(2, 0) = 0;
        mat3x3(2, 1) = -1;
        mat3x3(2, 2) = 2;

        Matrix<double> inverse1(3, 3, 1, 10);
        cout << inverse1 << "\n\n";
        Matrix<double> inverse2 = inverse3x3(inverse1);
        cout << inverse2 << "\n\n";
        cout << inverse1 * inverse2 << "\n\n";

        cout << "Original 3x3 matrix:\n"
             << mat3x3 << "\n\n";

        Matrix<double> inverseMat = inverse3x3(mat3x3);
        cout << "Inverse matrix:\n"
             << inverseMat << "\n\n";

        Matrix<double> identityCheck = mat3x3 * inverseMat;
        cout << "A * A^(-1) (should be identity):\n"
             << identityCheck << "\n\n";

        cout << " Comparison Operators " << "\n";
        Matrix<int> mat1(2, 2, 1);
        Matrix<int> mat2(2, 2, 1);

        cout << "mat1 == mat2: " << (mat1 == mat2 ? "true" : "false") << "\n";
        cout << "mat1 != mat2: " << (mat1 != mat2 ? "true" : "false") << "\n";

        cout << "complexA == complexB: " << (complexA == complexB ? "true" : "false") << "\n";
        cout << "complexA != complexB: " << (complexA != complexB ? "true" : "false") << "\n";
    }
    catch (const exception &e)
    {
        cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}