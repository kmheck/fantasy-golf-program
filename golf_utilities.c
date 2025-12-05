#include <string.h>
#include <stdio.h>
#include "golf_info.h"
/* test only */
FILE *test_output_file;
char test_output_filename[20];

extern void parse_line(char line[80], char element[20][40], int *num_elements, char delimiter);

int is_alphabetic(char s)
{
   if ((s >= 'A' && s <= 'Z') || (s >= 'a' && s <= 'z'))
      return -1;
   else
      return 0;

}

long string_to_integer(char input_string[])
{
 int i;
 long n;
 int num_chars;

 num_chars = strlen(input_string);
 n = 0;
 for (i = 0; i < num_chars; i++)
 {
    if ((input_string[i] == '.') || (input_string[i] == '\n') || (input_string[i] == '\0') || (input_string[i] == '\r'))
       break;
    if  ((input_string[i] >= '0') &&  (input_string[i] <= '9'))
    {
       n = 10 * n + (input_string[i] - '0');
    }
 }
 return n;
}

int ignore_case_compare(char *s, char *t)
{
int i;


   for (i = 0; i < 70; i++)
   {
      if (((s[i] == '\0') || (t[i] == '\0')) &&
		   (strlen(s) == strlen(t)))
         return 0;
      else
      {
         if ((s[i] != ' ')  && (t[i] != ' '))
         {
            if ((s[i] != t[i]) &&
                (s[i] != (t[i] + 32)) &&  /* ignore case */
                (s[i] != (t[i] - 32)))    /* ignore case */
            {
               return -1;
            }
         }
      }
   }
   return 0;
}

int mycmp(char *s, char *t)  /* doesn't care about case */
{
int index;
char line_element_s[5][40] = {"", "", "", "", ""};
char line_element_t[5][40] = {"", "", "", "", ""};
int number_elements_s;
int number_elements_t;

int good_comparison = 0;

   /* first parse the strings and then just do a quick compare to see if they
      even have the same number of elements.  If they do, then compare each
      individual element of the name */

   parse_line(s, line_element_s, &number_elements_s, ' ');
   parse_line(t, line_element_t, &number_elements_t, ' ');

   if (number_elements_s == number_elements_t)
   {
      for (index = 0; index < number_elements_s; index++)
      {
         if (ignore_case_compare(line_element_s[index], line_element_t[index]) == -1)
         {
            good_comparison = -1;
            break;
         }
      }
   }
   else
   {
      good_comparison = -1;
   }

   return good_comparison;
}

int probability_compare(char *s, char *t)
{
int s_length, t_length;
int s_index, t_index;
int number_of_matching_characters = 0;
int probability_of_match;

   s_length = strlen(s);
   t_length = strlen(t);

   if ((s_length <= t_length + 3) && (s_length >= t_length - 3))
   {
      for (s_index = 0; s_index < s_length; s_index++)
      {
         for (t_index = 0; t_index < t_length; t_index++)
         {
            if ((is_alphabetic(s[s_index]) == -1) &&
                (s[s_index] == t[t_index]) &&
                ((s_index <= t_index + 3) && (s_index >= t_index - 3)))
            {
               number_of_matching_characters++;
               break;
            }
         }
      }
   }
   else
   {
      probability_of_match = 0;
   }

   if (number_of_matching_characters >= s_length - 2)
   {
      probability_of_match = -1;  /* 0 is a good match, -1 is not a match */
   }

   return probability_of_match;
}

int read_database_data(char *player_name, FILE *fp)
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
int first_name_length;


   fgets(player_string, 80, fp);

   if (strlen(player_string) > 3)
   {

      fprintf(test_output_file, "db_string = %s\n", player_string);

      parse_line(player_string, name_element, &number_elements, ',');

      strcpy(last_name, name_element[0]);
      last_name_length = strlen(last_name);
      if (last_name[last_name_length - 1] == ',')
         last_name[last_name_length - 1] = '\0';

      /* remove leading spaces from first name */
      /* also remove any newline type characters \n\r */
      first_name_length = strlen(name_element[1]);
      for (index = 0; index < first_name_length; index++)
      {
         if (((name_element[1][index] != ' ') ||
            ((name_element[1][index] == ' ') &&
             (index > 1))) &&
             (name_element[1][index] != '\n') &&
             (name_element[1][index]!= '\r'))

         {
            first_name[first_name_index] = name_element[1][index];
            first_name_index++;
         }
      }

      first_name[first_name_index] = '\0';

      strcpy(entire_name, first_name);

      strcat(entire_name, " ");
      /* append last name to entire_name */
      strcat(entire_name, last_name);

      fprintf(test_output_file, "Entire name in database = %s\n", entire_name);
      strcpy(player_name, entire_name);
      return 0;
   }
   else
      return -1;

}

void append_tour_player_to_db(struct database_data *player, struct player_info *tournament_player, int count, FILE *fp)
{
int found;
int index_found;
int probability_player_found;
int i;


   fprintf(test_output_file, "Comparing player %s\n", player->entire_name);

   /* the following code simply tries to do a string match of names */
   found = 0;
   for (i = 0; i < count; i++)
   {
      /*if (mycmp(player->entire_name, tournament_player[i].entire_name) == 0)*/
	  if (ignore_case_compare(player->entire_name, tournament_player[i].entire_name) == 0)
      {
         found = -1;
         index_found = i;
         break;
      }
   }

   if (found == -1)
     fprintf(fp, "%s\t%ld\n", player->entire_name,
                              tournament_player[index_found].money);

   else
      {
         /* attempt to match by different method - (parsing last and first names) */
         probability_player_found = 0;
         for (i = 0; i < count; i++)
         {
            if (mycmp(player->entire_name, tournament_player[i].entire_name) == 0)
            {
               fprintf(fp, "close match %s\t%ld\n", player->entire_name,
                                         tournament_player[i].money);
               probability_player_found = -1;
               break;
            }
         }
         if (probability_player_found == 0)
         {
            fprintf(fp, "%s\n", player->entire_name);
         }
      }

}

