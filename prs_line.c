#include <stdio.h>

void parse_line(char line[80], char element[20][40], int *num_elements, char delimiter)
{
int i, j;
int element_count;
char last_char;

element_count = 0;
i = 0;
j = 0;

last_char = '\0';

while((line[i] != '\0') && (line[i] != '\r') && (line[i] != '\n'))
  {
  if ((line[i] != delimiter) && (line[i] != '\0') && (line[i] != '\r') && (line[i] != '\n'))  /* non white space character */
    {
    if (last_char == delimiter)  /* indicates beginning of something new */
      {
      element_count++;
      j = 0;
      }
    element[element_count][j] = line[i];
    j++;
    }
  else  /* char is  whitespace */
    {
    if ((last_char != delimiter) && (last_char != '\0') && (last_char != '\r') && (last_char != '\n'))
      element[element_count][j] = '\0';  /* terminate with null */
    }
  last_char = line[i];
  i++;
  }
*num_elements = element_count + 1;
}
