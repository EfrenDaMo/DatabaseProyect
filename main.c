//* Libraries
#include <stdio.h>   //* Standard in and out
#include <ctype.h>   //* Type detection
#include <stdlib.h>  //* Memory managing and type exchange
#include <string.h>  //* String manipulation and managing
#include <time.h>    //* Time mangement and handeling 
#ifdef _WIN32
    #include <windows.h> //* Windows functions
#elif __linux__
    #include <unistd.h>  //* Linux functions
#endif

#define MAX_LINE_LENGTH 70

/*
TODO:
* Custom Fields
* Databases, tables and relations
* Custom field searching
*- Better CLI looks:
*   - Database selector
*/

//* Prototypes
// Determines if the database is found
char *get_database_name();

// Count the quantity of lines in the file
int get_line_count(char *db_name);

// Finds the last key registered
int find_last_key_value(int line_count, char *db_name);

// Prints out the main menu
int main_menu(int line_count, char *db_name);

// Appends new data into the database
void append_new(int line_count, char *db_name);

// Reads and prints out all lines stored in the database
void show_all(char *db_name);

// Opens menu for specific data selection based on a field
void show_specific_menu(int line_count, char *db_name);

// Reads key inserted by user to then search in database
int read_key(int line_count, char *db_name);

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

// Reads name as input and searches for it in database
int read_name(int line_count, char *db_name);

// Opens a menu to select fields based on the username of the register
void show_specific_by_username_menu(int line_count, char *db_name);

// Looks for name and if found returns its key value
int found_name(char name[], int line_count, char *db_name);

//* Functionality

int main(void) {
  // Variables
  int menu_return;

  char cont;
  char option;

  char *db_name = get_database_name();

  if (db_name == NULL)
    return 0;

  do {
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif

    int lines_count = get_line_count(db_name);

    // Print main menu
    menu_return = main_menu(lines_count, db_name);

    if(menu_return == 4)
      break;

    printf("\nWould you like to continue? \n");
    printf("(y)es (n)o: ");
    scanf(" %c", &option);

  }while (tolower(option) != 'n');
  
  free(db_name);
  return 0;
}

// Determines if the database is found
char *get_database_name() {
  // Variables
  char select;
  char yes_no;

  int valid_file = 0;

  char *db_name = malloc(30 * sizeof(char));
  if (db_name == NULL) {
    free(db_name);
    return NULL;
  }

  FILE *database;

  // Functionality: determine if the file exist
  while (!valid_file) {
    do {
#ifdef _WIN32
      system("cls");
#elif __linux__
      system("clear");
#endif

      printf("\nName must contain the \".txt\" extension!\n");
      printf("\nIntroduce the name of the database: ");
      scanf("%s", db_name);

      printf("\nAre you sure about this name?\n");
      printf("(y)es (n)o: ");
      scanf(" %c", &yes_no);
    } while (tolower(yes_no) != 'y');

    db_name = realloc(db_name, (strlen(db_name) + 1) * sizeof(char));
    if (db_name == NULL) {
      free(db_name);
      return NULL;
    }

    database = fopen(db_name, "r");

    if (database == NULL) {
      printf("\nThis is file does not exist would you like to create it? \n");
      printf("(y)es (n)o: ");
      scanf(" %c", &select);

      switch (tolower(select)) {
      case 'n':
        printf("\nPlease introduce the name you'll like to use\n");
#ifdef _WIN32
        Sleep(2000);
#elif __linux__
        sleep(2);
#endif
        break;

      case 'y':
        printf(
            "\nUnderstood file will be create and fields will be inserted \n");

        database = fopen(db_name, "w");
        fprintf(database, "Key, User, Password");
        fclose(database);

        valid_file = 1;

#ifdef _WIN32
        Sleep(2000);
#elif __linux__
        sleep(2);
#endif
        break;

      default:
        printf("\nThis is not a valid option, please try again! \n");
#ifdef _WIN32
        Sleep(2000);
#elif __linux__
        sleep(2);
#endif
        break;
      }
    } else {
      printf("\nDatabase found! \n");
      fclose(database);
      valid_file = 1;
#ifdef _WIN32
      Sleep(2000);
#elif __linux__
      sleep(2);
#endif
    }
  }

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
int main_menu(int line_count, char *db_name) {
  // Variables
  int selection; // Menu selection

  // Functionality
  printf("\nDatabase name is: %s \n", db_name);
  printf("\n~~~~~Welcome~~~~~\n");

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
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif

    append_new(line_count, db_name);
    break;

  case 2:
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif

    show_all(db_name);
    break;

  case 3:
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif

    show_specific_menu(line_count, db_name);
    break;

  case 4:
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif

    printf("\nDatabase name is: %s \n", db_name);
    printf("\nUnderstood closing system!\n");
    return 4;

  default:
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif

    printf("\nDatabase name is: %s \n", db_name);
    printf("\nNot a valid option \n");
    break;
  }

  return 0;
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

  while ((character = fgetc(database)) != EOF) {
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

  printf("\nDatabase name is: %s \n", db_name);

  printf("\n~~Username must be 6-30 characters long~~ \n");
  printf("Introduce username: ");
  scanf("%s", username);

  username = realloc(username, (strlen(username) + 1) * sizeof(char));
  name_check = found_name(username, line_count, db_name);

  if (name_check != -1) {
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
  char line[MAX_LINE_LENGTH];

  time_t start, end;

  float t;

  FILE *database;

  // Functionality: Read all the contents of DB
  start = clock();
  database = fopen(db_name, "r");

  printf("\nDatabase name is: %s \n", db_name);

  printf("\nDatabase content: \n");
  while (fgets(line, MAX_LINE_LENGTH, database)) {
    printf(" %s", line);
  }
  printf("\n");

  fclose(database);
  end = clock();

  t = (float) (end - start) / (float) CLOCKS_PER_SEC;

  printf("\nTime elapsed: %.3fs\n", t);
  return;
}

// Opens menu for specific data selection based on a field
void show_specific_menu(int line_count, char *db_name) {
  // Variables
  int selection;

  // functionality: Handle menu for specific selection fields
  printf("\nDatabase name is: %s \n", db_name);

  printf("\n");
  printf("What field to you wish to select by: ");
  printf("\n 1.Key");
  printf("\n 2.Username");
  printf("\n 3.Return to previous menu");
  printf("\n: ");
  scanf("%i", &selection);
  printf("\n");

  switch (selection) {
  case 1:
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif

    show_specific_by_key_menu(line_count, db_name);
    break;

  case 2:
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif

    show_specific_by_username_menu(line_count, db_name);
    break;

  case 3:
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif
    printf("\nDatabase name is: %s \n", db_name);
    printf("\nUnderstood returning to previous menu! \n");
#ifdef _WIN32
    Sleep(2000);
    system("cls");
#elif __linux__
    sleep(2);
    system("clear");
#endif
    main_menu(line_count, db_name);
    break;

  default:
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif

    printf("This is not a selectable field");
    break;
  }

  return;
}

// Reads key inserted by user to then search in database
int read_key(int line_count, char *db_name) {
  // Variables
  int key_value;
  int last_key_value = find_last_key_value(line_count, db_name);

  printf("Key: ");
  scanf("%i", &key_value);
  printf("\n");
  if (key_value > last_key_value || key_value < 0) {
    printf("This is not a valid key!");
    return -1;
  }

  return key_value;
}

// Opens a menu to select fields based on the key of the register
void show_specific_by_key_menu(int line_count, char *db_name) {
  // Variables
  int selection;
  int key_value;

  // Functionality: Menu for specific search by key
  printf("\nDatabase name is: %s \n", db_name);

  printf("\n");
  printf("What field should be shown: ");
  printf("\n 1.All");
  printf("\n 2.Username");
  printf("\n 3.Username & Password");
  printf("\n 4.Password");
  printf("\n 5.Return to previous menu");
  printf("\n: ");
  scanf("%i", &selection);
  printf("\n");

  switch (selection) {
  case 1:
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif
    printf("\nDatabase name is: %s \n", db_name);

    key_value = read_key(line_count, db_name);

    if(key_value == -1) {
      return;
    }

    printf("\nAll: ");
    show_all_by_key(key_value, db_name);
    break;

  case 2:
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif
    printf("\nDatabase name is: %s \n", db_name);

    key_value = read_key(line_count, db_name);

    if(key_value == -1) {
      return;
    }

    printf("\nName:");
    show_username_by_key(key_value, db_name);
    break;

  case 3:
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif
    printf("\nDatabase name is: %s \n", db_name);

    key_value = read_key(line_count, db_name);

    if(key_value == -1) {
      return;
    }

    printf("\nName & Password:");
    show_username_and_password_by_key(key_value, db_name);
    break;

  case 4:
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif
    printf("\nDatabase name is: %s \n", db_name);

    key_value = read_key(line_count, db_name);

    if(key_value == -1) {
      return;
    }

    printf("\nPassword:");
    show_password_by_key(key_value, db_name);
    break;

  case 5:
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif
    printf("\nDatabase name is: %s \n", db_name);
    printf("\nUnderstood returning to previous menu! \n");
#ifdef _WIN32
    Sleep(2000);
    system("cls");
#elif __linux__
    sleep(2);
    system("clear");
#endif
    show_specific_menu(line_count, db_name);
    break;

  default:
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif

    printf("\nDatabase name is: %s \n", db_name);
    printf("\nThis is not a showable field");
    break;
  }

  return;
}

// Shows all Data in a line with the same key value
void show_all_by_key(int key_value, char *db_name) {
  // Variables
  int line_counter = 0;

  float t;

  char line[MAX_LINE_LENGTH];

  time_t start, end;

  FILE *database;

  // Functionality: Print all in line where key is
  start = clock();
  database = fopen(db_name, "r");

  while (fgets(line, MAX_LINE_LENGTH, database)) {
    line_counter++;
    if (line_counter - 2 == key_value)
      printf("%s", line);
  }

  fclose(database);
  end = clock();

  t = (float) (end - start) / (float) CLOCKS_PER_SEC;

  printf("\nTime elapsed: %.3fs \n", t);
  return;
}

// Shows only the username in a line with the same key value
void show_username_by_key(int key_value, char *db_name) {
  // Variables
  int line_counter = 0;
  int space_counter = 0;
  int current_index = 0;

  float t;

  char line[MAX_LINE_LENGTH];
  char character;

  time_t start, end;

  FILE *database;

  start = clock();
  database = fopen(db_name, "r");

  while (fgets(line, MAX_LINE_LENGTH, database)) {
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
  printf("\n");

  fclose(database);
  end = clock();

  t = (float) (end - start) / (float) CLOCKS_PER_SEC;

  printf("\nTime elapsed: %.3fs\n", t);
  return;
}

// Shows the username and password in a line with the same key value
void show_username_and_password_by_key(int key_value, char *db_name) {
  // Variables
  int line_counter = 0;
  int space_counter = 0;
  int current_index = 0;

  float t;

  char line[MAX_LINE_LENGTH];
  char character;

  time_t start, end;

  FILE *database;

  start = clock();
  database = fopen(db_name, "r");

  while (fgets(line, MAX_LINE_LENGTH, database)) {
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
  printf("\n");

  fclose(database);
  end = clock();

  t = (float) (end - start) / (float) CLOCKS_PER_SEC;

  printf("\nTime elapsed: %.3fs\n", t);
  return;
}

// Show only the password in a line with the same key value
void show_password_by_key(int key_value, char *db_name) {
  // Variables
  int line_counter = 0;
  int space_counter = 0;
  int current_index = 0;

  float t;

  char line[MAX_LINE_LENGTH];
  char character;

  time_t start, end;

  FILE *database;

  start = clock();
  database = fopen(db_name, "r");

  while (fgets(line, MAX_LINE_LENGTH, database)) {
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
  printf("\n");

  fclose(database);
  end = clock();

  t = (float) (end - start) / (float) CLOCKS_PER_SEC;

  printf("\nTime elapsed: %.3fs\n", t);
  return;
}

int read_name(int line_count, char *db_name) {
  // Variable Declaration
  char *username = malloc(30 * sizeof(char));

  int found_name_key;

  printf("\n");
  printf("Introduce the name to search for: ");
  scanf("%s", username);

  username = realloc(username, (strlen(username) + 1) * sizeof(char));

  found_name_key = found_name(username, line_count, db_name);

  if (found_name_key == -1) {
    printf("\nName %s was not found\n", username);
    return -1;
  }

  return found_name_key;
}

// Opens a menu to select fields based on the username of the register
void show_specific_by_username_menu(int line_count, char *db_name) {
  // Variables
  int selection;
  int found_name_key;

  float t;

  time_t start, end;

  // Functionality: Specific search by username
  printf("\nDatabase name is: %s \n", db_name);
  printf("\n");
  printf("What field should be shown: ");
  printf("\n 1.All");
  printf("\n 2.Key");
  printf("\n 3.key & Password");
  printf("\n 4.Password");
  printf("\n 5.Return to previous menu");
  printf("\n: ");
  scanf("%i", &selection);
  printf("\n");

  switch (selection) {
  case 1:
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif
    printf("\nDatabase name is: %s \n", db_name);

    found_name_key = read_name(line_count, db_name); 

    if (found_name_key == -1) {
      return;
    }

    printf("\nAll: ");
    show_all_by_key(found_name_key, db_name);
    break;

  case 2:
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif
    start = clock();
    printf("\nDatabase name is: %s \n", db_name);

    found_name_key = read_name(line_count, db_name); 

    if (found_name_key == -1) {
      return;
    }
    end = clock();

    printf("\nKey: %i\n", found_name_key);

    t = (float) (end - start) / (float) CLOCKS_PER_SEC;

    printf("\nTime elapsed: %.3fs\n", t);
    break;

  case 3:
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif
    printf("\nDatabase name is: %s \n", db_name);

    found_name_key = read_name(line_count, db_name); 

    if (found_name_key == -1) {
      return;
    }

    printf("\nKey & Password: %i,", found_name_key);
    show_password_by_key(found_name_key, db_name);
    printf("\n");
    break;

  case 4:
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif
    printf("\nDatabase name is: %s \n", db_name);

    found_name_key = read_name(line_count, db_name); 

    if (found_name_key == -1) {
      return;
    }

    printf("\nPassword:");
    show_password_by_key(found_name_key, db_name);
    printf("\n");
    break;

  case 5:
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif
    printf("\nDatabase name is: %s \n", db_name);
    printf("\nUnderstood returning to previous menu! \n");
#ifdef _WIN32
    Sleep(2000);
    system("cls");
#elif __linux__
    sleep(2);
    system("clear");
#endif
    show_specific_menu(line_count, db_name);
    break;

  default:
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif
    printf("\nDatabase name is: %s \n", db_name);
    printf("\nNot a valid option \n");
    break;
  }

  return;
}

// Looks for name and if found returns its key value
int found_name(char name[], int line_count, char *db_name) {
  // Variables
  int line_counter = 0;
  int compare_size = 1;
  int space_counter = 0;

  char line[MAX_LINE_LENGTH];
  char character;
  char *compare_name = malloc(sizeof(char));

  FILE *database;

  database = fopen(db_name, "r");

  while (fgets(line, MAX_LINE_LENGTH, database) != NULL) {
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
