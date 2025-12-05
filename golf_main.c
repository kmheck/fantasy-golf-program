#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "golf_info.h"
struct player_info tournament_player[160];
struct database_data database_player;

/* test only */
FILE *test_output_file;
char test_output_filename[20];

/******************************************************************************
Description:
   This program attempts to read in data from golf tournament results
   (published publicly at various sites), and extract the player names and
   money earned, and copy that data to a file that mirrors a database of
   players and tournament earnings.  That earnings in that file can then be
   copied directly into the database spreadsheet to save on data entry.

   The most difficult part about this program, is reading the player names
   from the tournament file and "matching" them with the names in the database.
   Currently it tries to do an exact match of strings for the names, but it
   may be in need of a more sophisticated approach in the future.

******************************************************************************/
int main(void)
  {
  char tournament_input_filename[30], golf_database_filename[30], tournament_output_filename[30];
  FILE *tournament_file, *golf_database_file, *tournament_output_file;
  int player_count;
  int file_type;
  int i;

   strcpy(test_output_filename, "test_output.txt");
   test_output_file = fopen(test_output_filename,"w");

  printf("Enter the name of the tournament file to open\n");
  gets(tournament_input_filename);

  tournament_file = fopen(tournament_input_filename,"r");
  if (tournament_file != NULL)
    ;
  else
    {
    printf("File %s could not be found",tournament_input_filename);
    exit(1);
    }
/*  printf("Enter the name of the database input file to open\n");
  gets(golf_database_filename);*/

  golf_database_file = fopen("golfdb.txt","r");
  if (golf_database_file != NULL)
    ;
  else
    {
    printf("File golfdb.txt could not be found\n");
    exit(-1);
    }

  i = 0;
  while(tournament_input_filename[i] != '.')
     {
     tournament_output_filename[i] = tournament_input_filename[i];
     i++;
     }
  tournament_output_filename[i] = '.';
  tournament_output_filename[i+1] = 'x';
  tournament_output_filename[i+2] = 'l';
  tournament_output_filename[i+3] = 's';
  tournament_output_filename[i+4] = '\0';

  tournament_output_file = fopen(tournament_output_filename,"w");

  file_type = 2;
  if (file_type == 1)
    /*player_count = read_player_data(tournament_file);*/
    ;
  else
    player_count = read_AP_data(tournament_file);

  while(feof(golf_database_file) == 0)
      {
      if (read_database_data(database_player.entire_name, golf_database_file) == 0)
         append_tour_player_to_db(&database_player, tournament_player, player_count, tournament_output_file);
      else
         break;
      }

  fclose(tournament_file);
  fclose(golf_database_file);
  fclose(tournament_output_file);

  /*test*/
  fclose(test_output_file);
  /*fclose(test_output_file);*/
  return 0;
  }



/*int read_player_data(FILE *fp)
{
char player_string[80];
long money;
int i;
char last_name[20], first_name[20];
char fixed_last_name[20], fixed_first_name[20];
char money_string[10];
int count = 0;

while(feof(fp) == 0)
  {
  fgets(player_string, 80, fp);
  for (i=0; i<=45; i++)
    {
    if (player_string[i] == '\n')
      break;

    if (i <= 15)
      last_name[i] = player_string[i];
    if (i >= 16 && i <= 30)
      first_name[i-16] = player_string[i];
    if (i >= 38 && i <= 43)
      money_string[i-38] = player_string[i];

    }

  money = string_to_integer(money_string);
  t[count].money = (money + 500)/1000;

  fix_last_name(last_name, fixed_last_name);
  fix_first_name(first_name, fixed_first_name);

  strcpy(tournament_player[count].last_name, fixed_last_name);
  strcpy(tournament_player[count].first_name, fixed_first_name);

  count++;
  }

return count;
}*/


/*void fix_last_name(char broken[20], char fixed[20])
{
int i;

for (i = 0; i < 20; i++)
  {
  if ((broken[i] != ' ') && (broken[i] != ','))
    fixed[i] = broken[i];
  else
    {
    fixed[i] = '\0';
    break;
    }
  }
}*/

/*void fix_first_name(char broken[20], char fixed[20])
{
int i,j;

for (i = 0; i < 20; i++)
  {
  if (broken[i] != ' ')
    fixed[i] = broken[i];
  else
    {
    if (broken[i+1] != ' ')
      {
      fixed[i] = broken[i];
      j = 1;
      while (broken[i+j] != ' ')
        {
        fixed[i+j] = broken[i+j];
        j++;
        }
      fixed[i+j] = '\0';
      break;
      }
    else
      {
      fixed[i] = '\0';
      break;
      }
    }
  }
}*/


int read_AP_data(FILE *fp)
{
int i = 0;
int j = 0;
char last_name[20];
char entire_name[40];
char line_element[20][40] = {"", "", "", "", "","", "", "", "", "","", "", "", "", "","", "", "", "", ""};
char other_line_element[20][40] = {"", "", "", "", "","", "", "", "", "","", "", "", "", "","", "", "", "", ""};
char money_string[20];
char test_string[40];
int on_first_name = -1;
int count=0;
int number_elements;
int index;
int money_index;
int element_length;
int last_name_element_index;

char player_string[80];
char copy_of_player_string[80];


   while(feof(fp) == 0)
   {
      fgets(player_string, 80, fp);
      /*fprintf(test_output_file, "Player String = %s\n", player_string);*/

	  /* first parse on comma to get name */
      /*parse_line(player_string, line_element, &number_elements, ',');*/
      const char delimiter[4] = ",";
      char* token;

      strcpy(copy_of_player_string, player_string);
      token = strtok(copy_of_player_string, delimiter);

      /*strcpy(entire_name, line_element[0]);*/

      strcpy(entire_name, token);
      strcpy(tournament_player[count].entire_name, entire_name);
      fprintf(test_output_file, "tournament player name is %s\n",
                 tournament_player[count].entire_name);

      char money_symbol = '$';

      /* Get the string past the delimiter (money)*/
      /*token = strtok(NULL, delimiter);
      strcpy(money_string, token);*/

      while (token != 0)
      {
		strcpy(test_string, token);
		char *result = strchr(test_string, money_symbol);
		if (result != NULL)
		{
			strcpy(money_string, test_string);
			fprintf(test_output_file, "money string found\n");
			break;
		}
		token = strtok(NULL, delimiter);
      }

      /* parse again to get money */ /*Is this correct? Should it be parsed again?*/

      /*parse_line(player_string, other_line_element, &number_elements, ' ');*/

      /*for (index = 0; index < number_elements; index++)
      {
         if (other_line_element[index][0] == '$')
         {
            money_index = index;
            break;
         }
      }
      strcpy(money_string, other_line_element[money_index]);*/
      fprintf(test_output_file, "money_string is %s\n",
                 money_string);
      tournament_player[count].money = (string_to_integer(money_string) + 500)/1000;
      fprintf(test_output_file, "money after string_to_integer conversion is %d\n",
                 tournament_player[count].money);

      count++;
   }
   return count;
}

/*int read_database_data(struct database_data *player, FILE *fp)
{
int i = 0;
int j = 0;
char last_name[20];
char first_name [20] = "";
char entire_name[40];
char name_element[4][40] = {"", "", "", ""};
int number_elements;
int on_last_name = -1;
int index;
int first_name_index = 0;
char player_string[80] = "";
int last_name_length;

   fgets(player_string, 80, fp);

   if (strlen(player_string) > 3)
   {


      parse_line(player_string, name_element, &number_elements, ',');

      strcpy(last_name, name_element[0]);
      last_name_length = strlen(last_name);
      if (last_name[last_name_length - 1] == ',')
         last_name[last_name_length - 1] = '\0';

      for (index = 0; index < strlen(name_element[1]); index++)
      {
         if ((name_element[1][index] != ' ') ||
             ((name_element[1][index] == ' ') &&
             (index > 1)))

         {
            first_name[first_name_index] = name_element[1][index];
            first_name_index++;
         }
      }

      first_name[first_name_index] = '\0';

      strcpy(entire_name, first_name);

      strcat(entire_name, " ");
      strcat(entire_name, last_name);


      strcpy(player->entire_name, entire_name);
      return 0;
   }
   else
      return -1;

}*/




