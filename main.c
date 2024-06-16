//* Libraries
#include <stdio.h>  //* Standard in and out
#include <ctype.h>  //* Type detection
#include <stdlib.h> //* Memory managing and type exchange
#include <string.h> //* String manipulation and managing

//* Prototypes
// Determines if the database is found
char *get_database_name();

// Count the quantity of lines in the file
int line_count(char *db_name);

// Finds the last key registered
int find_last_key(int line_count, char *db_name);

// Prints out the main menu
void main_menu(int line_count, char *db_name);

// Appends new data into the database
void append_new(int line_count, char *db_name);

// Reads and prints out all lines stored in the database
void show_all(char *db_name);

// Opens menu for specific data selection based on a field
void show_specific_menu(int line_count, char *db_name);

// Opens a menu to select fields based on the key of the register
void show_specific_by_key_menu(int line_count, char *db_name);

// Shows all Data in a line with the same key value
void show_all_by_key(int key_value, char *db_name);

// Shows only the username in a line with the same key value
void show_username_by_key(int key_value, char *db_name);

// Shows the username and password in a line with the same key value
void show_username_and_password_by_key(int key_value, char *db_name);

// Show only the password in a line with the same key value
void show_password_by_key(int key_value, char *db_name);

// Opens a menu to select fields based on the username of the register
void show_specific_by_username_menu(int line_count, char *db_name);

// Looks for name and if found returns its key value
int found_name(char name[], int line_count, char *db_name);

/*
TODO:
* Comment and document code
* Clean up
* Clarify some variable names
* Optimize code
* Handle memory better
* Handle database name
*/

//* Functionality

int main(void) {
  // Variables
  char *name = get_database_name();

  if (name == NULL)
    return 0;

  printf("\nDatabase name is: %s \n", name);

  int lines = line_count(name);

  // Print main menu
  main_menu(lines, name);

  return 0;
}

// Determines if the database is found
char *get_database_name() {
  // Variables
  char select;

  char *db_name = malloc(30 * sizeof(char));
  char f_ext[5] = ".txt";

  FILE *file;

  // Functionality: determine if the file exist
  printf("\nName must contain the \".txt\" extension\n");
  printf("\nIntroduce the name of the database: ");
  scanf("%s", db_name);

  realloc(db_name, strlen(db_name) * sizeof(char));

  file = fopen(db_name, "r");

  if (file == NULL) {
    fclose(file);
    printf("This is file does not exist would you like to create it? \n");
    printf("(y)es (n)o: ");
    scanf(" %c", &select);

    if (tolower(select) == 'n') {
      printf("Understood system will close\n");
      free(db_name);
      return NULL;
    } else if (tolower(select) == 'y') {
      printf("Understood file will be create and fields will be inserted \n");

      file = fopen(db_name, "w");

      fprintf(file, "Key, User, Password");

      fclose(file);

      return db_name;
    } else {
      printf("This is not a valid option please try again! \n");
      free(db_name);
      return NULL;
    }
  }

  printf("\nDatabase found! \n");
  fclose(file);
  return db_name;
}

// Count the quantity of lines in the file
int line_count(char *db_name) {
  // Variables
  int lines = 0;
  char ch;

  FILE *file;

  // Functionality: Loops through text file to find lines
  file = fopen(db_name, "r");

  while ((ch = fgetc(file)) != EOF) {
    if (ch == '\n')
      lines++;
  }
  lines++;

  fclose(file);
  return lines;
}

// Prints out the main menu
void main_menu(int line_count, char *db_name) {
  // Variables
  int selection; // Menu selection

  // Functionality
  printf("\n");
  printf("Welcome to database: ");
  printf("\n");
  printf("\nSelect one of the following options: ");
  printf("\n 1.Append new");
  printf("\n 2.Read all");
  printf("\n 3.Read specific");
  printf("\n 4.Close system");
  printf("\n: ");
  scanf("%i", &selection);
  printf("\n");

  switch (selection) {
  case 1:
    append_new(line_count, db_name);
    break;

  case 2:
    show_all(db_name);
    break;

  case 3:
    show_specific_menu(line_count, db_name);
    break;

  case 4:
    printf("Understood closing system!\n");
    return;

  default:
    printf("\nNot a valid option \n");
    break;
  }
}

// Finds the last key registered
int find_last_key(int line_count, char *db_name) {
  // Variables
  int count = 0;
  int x_size = 1;
  int key;

  char ch;
  char *x = malloc(sizeof(char));

  FILE *file;

  // Functionality: Find the last key to set next optimally
  file = fopen(db_name, "r");

  while ((ch = fgetc(file)) != EOF) {
    if (ch == '\n')
      count++;

    if (count + 1 == line_count && isdigit(ch)) {
      x_size++;
      x = realloc(x, x_size * sizeof(char));
      x[x_size - 2] = ch;
    }

    if (count + 1 == line_count && ch == ',')
      break;
  }

  x[x_size - 1] = '\0';
  key = atoi(x);

  fclose(file);
  free(x);

  return key;
}

// Appends new data into the database
void append_new(int line_count, char *db_name) {
  // Variables
  int key = find_last_key(line_count, db_name);
  const int MAX_INPUT_SIZE = 30;

  char username[MAX_INPUT_SIZE];
  char password[MAX_INPUT_SIZE];

  FILE *file;

  // Functionality: Append new data to the database
  file = fopen(db_name, "a");

  if (line_count == 1)
    key = 0;
  else
    key++;

  printf("~~Username must be 6-30 characters long~~ \n");
  printf("Introduce username: ");
  scanf("%s", &username);

  if (strlen(username) <= 6 || strlen(username) >= 30) {
    printf("\n Username is to short or too long, must be 6-30 characters \n");
    return;
  }

  printf("\n\n");

  printf("~~Password must be 6-30 characters long~~ \n");
  printf("Introduce password: ");
  scanf("%s", &password);

  if (strlen(password) <= 6 || strlen(password) >= 30) {
    printf("\n Username is to short or too long, must be 6-30 characters \n");
    return;
  }

  fprintf(file, "\n%i, %s, %s.", key, username, password);
  printf("\nInserted: ");
  printf("\nkey: %i,", key);
  printf("\nUser: %s,", username);
  printf("\nPassword: %s", password);
  printf("\n");

  fclose(file);
}

// Reads and prints out all lines stored in the database
void show_all(char *db_name) {
  // Variables
  char line[70];

  FILE *file;

  // Functionality: Read all the contents of DB
  file = fopen(db_name, "r");

  printf("Database content: \n");
  while (fgets(line, 70, file)) {
    printf(" %s", line);
  }

  fclose(file);
}

// Opens menu for specific data selection based on a field
void show_specific_menu(int line_count, char *db_name) {
  // Variables
  int selection;

  // functionality: Handle menu for specific selection fields
  printf("\n");
  printf("What field to you wish to select by: ");
  printf("\n 1.Key");
  printf("\n 2.Username");
  printf("\n: ");
  scanf("%i", &selection);
  printf("\n");

  switch (selection) {
  case 1:
    show_specific_by_key_menu(line_count, db_name);
    break;

  case 2:
    show_specific_by_username_menu(line_count, db_name);
    break;

  default:
    printf("This is not a selectable field");
    break;
  }
}

// Opens a menu to select fields based on the key of the register
void show_specific_by_key_menu(int line_count, char *db_name) {
  // Variables
  int selection;
  int key;
  int lastkey = find_last_key(line_count, db_name);

  // Functionality: Menu for specific search by key
  printf("\n");
  printf("What field should be shown: ");
  printf("\n 1.All");
  printf("\n 2.Username");
  printf("\n 3.Username & Password");
  printf("\n 4.Password");
  printf("\n: ");
  scanf("%i", &selection);
  printf("\n");

  printf("Key: ");
  scanf("%i", &key);
  printf("\n");
  if (key > lastkey || key < 0) {
    printf("This is not a valid key!");
    return;
  }

  switch (selection) {
  case 1:
    printf("\nAll: ");
    show_all_by_key(key, db_name);
    break;

  case 2:
    printf("\nName:");
    show_username_by_key(key, db_name);
    break;

  case 3:
    printf("\nName & Password:");
    show_username_and_password_by_key(key, db_name);
    break;

  case 4:
    printf("\nPassword:");
    show_password_by_key(key, db_name);
		break;

	default:
		printf("This is not a showable field");
		break;
	}
}

// Shows all Data in a line with the same key value
void show_all_by_key(int key_value, char *db_name) {
  // Variables
  int count = 0;

  char line[70];

  FILE *file;

  // Functionality: Print all in line where key is
  file = fopen(db_name, "r");

  while (fgets(line, 1000, file)) {
    count++;
    if (count - 2 == key_value)
      printf("%s", line);
  }

  fclose(file);
}

// Shows only the username in a line with the same key value
void show_username_by_key(int key_value, char *db_name) {
  // Variables
  int count = 0;
  int ic = 0;
  int comacount = 0;
  int spacecount = 0;

  char ch;
  char line[70];

  FILE *file;

  file = fopen(db_name, "r");

  while (fgets(line, 1000, file)) {
    count++;
    if (count - 2 == key_value) {
      while (ch != '\n') {
        ch = line[ic];

        if (ch == ',')
          comacount++;

        if (ch == ' ')
          spacecount++;

        if (comacount > 0 && spacecount > 0 && ch == ',')
          break;

        if (comacount > 0 && spacecount > 0)
          printf("%c", ch);
        ic++;
      }
    }
  }

  fclose(file);
}

// Shows the username and password in a line with the same key value
void show_username_and_password_by_key(int key_value, char *db_name) {
  // Variables
  int count = 0;
  int ic = 0;
  int comacount = 0;
  int spacecount = 0;

  char ch;
  char line[70];

  FILE *file;

  file = fopen(db_name, "r");

  while (fgets(line, 1000, file)) {
    count++;
    if (count - 2 == key_value) {
      while (ch != '\n') {
        ch = line[ic];

        if (ch == ',')
          comacount++;

        if (ch == ' ')
          spacecount++;

        if (comacount > 0 && spacecount > 0 && ch == '.')
          break;

        if (comacount > 0 && spacecount > 0)
          printf("%c", ch);
        ic++;
      }
    }
  }

  fclose(file);
}

// Show only the password in a line with the same key value
void show_password_by_key(int key_value, char *db_name) {
  // Variables
  int count = 0;
  int ic = 0;
  int comacount = 0;
  int spacecount = 0;

  char ch;
  char line[70];

  FILE *file;

  file = fopen(db_name, "r");

  while (fgets(line, 1000, file)) {
    count++;

    if (count - 2 == key_value) {
      while (ch != '\n') {
        ch = line[ic];

        if (ch == ',')
          comacount++;

        if (ch == ' ')
          spacecount++;

        if (comacount > 1 && spacecount > 1 && ch == '.')
          break;

        if (comacount > 1 && spacecount > 1)
          printf("%c", ch);
        ic++;
      }
    }
  }

  fclose(file);
}

// Opens a menu to select fields based on the username of the register
void show_specific_by_username_menu(int line_count, char *db_name) {
  // Variables
  int selection;
  char name[30];

  // Functionality: Specific search by username
  printf("\n");
  printf("What field should be shown: ");
  printf("\n 1.All");
  printf("\n 2.Key");
  printf("\n 3.key & Password");
  printf("\n 4.Password");
  printf("\n: ");
  scanf("%i", &selection);
  printf("\n");

  printf("\n");
  printf("Introduce the name to search for: ");
  scanf("%s", &name);

  int found_name_key = found_name(name, line_count, db_name);

  if (found_name_key == -1) {
    printf("\nName %s was not found\n", name);
    return;
  }

  switch (selection) {
  case 1:
    printf("\nAll: ");
    show_all_by_key(found_name_key, db_name);
    break;

  case 2:
    printf("\nKey: %i\n", found_name_key);
    break;

  case 3:
    printf("\nKey & Password: %i,", found_name_key);
    show_password_by_key(found_name_key, db_name);
    printf("\n");
    break;

  case 4:
    printf("\nPassword:");
    show_password_by_key(found_name_key, db_name);
    printf("\n");
    break;

  default:
    printf("\nNot a valid option \n");
    break;
  }

  return;
}

// Looks for name and if found returns its key value
int found_name(char name[], int line_count, char *db_name) {
  // Variables
  int spacecount = 0;
  int cc = 0;
  int counter = 0;
  int cmpsize = 1;

  char ch;
  char line[70];
  char *cmpname = malloc(sizeof(char));

  FILE *file;

  file = fopen(db_name, "r");

  while (fgets(line, 70, file) != NULL) {
    if (counter + 1 == line_count)
      break;
    cc = 0;
    spacecount = 0;
    cmpsize = 1;

    while ((ch = fgetc(file)) != '\n') {
      if (ch == ' ') {
        spacecount++;
        continue;
      }

      if (spacecount == 1 && ch == ',')
        break;

      if (spacecount == 0)
        continue;

      if (spacecount == 1) {
        cmpsize++;
        cmpname = realloc(cmpname, cmpsize * sizeof(char));
        cmpname[cmpsize - 2] = ch;
      }
      cc++;
    }

    cmpname[cmpsize - 1] = '\0';

    if (strcasecmp(name, cmpname) == 0) {
      fclose(file);
      free(cmpname);
      return counter;
    }
    counter++;
  }

  fclose(file);
  free(cmpname);

  return -1;
}
