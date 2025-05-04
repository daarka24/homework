#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

void readMatrix(int& n, vector<vector<int>>& matrix, bool fromFile) {
    if (fromFile) {
        ifstream fin("file.txt");
        if (!fin) {
            cout << "Failed to open file!\n";
            exit(1);  
        }
        fin >> n;
        matrix.resize(n, vector<int>(n));  
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                fin >> matrix[i][j];
        fin.close();
    }
    else {
        cout << "Enter the size of the matrix (n x n): ";
        cin >> n;
        matrix.resize(n, vector<int>(n)); 
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                cout << "A[" << i << "][" << j << "] = ";
                cin >> matrix[i][j];
            }
    }
}
void buildCompressed(const vector<vector<int>>& matrix,
    vector<int>& val, vector<int>& pos, vector<int>& ptr) {
    int n = matrix.size();
    ptr.push_back(0);  

    for (int i = 0; i < n; ++i) {
        int count = 0;

        
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] != 0) {
                val.push_back(matrix[i][j]);
                pos.push_back(j);
                count++;
            }
        }

        ptr.push_back(ptr.back() + count); 
    }
}

void subtractDiagonal(int n, int k, vector<int>& val, vector<int>& pos, vector<int>& ptr) {
    vector<int> newVal, newPos, newPtr;
    newPtr.push_back(0);

    for (int i = 0; i < n; ++i) {
        int count = 0;
        bool diagFound = false;

        for (int j = ptr[i]; j < ptr[i + 1]; ++j) {
            int col = pos[j];
            int value = val[j];

            if (col == i) {
                value -= k;
                diagFound = true;
            }

            if (value != 0) {
                newVal.push_back(value);
                newPos.push_back(col);
                count++;
            }
        }

        
        if (!diagFound && k != 0) {
            newVal.push_back(-k);
            newPos.push_back(i);
            count++;
        }

        newPtr.push_back(newPtr.back() + count);
    }

    
    val = newVal;
    pos = newPos;
    ptr = newPtr;
}



vector<vector<int>> decompressMatrix(int n, const vector<int>& val, const vector<int>& pos, const vector<int>& ptr) {
    vector<vector<int>> matrix(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = ptr[i]; j < ptr[i + 1]; ++j) {
            matrix[i][pos[j]] = val[j]; 
        }
    }

    return matrix;
}


void printMatrix(const vector<vector<int>>& matrix) {
    cout << "\nModified matrix:\n";
    for (const auto& row : matrix) {
        for (int x : row) cout << x << "\t";
        cout << endl;
    }
}


int main() {
    int n;
    vector<vector<int>> matrix;

    
    bool fromFile = true; 
    readMatrix(n, matrix, fromFile);

    
    vector<int> val, pos, ptr;
    buildCompressed(matrix, val, pos, ptr);

    
    int k;
    cout << "Enter the value of k: ";
    cin >> k;
    subtractDiagonal(n, k, val, pos, ptr);

    
    vector<vector<int>> modifiedMatrix = decompressMatrix(n, val, pos, ptr);

   
    printMatrix(modifiedMatrix);

    cout << "\nPtr array: ";
    for (int p : ptr) {
        cout << p << " ";
    }
    cout << endl;
    cout << "\nPos array: ";
    for (int p : pos) {
        cout << p << " ";
    }
    cout << endl;
    cout << "\nVal array: ";
    for (int p : val) {
        cout << p << " ";
    }
    cout << endl;

    return 0;
}
 
