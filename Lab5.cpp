
#include <iostream>
#include <vector>

using namespace std;

//2    0  33  -1 -21
//78    7  -4   -3  11
// -2  -7  -1   -9    0
//13  61  60  42 -10
//  1    0   4    0   16


void merge(int merged[], int lenD, int L[], int lenL, int R[], int lenR)  //сортування
{

    int i = 0;
    int j = 0;


    while (i < lenL || j < lenR) 
    {
        if (i < lenL & j < lenR) {
            if (L[i] <= R[j]) {
                merged[i + j] = L[i];
                i++;
            }
            else {
                merged[i + j] = R[j];
                j++;
            }
        }
        else if (i < lenL) {
            merged[i + j] = L[i];
            i++;
        }
        else if (j < lenR) {
            merged[i + j] = R[j];
            j++;
        }
    }
}


void mergeSort(int data[], int lenD) {

    if (lenD > 1) {
        int middle = lenD / 2;
        int rem = lenD - middle;
        int* L = new int[middle];
        int* R = new int[rem];
        for (int i = 0; i < lenD; i++) {

            if (i < middle) {
                L[i] = data[i];
            }
            else {
                R[i - middle] = data[i];
            }
        }
        mergeSort(L, middle);
        mergeSort(R, rem);
        merge(data, lenD, L, middle, R, rem);
    }
}


class arr1dХ { //клас одновимірного масиву
private:

    int* data;
    int size;

public:

    arr1dХ(int n)
    {
        data = new int[n];
        size = n;
    };

    ~arr1dХ()
    {
        delete[] data;
        cout << "decstruct" << endl;
    };

    int getSize() // достаєм рощмір масиву
    {
        return size;
    }

    int getData(int i) //достає елемент з масиву
    {
        if (i > size - 1 || i < 0) {
            cout << "Out of range!";

            return 0;
        };
        return data[i];
    }

    void setData(int i, int dat)//встановлюємо і-тий елемент масиву
    {
        if (i > size - 1 || i < 0) {
            cout << "Out of range!";
            return;
        };
        data[i] = dat;
    }

    friend void calculate(); //дстає всі елементи з класу
};

int sum(arr1dХ* row) // рахує суму масиву
{
    int sum = 0;
    for (int i = 0; i < row->getSize(); i++)
        sum = sum + row->getData(i);

    return sum;
}

float geometricMean(arr1dХ* row) //рахує середнє геометричне
{
    int prod = 1;
    int N = row->getSize();
    for (int i = 0; i < N; i++)
        prod = prod * row->getData(i);

    float res = pow(prod, 1.0 / N);
    return res;
}

class Matrix
{
public:
    Matrix(int N);

    ~Matrix();

    int getItem(int i, int j)//дістати елемент матриці ітий йотий
    {
        arr1dХ* row = matr[i];
        int d = row->getData(j);
        return d;
    };

    int getSize() //повертає розмір
    {
        return size;
    };

    void setItem(int i, int j, int data)//встановлює елементи за координатами
    {
        arr1dХ* row = matr[i];
        row->setData(j, data);
    };

private:
    vector<arr1dХ*> matr;
    int size;

};

Matrix::Matrix(int N)// конструктор
{
    for (int i = 0; i < N; i++)
    {
        arr1dХ* row = new arr1dХ(N);
        for (int j = 0; j < N; j++)
        {
            row->setData(j, 0);
        }
        matr.push_back(row);
    }
    size = N;
}

Matrix::~Matrix()
{
}



void printMatrix(Matrix matr)  //друк матриці у вигляді таблиці
{
    int N = matr.getSize();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
        {
            cout << matr.getItem(i, j) << " ";
        }
        cout << endl;
    }
}

void inputMatrix(Matrix& mat)//ввід матриці з клаавіатури
{
    int N = mat.getSize();
    for (int i = 0; i < N; i++)
    {
        cout << " Row " << i << ": ";
        for (int j = 0; j < N; j++)
        {
            int t;
            cin >> t;
            mat.setItem(i, j, t);

        }
    }
    cout << endl;
}
void calculate()
{
    int N;
    cout << "Input size of  matrix N = ";
    cin >> N;
    cout << endl;

    Matrix matr(N);
    Matrix matrOut(N);

    //initMatrix(matr);
    inputMatrix(matr);
    printMatrix(matr);
    cout << endl;
    cout << "--------------------------" << endl << endl;

    
        arr1dХ* col = new arr1dХ(N);
    arr1dХ* row = new arr1dХ(N);

    int d;
    for (int j = 0; j < N; j++)
    {
        for (int i = 0; i < N; i++)
        {
            d = matr.getItem(i, j);
            col->setData(i, d);
        }

        mergeSort(col->data, col->size);

        for (int i = 0; i < N; i++)
        {
            d = col->getData(i);
            matrOut.setItem(i, j, d);
        }

    }


    printMatrix(matrOut);
    int sumOut;
    arr1dХ* colSums = new arr1dХ(N);


    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            d = matrOut.getItem(i, j);
            row->setData(j, d);
        }
        sumOut = sum(row);
        colSums->setData(i, sumOut);
        cout << "Sum of element in " << i << " row is " << sumOut << endl;
    }

    cout << endl << "Geometric mean: " << geometricMean(colSums) << endl << endl;


}

int main() {
    calculate();
    return 0;
}
