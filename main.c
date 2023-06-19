#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <sqlite3.h>

#define MAX_BOOKS 100

char bookNames[MAX_BOOKS][100];
int i = 0;

sqlite3 * db;
int bookID;

int callback(void * data, int argc, char ** argv, char ** azColName) {
  for (int i = 0; i < argc; i++) {
    printf("%s: %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

// Fonction pour afficher toutes les données dans la base de données
void showData(sqlite3 * db) {
  char * selectQuery = "SELECT * FROM listedeslivres;";
  char * errMsg = 0;
  int rc = sqlite3_exec(db, selectQuery, callback, 0, & errMsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Erreur lors de la sélection des données : %s\n", errMsg);
    sqlite3_free(errMsg);
  }
}

void getBookNameByID(sqlite3 * db) {
  sqlite3_stmt * stmt;
  char selectQuery[100];
  printf("Enter the book ID: ");
  scanf("%d", & bookID);
  snprintf(selectQuery, sizeof(selectQuery), "SELECT book_name FROM listedeslivres WHERE Id = %d;", bookID);


  int rc = sqlite3_prepare_v2(db, selectQuery, -1, & stmt, NULL);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));
    return;
  }

  while (sqlite3_step(stmt) == SQLITE_ROW && i < MAX_BOOKS) {
    const unsigned char * result = sqlite3_column_text(stmt, 0);
    strcpy(bookNames[i], (const char * ) result);
    i++;
  }
}

void printmylist() {
  for (int i = 0; i < MAX_BOOKS; i++) {
    if (strlen(bookNames[i]) > 0) {
      printf("Livre %d: %s\n", i + 1, bookNames[i]);
    }
  }
}
void saveBookList() {
  FILE * file = fopen("book_list.txt", "w");
  if (file == NULL) {
    fprintf(stderr, "Cannot open file for writing.\n");
    return;
  }

  for (int i = 0; i < MAX_BOOKS; i++) {
    if (strlen(bookNames[i]) > 0) {
      fprintf(file, "%s\n", bookNames[i]);
    }
  }

  fclose(file);
  printf("Book list saved to file.\n");
}
void loadBookList() {
  FILE * file = fopen("book_list.txt", "r");
  if (file == NULL) {
    fprintf(stderr, "Cannot open file for reading.\n");
    return;
  }

  char line[100];
  int i = 0;
  while (fgets(line, sizeof(line), file) != NULL && i < MAX_BOOKS) {
    line[strcspn(line, "\n")] = '\0'; // Supprimer le saut de ligne
    strcpy(bookNames[i], line);
    i++;
  }

  fclose(file);
  printf("Book list loaded from file.\n");
}

int main() {
  int rc = sqlite3_open("listedeslivres.db", & db);
  if (rc) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return 1;
  }
  loadBookList();
  while (1) {
    char commande[20];
    printf("Enter a command ('show', 'id', 'liste', or 'close'): ");
    scanf("%s", commande);

    if (strcmp(commande, "show") == 0) {
      showData(db);
    } else if (strcmp(commande, "id") == 0) {
      getBookNameByID(db);
      saveBookList();
    } else if (strcmp(commande, "liste") == 0) {
      printmylist();
    } else if (strcmp(commande, "close") == 0) {
      break;
    } else {
      printf("Invalid command. Please try again.\n");
    }
  }

  sqlite3_close(db);
  printf("Database connection closed.\n");

  return 0;
}
