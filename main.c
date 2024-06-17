//* Libraries
#include <stdio.h>  //* Standard in and out
#include <ctype.h>  //* Type detection
#include <stdlib.h> //* Memory managing and type exchange
#include <string.h> //* String manipulation and managing

/*
TODO:
*/

//* Prototypes
// Determines if the database is found
char *get_database_name();

// Count the quantity of lines in the file
int get_line_count(char *db_name);

// Finds the last key registered
int find_last_key_value(int line_count, char *db_name);

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

//* Functionality

int main(void) {
  // Variables
  char *name = get_database_name();

  if (name == NULL)
    return 0;

  printf("\nDatabase name is: %s \n", name);

  int lines_count = get_line_count(name);

  // Print main menu
  main_menu(lines_count, name);

  free(name);
  return 0;
}

// Determines if the database is found
char *get_database_name() {
  // Variables
  char select;
  char *db_name = malloc(30 * sizeof(char));

  FILE *database;

  // Functionality: determine if the file exist
  printf("\nName must contain the \".txt\" extension\n");
  printf("\nIntroduce the name of the database: ");
  scanf("%s", db_name);

  db_name = realloc(db_name, strlen(db_name) * sizeof(char));

  database = fopen(db_name, "r");

  if (database == NULL) {
    fclose(database);
    printf("This is file does not exist would you like to create it? \n");
    printf("(y)es (n)o: ");
    scanf(" %c", &select);

    if (tolower(select) == 'n') {
      printf("Understood system will close\n");
      free(db_name);
      return NULL;
    } else if (tolower(select) == 'y') {
      printf("Understood file will be create and fields will be inserted \n");

      database = fopen(db_name, "w");

      fprintf(database, "Key, User, Password");

      fclose(database);

      return db_name;
    } else {
      printf("This is not a valid option please try again! \n");
      free(db_name);
      return NULL;
    }
  }

  printf("\nDatabase found! \n");
  fclose(database);
  return db_name;
}

// Count the quantity of lines in the file
int get_line_count(char *db_name) {
  // Variables
  int lines_count = 0;

  char character;

  FILE *database;

  // Functionality: Loops through text file to find lines
  database = fopen(db_name, "r");

  while ((character = fgetc(database)) != EOF) {
    if (character == '\n')
      lines_count++;
  }
  lines_count++;

  fclose(database);
  return lines_count;
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

  return;
}

// Finds the last key registered
int find_last_key_value(int line_count, char *db_name) {
  // Variables
  int key_size = 1;
  int key_value = 0;
  int line_counter = 0;

  char character;
  char *key = malloc(sizeof(char));

  FILE *database;

  // Functionality: Find the last key to set next optimally
  database = fopen(db_name, "r");

  while ((character = fgetc(database))!= EOF) {
    if (character == '\n')
      line_counter++;

    if (line_counter + 1 == line_count && isdigit(character)) {
      key_size++;
      key = realloc(key, key_size * sizeof(char));
      key[key_size - 2] = character;
    }

    if (line_counter + 1 == line_count && character == ',')
      break;
  }

  key[key_size - 1] = '\0';
  key_value = atoi(key);

  fclose(database);
  free(key);

  return key_value;
}

// Appends new data into the database
void append_new(int line_count, char *db_name) {
  // Variables
  int key = find_last_key_value(line_count, db_name);
  int name_check = 0;

  char *username = malloc(30 * sizeof(char));
  char *password = malloc(30 * sizeof(char));

  FILE *database;

  // Functionality: Append new data to the database
  database = fopen(db_name, "a");

  if (line_count == 1)
    key = 0;
  else
    key++;

  printf("~~Username must be 6-30 characters long~~ \n");
  printf("Introduce username: ");
  scanf("%s", username);

  username = realloc(username, (strlen(username) + 1) * sizeof(char));
  name_check = found_name(username, line_count, db_name);

  if(name_check != -1) {
      printf("\n This username is already in system, please pick a new one \n");
      return;
  }

  if (strlen(username) < 6 || strlen(username) > 30) {
    printf("\n Username is to short or too long, must be 6-30 characters \n");
    return;
  }

  printf("\n\n");

  printf("~~Password must be 6-30 characters long~~ \n");
  printf("Introduce password: ");
  scanf("%s", password);

  password = realloc(password, (strlen(password) + 1) * sizeof(char));

  if (strlen(password) < 6 || strlen(password) > 30) {
    printf("\n Username is to short or too long, must be 6-30 characters \n");
    return;
  }

  fprintf(database, "\n%i, %s, %s.", key, username, password);
  printf("\nInserted: ");
  printf("\nkey: %i,", key);
  printf("\nUser: %s,", username);
  printf("\nPassword: %s", password);
  printf("\n");

  free(username);
  free(password);
  fclose(database);
  return;
}

// Reads and prints out all lines stored in the database
void show_all(char *db_name) {
  // Variables
  char line[70];

  FILE *database;

  // Functionality: Read all the contents of DB
  database = fopen(db_name, "r");

  printf("Database content: \n");
  while (fgets(line, 70, database)) {
    printf(" %s", line);
  }

  fclose(database);
  return;
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

  return;
}

// Opens a menu to select fields based on the key of the register
void show_specific_by_key_menu(int line_count, char *db_name) {
  // Variables
  int selection;
  int key_value;
  int last_key_value = find_last_key_value(line_count, db_name);

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
  scanf("%i", &key_value);
  printf("\n");
  if (key_value > last_key_value || key_value < 0) {
    printf("This is not a valid key!");
    return;
  }

  switch (selection) {
  case 1:
    printf("\nAll: ");
    show_all_by_key(key_value, db_name);
    break;

  case 2:
    printf("\nName:");
    show_username_by_key(key_value, db_name);
    break;

  case 3:
    printf("\nName & Password:");
    show_username_and_password_by_key(key_value, db_name);
    break;

  case 4:
    printf("\nPassword:");
    show_password_by_key(key_value, db_name);
    break;

  default:
    printf("This is not a showable field");
    break;
  }

  return;
}

// Shows all Data in a line with the same key value
void show_all_by_key(int key_value, char *db_name) {
  // Variables
  int line_counter = 0;

  char line[70];

  FILE *database;

  // Functionality: Print all in line where key is
  database = fopen(db_name, "r");

  while (fgets(line, 1000, database)) {
    line_counter++;
    if (line_counter - 2 == key_value)
      printf("%s", line);
  }

  fclose(database);
  return;
}

// Shows only the username in a line with the same key value
void show_username_by_key(int key_value, char *db_name) {
  // Variables
  int line_counter = 0;
  int space_counter = 0;
  int current_index = 0;

  char line[70];
  char character;

  FILE *database;

  database = fopen(db_name, "r");

  while (fgets(line, 1000, database)) {
    line_counter++;
    if (line_counter - 2 == key_value) {
      while (character != '\n') {
        character = line[current_index];

        if (character == ' ')
          space_counter++;

        if (space_counter > 0 && character == ',')
          break;

        if (space_counter > 0)
          printf("%c", character);

        current_index++;
      }
    }
  }

  fclose(database);
  return;
}

// Shows the username and password in a line with the same key value
void show_username_and_password_by_key(int key_value, char *db_name) {
  // Variables
  int line_counter = 0;
  int space_counter = 0;
  int current_index = 0;

  char line[70];
  char character;

  FILE *database;

  database = fopen(db_name, "r");

  while (fgets(line, 1000, database)) {
    line_counter++;
    if (line_counter - 2 == key_value) {
      while (character != '\n') {
        character = line[current_index];

        if (character == ' ')
          space_counter++;

        if (space_counter > 0 && character == '.')
          break;

        if (space_counter > 0)
          printf("%c", character);
        
        current_index++;
      }
    }
  }

  fclose(database);
  return;
}

// Show only the password in a line with the same key value
void show_password_by_key(int key_value, char *db_name) {
  // Variables
  int line_counter = 0;
  int space_counter = 0;
  int current_index = 0;

  char line[70];
  char character;

  FILE *database;

  database = fopen(db_name, "r");

  while (fgets(line, 1000, database)) {
    line_counter++;

    if (line_counter - 2 == key_value) {
      while (character != '\n') {
        character = line[current_index];

        if (character == ' ')
          space_counter++;

        if (space_counter > 1 && character == '.')
          break;

        if (space_counter > 1)
          printf("%c", character);
        current_index++;
      }
    }
  }

  fclose(database);
  return;
}

// Opens a menu to select fields based on the username of the register
void show_specific_by_username_menu(int line_count, char *db_name) {
  // Variables
  int selection;

  char *username = malloc(30 * sizeof(char));

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
  scanf("%s", username);

  username = realloc(username, (strlen(username) + 1) * sizeof(char));

  int found_name_key = found_name(username, line_count, db_name);

  if (found_name_key == -1) {
    printf("\nName %s was not found\n", username);
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

  free(username);
  return;
}

// Looks for name and if found returns its key value
int found_name(char name[], int line_count, char *db_name) {
  // Variables
  int line_counter = 0;
  int compare_size = 1;
  int space_counter = 0;

  char line[70];
  char character;
  char *compare_name = malloc(sizeof(char));

  FILE *database;

  database = fopen(db_name, "r");

  while (fgets(line, 70, database) != NULL) {
    if (line_counter + 1 == line_count)
      break;
    space_counter = 0;
    compare_size = 1;

    while ((character = fgetc(database)) != '\n') {
      if (character == ' ') {
        space_counter++;
        continue;
      }

      if (space_counter == 1 && character == ',')
        break;

      if (space_counter == 0)
        continue;

      if (space_counter == 1) {
        compare_size++;
        compare_name = realloc(compare_name, compare_size * sizeof(char));
        compare_name[compare_size - 2] = character;
      }
    }

    compare_name[compare_size - 1] = '\0';

    if (strcasecmp(name, compare_name) == 0) {
      fclose(database);
      free(compare_name);
      return line_counter;
    }
    line_counter++;
  }

  fclose(database);
  free(compare_name);
  return -1;
}

