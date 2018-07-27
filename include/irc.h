/*
** EPITECH PROJECT, 2018
** My IRC
** File description:
** irc header file
*/

#ifndef IRC_H_
#define IRC_H_

#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <time.h>

typedef struct s_p_msg p_msg_t;
typedef struct s_channel channel_t;
typedef struct s_msg msg_t;
typedef struct s_client client_t;
typedef struct s_c_client c_client_t;

typedef struct sockaddr_in sockadd_t;
typedef struct sockaddr* sockadd_p;
typedef struct timeval xtime;

#define TIMEOUT 1;
#define len(x) sizeof(x)
#define error_handle(msg) do {perror(msg); exit(EXIT_FAILURE);} while (0)
#define ip(x) inet_ntoa(x)
#define CLIENT_NUMBER 42
#define unused(x) (void)x
#define CBUFF_SIZE 2048

typedef struct s_buff {
	char *buffer;
	char *used;
	int used_size;
	int write;
	int read;
}buffer_t;

typedef struct server {
	int fd;
	fd_set rfds;
	int max_fd;
	int cfd;
	sockadd_t sin;
	channel_t *channel;
	client_t *client;
} server_t;

struct s_p_msg {
	struct s_p_msg* next;
	struct s_p_msg* prev;
	char *name;
	msg_t *msgs;
};

struct s_channel {
	struct s_channel* next;
	struct s_channel* prev;
	msg_t *msgs;
	char *c_name;
	c_client_t *clients;
};

struct s_msg {
	struct s_msg* next;
	struct s_msg* prev;
	client_t *client;
	char *msg;
};

struct s_client {
	struct s_client* next;
	struct s_client* prev;
	int fd;
        char *name;
	char *username;
	int is_logged;
	int is_registered;
	p_msg_t *p_msg;
	channel_t* channel;
	buffer_t *sen_b;
	buffer_t *rec_b;
};

struct s_c_client {
	struct s_c_client *next;
	struct s_c_client *prev;
	client_t *client;
};

typedef struct s_list {
	struct s_list* next;
	struct s_list* prev;
}list_t;

typedef struct s_cmd{
	char *command;
	void (*fct)(client_t*, char**, server_t*);
}cmd_t;

void usage(char *);

//list creation
channel_t *new_channel(char *);
p_msg_t *new_pmsg(char *);
msg_t *new_msg(client_t *, char *);
client_t *new_client(int, channel_t*);
c_client_t *new_channel_client(client_t *);

//list editing
void *l_add(void *, void *);
void l_remove(void **, int);
void l_clean(void **);

//tools
int is_digit(char);
int is_number(char *);
char *add_str(char **, char *);
char **split(char *, char *);
void display(client_t *client, char **cmd, server_t *server);
char *trim(char *str);
char * reform(char **cmd);

//tools list
int get_client_channel_id(client_t *, c_client_t *);
channel_t *get_channel_from_name(char *, channel_t *);
client_t *get_client_by_fd(client_t *, int);
int get_client_fd(client_t *, char *);

//server fucntions
int s_socket(server_t*);
int s_bind(int *, server_t*);
int s_listen(server_t*);
int s_accept(server_t*);
int make_server(int *, server_t*);
int s_init(char*, server_t**);
int s_run(server_t **);
int s_select(server_t*);
int s_catch_client(server_t**);
int s_add_clients_fd(server_t *);
void handle_fds(server_t *);
void accept_and_receive(server_t *, int *);
void s_run_cmd(server_t*, char *, int);

//server cmd
void s_list(client_t *, char **, server_t *);
void s_join_channel(client_t *, char **, server_t *);
void s_part_channel(client_t *, char **, server_t *);
void s_users(client_t *, char **, server_t *);
void c_nick(client_t *, char **, server_t *);
void c_names(client_t *, char **, server_t *);
void c_msg(client_t *, char **, server_t *);
void c_next_channel(client_t *, char **, server_t *);
void c_previous_channel(client_t *, char **, server_t *);
void s_diffuse(server_t*, char*, int);
int valid_nick(client_t *, char *);
char *pick_random(const char *);
int check_client(client_t *, char *, char *);
int register_client(client_t *, char *);
void count_letters(int *, int *, char **);
void accept_and_receive(server_t*, int*);
void run(server_t*, client_t*, char **, char*, int);
void s_run_cmd(server_t *, char *, int);
char *get_channel_text(channel_t *);

//server io
int s_send(client_t *, char *);
char *s_receive(client_t *);
int send_rest(client_t *client);

//data structures

static const cmd_t cmd[9] = {{"/list", s_list}, {"/join", s_join_channel}, {"/part", s_part_channel},
			     {"/users", s_users}, {"/nick", c_nick}, {"/names", c_names},
			     {"/msg", c_msg}, {"/next", c_next_channel}, {"/prev", c_previous_channel}};


#endif /* IRC_H_ */
