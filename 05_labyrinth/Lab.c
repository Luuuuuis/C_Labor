#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXCOLS 256
#define MAXROWS 256

typedef struct labyrinth {
    char lab[MAXCOLS + 2][MAXROWS];
    long costs[MAXCOLS][MAXROWS];
    int maxrow;
    int startx;
    int starty;
    int treasurex;
    int treasurey;
} LabCell, *Lab_p;

void readLabyrinthFromFile(const char *filename, Lab_p labyrinth) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Fehler beim Öffnen der Datei.\n");
        return;
    }

    char line[MAXCOLS + 2];
    int row = 0;

    while (fgets(line, sizeof(line), file)) {
        if (row >= MAXROWS) {
            printf("Maximale Anzahl von Zeilen überschritten.\n");
            break;
        }

        line[strcspn(line, "\n")] = '\0'; // Entferne Zeilenumbruch

        if (strlen(line) > MAXCOLS) {
            printf("Maximale Anzahl von Spalten überschritten in Zeile %d.\n", row);
            break;
        }

        strncpy(labyrinth->lab[row], line, MAXCOLS);

        // Suche Startposition
        char *startPos = strchr(line, 'S');
        if (startPos != NULL) {
            labyrinth->startx = (int) (startPos - line);
            labyrinth->starty = row;
        }

        // Suche Schatzposition
        char *treasurePos = strchr(line, 'X');
        if (treasurePos != NULL) {
            labyrinth->treasurex = (int) (treasurePos - line);
            labyrinth->treasurey = row;
        }

        row++;
    }

    labyrinth->maxrow = row;

    fclose(file);
}

void printLabyrinth(const LabCell *labyrinth) {
    for (int row = 0; row < labyrinth->maxrow; row++) {
        printf("%s\n", labyrinth->lab[row]);
    }
}

void clearConsole() {
    system("cls"); // Für Windows
}

bool findPath(Lab_p labyrinth, int x, int y) {
    char currentCell = labyrinth->lab[y][x];

    if (currentCell == '#')
        return false; // Hindernis, kein Weg möglich

    if (currentCell == 'X')
        return true; // Ziel erreicht yay

    if (currentCell == '.')
        return false; // bereits besucht

    labyrinth->lab[y][x] = '.'; // schon da gewesen

    clearConsole();
    printf("Aktueller Pfad:\n");
    printLabyrinth(labyrinth);
    printf("\n");

    // Suche in alle Richtungen
    if (findPath(labyrinth, x + 1, y) || // rechts
        findPath(labyrinth, x - 1, y) || // links
        findPath(labyrinth, x, y + 1) || // oben
        findPath(labyrinth, x, y - 1))   // unten
        return true;

//    labyrinth->lab[y][x] = ' '; // entferne Markierung

    return false; // kein Weg gefunden
}

int main() {
    LabCell labyrinth;
    const char *filename = "C:\\Users\\LUIBROS\\Uni\\2. Semester\\Labor\\05_labyrinth\\LABS\\testlabtheseus.txt";

    readLabyrinthFromFile(filename, &labyrinth);

    // Testausgabe
    printf("Maxrow: %d\n", labyrinth.maxrow);
    printf("Startposition: (%d, %d)\n", labyrinth.startx, labyrinth.starty);
    printf("Schatzposition: (%d, %d)\n", labyrinth.treasurex, labyrinth.treasurey);


    printLabyrinth(&labyrinth);

    printf("Suche: \n");

    // Weg finden
    bool pathFound = findPath(&labyrinth, labyrinth.startx, labyrinth.starty);

    // Labyrinth nach der Suche ausgeben
    printf("\nLabyrinth nach der Suche:\n");
    printLabyrinth(&labyrinth);

    if (pathFound) {
        printf("\nEin Weg zum Ziel wurde gefunden.\n");
    } else {
        printf("\nEs wurde kein Weg zum Ziel gefunden.\n");
    }


    return 0;
}
