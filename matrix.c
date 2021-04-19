/*
 * Autore: Bartocetti Enrico
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void menu(float **matrice, int colonne, int righe);
void stampaMenu();
int trovaRango(float **matriceIniz, int colonne, int righe);
void ordina(float **matrice, int colonne, int righe);
void scambiaRighe(float **matrice, int colonne, int r1, int r2);
void trasforma(float **matrice, int colonne, int r1, int r2, int pivot);
void modificaElemento(float **matrice, int colonne, int righe);
int trovaDeterminante(float **matrice, int colonne, int righe);
float** complementiAlgebrici(float **matrice, int colonne, int righe);
float** matriceTrasposta(float **matrice, int colonne, int righe);
float** matriceInversa(float **matrice, int colonne, int righe);

int main() {
    int colonne, righe;
    int i, j;
    float **matrice; 

    printf("\nInserire il numero di righe della matrice\n> ");
    scanf("%d", &righe);
    while (righe <= 0) {
        printf("ATTENZIONE! NUMERO DI RIGHE INSERITO NON VALIDO\nInserire il numero di righe della matrice\n> ");
        scanf("%d", &righe);
    }

    printf("Inserire il numero di colonne della matrice\n> ");
    scanf("%d", &colonne);
    while (colonne <= 0) {
        printf("ATTENZIONE! NUMERO DI COLONNE INSERITO NON VALIDO\nInserire il numero di colonne della matrice\n> ");
        scanf("%d", &colonne);
    }

    matrice = (float **) malloc(righe * colonne * sizeof(float));

    for (i = 0; i < righe; i++) {
        matrice[i] = (float *) malloc(colonne * sizeof(float));
    }

    printf("\nINSERIMENTO MATRICE\n");

    for (i = 0; i < righe; i++) {
        for(j = 0; j < colonne; j++) {
            printf("Elemento [%d] [%d]: ", i, j);
            scanf("%f",&matrice[i][j]);
        }
    }

    menu(matrice, colonne, righe);

    return 0;
}

void menu(float **matrice, int colonne, int righe) {
    float **inversa, **complementi, **trasposta;
    int scelta, rango, determinante;

    stampaMenu();
    printf("\n> ");
    scanf("%d", &scelta);

    while (scelta != 0) {

        switch (scelta) {
            
            case 1:
                rango = trovaRango(matrice, colonne, righe);
                printf("\nLA MATRICE HA RANGO %d\n", rango);
                break;

            case 2:
                if (colonne == righe) {
                    determinante = trovaDeterminante(matrice, colonne, righe);
                    printf("\nLA MATRICE HA DETERMINANTE %d\n", determinante);
                } else {
                    printf("\nATTENZIONE! IL DETERMINANTE È CALCOLABILE SOLO PER MATRICI QUADRATE\n");
                }
                break;

            case 3:
                if (colonne == righe) {
                    complementi = complementiAlgebrici(matrice, colonne, righe);
                    printf("\nMATRICE DEI COMPLEMENTI\n\n");
                    for (int r = 0; r < righe; r++) {
                        for (int c = 0; c < colonne; c++) {
                            printf("%6.2f ", complementi[r][c]);
                        }
                        printf("\n");
                    }
                } else {
                    printf("\nATTENZIONE! LA MATRICE DEI COMPLEMENTI È CALCOLABILE SOLO PER MATRICI QUADRATE\n");
                }
                break;

            case 4:
                if (colonne == righe) {
                    trasposta = matriceTrasposta(matrice, colonne, righe);
                    printf("\nMATRICE TRASPOSTA\n\n");
                    for (int r = 0; r < righe; r++) {
                        for (int c = 0; c < colonne; c++) {
                            printf("%6.2f ", trasposta[r][c]);
                        }
                        printf("\n");
                    }
                } else {
                    printf("\nATTENZIONE! LA MATRICE TRASPOSTA È CALCOLABILE SOLO PER MATRICI QUADRATE\n");
                }
                break;

            case 5:
                if (colonne == righe) {
                    determinante = trovaDeterminante(matrice, colonne, righe);
                    if (determinante != 0) {
                        inversa = matriceInversa(matrice, colonne, righe);
                        printf("\nMATRICE INVERSA\n\n");
                        for (int r = 0; r < righe; r++) {
                            for (int c = 0; c < colonne; c++) {
                                printf("%6.3f ", inversa[r][c]);
                            }
                            printf("\n");
                        }
                    } else {
                        printf("\nLA MATRICE NON È INVERTIBILE (DETERMINANTE = 0)\n");
                    }
                } else {
                    printf("\nATTENZIONE! LA MATRICE INVERSA È CALCOLABILE SOLO PER MATRICI QUADRATE\n");
                }
                break;

            case 6:
                modificaElemento(matrice, colonne, righe);
                break;

            case 7:
                printf("\n");
                for (int r = 0; r < righe; r++) {
                    for (int c = 0; c < colonne; c++) {
                        printf("%6.2f ", matrice[r][c]);
                    }
                    printf("\n");
                }
                break;

            default:
                printf("Scelta non riconosciuta\n");
                break;
        }

        stampaMenu();
        printf("\n> ");
        scanf("%d", &scelta);
    }
}

void stampaMenu() {
    printf("\n╔═══════════════════════════════╗\n");
    printf("║                               ║\n");
    printf("║       MATRIX CALCULATOR       ║\n");
    printf("║                  by EnryBarto ║\n");
    printf("╚═══════════════════════════════╝\n");
    printf("\n1) Calcolo rango\n");
    printf("2) Calcolo determinante\n");
    printf("3) Complementi algebrici\n");
    printf("4) Matrice trasposta\n");
    printf("5) Matrice inversa\n");
    printf("6) Modifica elemento matrice\n");
    printf("7) Stampa matrice\n");
    printf("0) Uscita\n");
}

int trovaRango(float **matriceIniz, int colonne, int righe) {
    float **matrice;// Matrice copiata
    int rango = 0;  // Rango della matrice
    bool nullo;     // Diventa false quando incontra un pivot
    int i;  // Contatore per le righe
    int j;  // Contatore per le colonne
    int k;  // Contatore per le righe successive a quelle del pivot

    matrice = (float **) malloc(righe * colonne * sizeof(float));

    for (i = 0; i < righe; i++) {
        matrice[i] = (float *) malloc(colonne * sizeof(float));
    }

    for (i = 0; i < righe; i ++) {
        for (j = 0; j < colonne; j++) {
            matrice[i][j] = matriceIniz[i][j];
        }
    }

    ordina(matrice, colonne, righe);

    i = 0;
    j = 0;
    k = 0;

    // Trasforma la matrice a scala
    while ((i < righe) && (j < colonne)) {
        nullo = true;

        // Trova il pivot
        while ((nullo == true) && (j < colonne)) {
            if (matrice[i][j] != 0) {
                nullo = false;
            }
            j++;
        }
        j--;

        // Trasforma le righe con i giusti 0
        for (k = i + 1; k < righe; k++) {
            if (matrice[k][j] != 0) {
                trasforma(matrice, colonne, i, k, j);
            }
        }

        i++;
    }

    i = 0;
    j = 0;

    // Calcola il rango
    while ((i < righe) && (j < colonne)) {

        if (matrice[i][j] != 0) {
            rango++;
            i++;
            j++;
        } else {
            j++;
        }

    }

    return rango;
}

void ordina(float **matrice, int colonne, int righe) {
    bool controllo; // True se non sono state scambiate le righe
    bool zeri;      // True quando il primo elemento è 0
    int i; // Contatore per le righe
    int j; // Contatore per le colonne
    int k; // Posizione pivot

    // Scala la matrice (con gli 0 già presenti)
    for (i = 0; i < righe - 1; i++) {
        controllo = true;
        j = 0;

        // Cerca una riga con elementi nulli da scambiare con la riga di indice i
        while ((controllo == true) && (j < colonne)) {

            // Controlla se nella riga è presente un elemento nullo
            if (matrice[i][j] == 0) {
                zeri = true;
                k = i + 1; // k assume il valore della riga successiva ad i

                // Cerca una riga in cui sono presenti meno elementi nulli della riga i
                while ((zeri == true) && (k < righe)) {

                    if (matrice[k][j] != 0) {
                        zeri = false;
                    }
                    k++;

                }
                k--;

                // Scambia la riga k e la riga i
                if (zeri == false) {
                    scambiaRighe(matrice, colonne, i, k);
                    controllo = false;
                } 
            }
            j++;
        }
    }
}

void scambiaRighe(float **matrice, int colonne, int r1, int r2) {
    float *temp; // Variabile temporanea

    temp = (float *) malloc(colonne * sizeof(float));

    for (int i = 0; i < colonne; i++) {
        temp[i] = matrice[r1][i];
    }

    for (int i = 0; i < colonne; i++) {
        matrice[r1][i] = matrice[r2][i];
    }

    for (int i = 0; i < colonne; i++) {
        matrice[r2][i] = temp[i];
    }
}

void trasforma(float **matrice, int colonne, int r1, int r2, int pivot) {
    float coeff1, coeff2; // Coefficienti per cui moltiplicare le righe

    coeff1 = matrice[r1][pivot];
    coeff2 = matrice[r2][pivot];

    for (int i = 0; i < colonne; i++) {
        matrice[r2][i] = coeff2 * matrice[r1][i] - coeff1 * matrice[r2][i];
    }

}

void modificaElemento(float **matrice, int colonne, int righe) {
    int riga, colonna; // Riga e colonna dell'elemento da modificare

    printf("\nChe elemento si vuole modificare");
    printf("\nRiga > ");
    scanf("%d", &riga);
    while((riga < 0) || (riga >= righe)) {
        printf("RIGA NON VALIDA\nRiga > ");
        scanf("%d", &riga);
    }

    printf("Colonna > ");
    scanf("%d", &colonna);
    while((colonna < 0) || (colonna >= colonne)) {
        printf("COLONNA NON VALIDA\nColonna > ");
        scanf("%d", &colonna);
    }

    printf("\nElemento precedente: %d\nInserire il nuovo elemento\n> ", matrice[riga][colonna]);
    scanf("%d", &matrice[riga][colonna]);

}

int trovaDeterminante(float **matrice, int colonne, int righe) {
    int det = 0, det2 = 0, colonne2, righe2, fattore;
    int i = 0, j = 0, k = 0, l = 0, r = 0, c = 0;
    float **appoggio;

    if (righe == 1) {
        det = matrice[0][0];
    } else {
        colonne2 = colonne - 1;
        righe2 = righe - 1;

        for (c = 0; c < colonne; c++) {
            appoggio = (float **) malloc(righe2 * colonne2 * sizeof(float));

            for (i = 0; i < righe2; i++) {
                appoggio[i] = (float *) malloc(colonne2 * sizeof(float));
            }

            k = 0;
            l = 0;

            for (i = 0; i < righe; i++) {
                for (j = 0; j < colonne; j++) {
                    if ((i != r) && (j != c)) {
                        if (l >= righe2) {
                            l = 0;
                            k++;
                        }
                        appoggio[k][l] = matrice[i][j];

                        l++;
                    }
                }
            }

            if (((r + c) % 2) != 0) {
                fattore = -1;
            } else {
                fattore = 1;
            }

            det2 = trovaDeterminante(appoggio, colonne2, righe2);

            det += matrice[r][c] * fattore * det2;

            free(appoggio);
        }
    }

    return det;   

}

float** complementiAlgebrici(float **matrice, int colonne, int righe) {
    int i = 0, j = 0, k = 0, l = 0, r = 0, c = 0;
    int det = 0, colonne2, righe2, fattore;
    float **complementi, **appoggio;

    complementi = (float **) malloc(righe * colonne * sizeof(float));

    for (i = 0; i < righe; i++) {
        complementi[i] = (float *) malloc(colonne * sizeof(float));
    }

    colonne2 = colonne - 1;
    righe2 = righe - 1;

    for (r = 0; r < righe; r++) {
        for (c = 0; c < colonne; c++) {
            appoggio = (float **) malloc(righe2 * colonne2 * sizeof(float));

            for (i = 0; i < righe2; i++) {
                appoggio[i] = (float *) malloc(colonne2 * sizeof(float));
            }

            k = 0;
            l = 0;

            for (i = 0; i < righe; i++) {
                for (j = 0; j < colonne; j++) {
                    if ((i != r) && (j != c)) {
                        if (l >= righe2) {
                            l = 0;
                            k++;
                        }
                        appoggio[k][l] = matrice[i][j];
                        l++;
                    }
                }
            }

            if (((r + c) % 2) != 0) {
                fattore = -1;
            } else {
                fattore = 1;
            }

            det = trovaDeterminante(appoggio, colonne2, righe2);

            complementi[r][c] = det * fattore;

            free(appoggio);
        }
    }

    return complementi;
}


float** matriceTrasposta(float **matrice, int colonne, int righe) {
    float** trasposta;

    trasposta = (float **) malloc(righe * colonne * sizeof(float));

    for (int i = 0; i < righe; i++) {
        trasposta[i] = (float *) malloc(colonne * sizeof(float));
    }

    for (int r = 0; r < righe; r++) {
        for (int c = 0; c < colonne; c++) {
            trasposta[r][c] = matrice[c][r];
        }
    }

    return trasposta;
}

float** matriceInversa(float **matrice, int colonne, int righe) {
    float **inversa, **temp, **complementi;
    int det;

    inversa = (float **) malloc(righe * colonne * sizeof(float));

    for (int i = 0; i < righe; i++) {
        inversa[i] = (float *) malloc(colonne * sizeof(float));
    }

    complementi = (float **) malloc(righe * colonne * sizeof(float));

    for (int i = 0; i < righe; i++) {
        complementi[i] = (float *) malloc(colonne * sizeof(float));
    }

    complementi = complementiAlgebrici(matrice, colonne, righe);
    det = trovaDeterminante(matrice, colonne, righe);

    temp = inversa;

    for (int r = 0; r < righe; r++) {
        for (int c = 0; c < colonne; c++) {
            inversa[r][c] = (1 / (float) det) * complementi[r][c];
        }
    }

    inversa = (float**) matriceTrasposta(inversa, colonne, righe);

    free(complementi);
    free(temp);

    return inversa;
}
