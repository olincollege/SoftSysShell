char **get_input(char *input,char *seperator);
int cd(char *);
void send_output(char *input, char *path);
int redirection_check(char *input);
void redirect_out(char *file_name);
void redirect_out_append(char *file_name);
char *trim(char *str);
void print_history();
void redirect_command(int redirect, int saved_stdout, char **command_and_file, char *input);