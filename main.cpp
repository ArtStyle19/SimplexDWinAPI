#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"

#include <limits>

HINSTANCE hInst;

#include <iostream>

using namespace std;



#include <vector>


#define IDC_FIRST_BUTTON 1000
#define IDC_FIRST_EDIT   2000
#define BUTTON_WIDTH     107
#define BUTTON_HEIGHT    30
#define EDIT_WIDTH       107
#define EDIT_HEIGHT      20
#define BUTTON_GAP       10
#define EDIT_GAP         10

vector<HWND> buttonHandles;
vector<HWND> editHandles;
vector<int> editValues;


void printTableau(double** tableau, int M, int N) {
    for (int i = 0; i < M + 1; ++i) {
        for (int j = 0; j < N + M + 1; ++j) {
            // Imprimir el valor con un ancho fijo
            cout << " " << tableau[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void simplex(double** tableau, int M, int N) {
    int row = M + 1;
    int col = N + M + 1;

    while (true) {
        // Encontrar la columna pivote (la más negativa en la fila objetivo)
        int pivotCol = -1;
        double minVal = 0;
        for (int j = 0; j < col - 1; ++j) {
            if (tableau[row - 1][j] < minVal) {
                minVal = tableau[row - 1][j];
                pivotCol = j;
            }
        }

        if (pivotCol == -1) break; // Todos los valores en la fila objetivo son no negativos

        // Encontrar la fila pivote usando la regla de razón mínima
        int pivotRow = -1;
        double minRatio = 1.0e30; // Usar un valor muy grande como infinito
        for (int i = 0; i < row - 1; ++i) {
            if (tableau[i][pivotCol] > 0) {
                double ratio = tableau[i][col - 1] / tableau[i][pivotCol];
                if (ratio < minRatio) {
                    minRatio = ratio;
                    pivotRow = i;
                }
            }
        }

        if (pivotRow == -1) {
            cout << "Problema sin solución acotada" << endl;
            return;
        }

        // Hacer la fila pivote igual a 1 en el pivote
        double pivot = tableau[pivotRow][pivotCol];
        for (int j = 0; j < col; ++j) {
            tableau[pivotRow][j] /= pivot;
        }

        // Hacer ceros en la columna pivote
        for (int i = 0; i < row; ++i) {
            if (i != pivotRow) {
                double factor = tableau[i][pivotCol];
                for (int j = 0; j < col; ++j) {
                    tableau[i][j] -= factor * tableau[pivotRow][j];
                }
            }
        }

        printTableau(tableau, M, N); // Imprimir el tableau en cada iteración
    }

    cout << "Solución Óptima: " << tableau[row - 1][col - 1] << endl;
}







           int M = 3; // Número de restricciones
    int N = 3; // Número de variables
    int NUM_CONTROLS =  (M + N+1); // Cambiar según el número deseado de controles



BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
    {




//    vector<vector<double>> tableau = {
//        {-2, 3, 1, 0, 0, 6},
//        {1, 2, 0, 1, 0, 8},
//        {1, 1, 0, 0, 1, 6},
//        {-1, -2, 0, 0, 0, 0}
//    };


    // tabla ejemplo examen plan b;

//        {2, 1, 1, 0, 6},
//        {1, -1, 0, 1, 0},
//        {-5, -1, 0, 0, 0}





    }
    return TRUE;

    case WM_CLOSE:
    {
        EndDialog(hwndDlg, 0);
    }
    return TRUE;
case WM_CREATE: {


        return TRUE;
    }
    return TRUE;
    case WM_COMMAND:
    {
        switch(LOWORD(wParam))
        {
        case BUTTON1:
            int xxas =0 , yyas=0;


            M =GetDlgItemInt(hwndDlg,NVARIABLES, 0, FALSE);
            N =GetDlgItemInt(hwndDlg,NRESTRICCIONES, 0, FALSE);
//            int mas =GetDlgItemInt(hwndDlg,NRESTRICCIONES, 0, FALSE);
            double mad = 1;
            NUM_CONTROLS =  (M+1) * (N+4);

            int numControls = NUM_CONTROLS;

        int numRows = M + 1;
        int numCols = N + M + 1;


        editValues.clear();
        editHandles.clear();


        // Create edit controls in rows and columns
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                HWND edit = CreateWindow(
                "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | WS_TABSTOP,
                120 + (EDIT_WIDTH + EDIT_GAP) * j, 120 + (EDIT_HEIGHT + EDIT_GAP) * i,
                EDIT_WIDTH, EDIT_HEIGHT, hwndDlg, (HMENU)(IDC_FIRST_EDIT + i * numCols + j),
                NULL, NULL
            );
                editHandles.push_back(edit);
            }
        }

                double** tableau = new double*[M + 1];
                for (int i = 0; i < M + 1; ++i)
                {
                    tableau[i] = new double[N + M + 1];
                }



                for (int i = 0; i < NUM_CONTROLS; ++i)
                {
                    int value = GetDlgItemInt(hwndDlg, IDC_FIRST_EDIT + i, NULL, TRUE);
                    editValues.push_back(value);
                }

//                for (int i = 0; i < editValues.size(); ++i)
//                {
//                    wprintf(L"Value %d: %d\n", i + 1, editValues[i]);
//                }


                // Inicializar el tableau
//                double initialTableau[M + 1][N + M + 1] = {
//                    {1, 2, 3, 1, 0, 0, 30},
//                    {2, 2, 5, 0, 1, 0, 24},
//                    {4, 1, 2, 0, 0, 1, 36},
//                    {-3, -2, -1, 0, 0, 0, 0}
//                };







                for (int i = 0; i < M + 1; ++i)
                {
                    for (int j = 0; j < N + M + 1; ++j)
                    {
                        tableau[i][j] = editValues[j + (M+N+1)*i];
                    }
                }

                cout << "Tabla Inicial: " << endl;
                printTableau(tableau, M, N);

                simplex(tableau, M, N);

                // Liberar la memoria
                for (int i = 0; i < M + 1; ++i)
                {
                    delete[] tableau[i];
                }
                delete[] tableau;

            InvalidateRect(hwndDlg,NULL,true);

            return TRUE;


        }


    }
    return TRUE;
    }
    return FALSE;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst=hInstance;
    InitCommonControls();
    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}
