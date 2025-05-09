#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

void inputMatrix(vector<vector<int>>& matrix, int& rows, int& cols, bool randomize) {
    cout << "Enter number of rows and columns: ";
    cin >> rows >> cols;

    matrix.clear();
    for (int i = 0; i < rows; ++i) {
        vector<int> row;
        for (int j = 0; j < cols; ++j) {
            int value;
            if (randomize) {
                value = rand() % 10;
            }
            else {
                cout << "Element [" << i << "][" << j << "]: ";
                cin >> value;
            }
            row.push_back(value);
        }
        matrix.push_back(row);
    }
}

bool readMatrixFromFile(vector<vector<int>>& matrix, int& rows, int& cols, const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Failed to open file: " << filename << endl;
        return false;
    }

    fin >> rows >> cols;
    cout << "Rows: " << rows << ", Cols: " << cols << endl; 
    matrix.clear();

    for (int i = 0; i < rows; ++i) {
        vector<int> row;
        for (int j = 0; j < cols; ++j) {
            int value;
            fin >> value;
            cout << "Reading [" << i << "][" << j << "]: " << value << endl;
            row.push_back(value);
        }
        matrix.push_back(row);
    }

    fin.close();
    return true;
}

void displayMatrix(const vector<vector<int>>& matrix) {
    cout << "\nMatrix:\n";
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void toCSR(const vector<vector<int>>& matrix, vector<int>& val, vector<int>& colIdx, vector<int>& rowPtr) {
    val.clear();
    colIdx.clear();
    rowPtr.clear();
    rowPtr.push_back(0);  

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j] != 0) {
                val.push_back(matrix[i][j]);
                colIdx.push_back(j);
            }
        }
        rowPtr.push_back(val.size());
    }
}

void subtractFromDiagonal(vector<int>& val, vector<int>& colIdx, vector<int>& rowPtr, int scalar, int rows) {
    for (int i = 0; i < rows; ++i) {
        bool found = false;
        int start = rowPtr[i];
        int end = rowPtr[i + 1];

        for (int j = start; j < end; ++j) {
            if (colIdx[j] == i) { 
                val[j] -= scalar;
                found = true;

              
                if (val[j] == 0) {
                    val.erase(val.begin() + j);
                    colIdx.erase(colIdx.begin() + j);

                  
                    for (int k = i + 1; k < rowPtr.size(); ++k) {
                        rowPtr[k]--;
                    }
                }
                break;
            }
        }

       
        if (!found && scalar != 0) {
            val.insert(val.begin() + end, -scalar);
            colIdx.insert(colIdx.begin() + end, i);
            for (int k = i + 1; k < rowPtr.size(); ++k) {
                rowPtr[k]++;
            }
        }
    }
}

void fromCSR(vector<vector<int>>& matrix, const vector<int>& val, const vector<int>& colIdx, const vector<int>& rowPtr) {
    int rows = rowPtr.size() - 1;
    int cols = rows;

    matrix.clear();
    for (int i = 0; i < rows; ++i) {
        vector<int> row(cols, 0);  
        matrix.push_back(row);
    }

    for (int i = 0; i < rows; ++i) {
        int start = rowPtr[i];
        int end = rowPtr[i + 1];
        for (int j = start; j < end; ++j) {
            int col = colIdx[j];
            matrix[i][col] = val[j];
        }
    }
}

void printCSR(const vector<int>& val, const vector<int>& colIdx, const vector<int>& rowPtr) {
    cout << "\nval: ";
    for (int i = 0; i < val.size(); ++i)
        cout << val[i] << " ";

    cout << "\ncolIdx: ";
    for (int i = 0; i < colIdx.size(); ++i)
        cout << colIdx[i] << " ";

    cout << "\nrowPtr: ";
    for (int i = 0; i < rowPtr.size(); ++i)
        cout << rowPtr[i] << " ";

    cout << endl;
}

int main() {
    srand(time(0));

    vector<vector<int>> matrix;
    vector<int> val, colIdx, rowPtr;
    int rows = 0, cols = 0;

    cout << "Choose input mode:\n1 - Random\n2 - Manual\n3 - From file\nYour choice: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        inputMatrix(matrix, rows, cols, true);
    }
    else if (choice == 2) {
        inputMatrix(matrix, rows, cols, false);
    }
    else if (choice == 3) {
        string filename;
        cout << "Enter filename (e.g. matrix.txt): ";
        cin >> filename;
        if (!readMatrixFromFile(matrix, rows, cols, filename)) {
            cout << "Reading from file failed. Exiting.\n";
            return 1;
        }
    }
    else {
        cout << "Invalid choice. Exiting.\n";
        return 1;
    }

    cout << "\nOriginal Matrix:\n";
    displayMatrix(matrix);

    
    toCSR(matrix, val, colIdx, rowPtr);

    
    printCSR(val, colIdx, rowPtr);

    int scalar;
    cout << "\nEnter number to subtract from diagonal: ";
    cin >> scalar;

    
    subtractFromDiagonal(val, colIdx, rowPtr, scalar, rows);

    
    fromCSR(matrix, val, colIdx, rowPtr);

    cout << "\nMatrix after diagonal subtraction:\n";
    displayMatrix(matrix);

    printCSR(val, colIdx, rowPtr);

    return 0;
}
