struct player_info
{
char entire_name[40];
long money;
};

struct database_data
{
char entire_name[40];
};

long string_to_integer(char input_string[]);
int read_player_data(FILE *fp);
int read_AP_data(FILE *fp);
int  read_database_data(char *player_name, FILE *fp);
void append_tour_player_to_db(struct database_data *player, struct player_info *tournament_player, int count, FILE *fp);
void parse_line(char line[80], char element[20][40], int *num_elements, char delimiter);
void fix_last_name(char broken[20], char fixed[20]);
void fix_first_name(char broken[20], char fixed[20]);
int mycmp(char *s, char *t);
int ignore_case_compare(char *s, char *t);
int probability_compare(char *s, char *t);
int is_alphabetic(char s);
