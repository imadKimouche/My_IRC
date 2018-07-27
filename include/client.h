/*
** EPITECH PROJECT, 2018
** My IRC
** File description:
** client
*/

#ifndef CLIENT_H_
#define CLIENT_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <gtk/gtk.h>
#include <sys/stat.h>

typedef struct sockaddr_in sockadd_t;
typedef struct sockaddr* sockadd_p;
typedef struct s_client client_t;

#define error_handle(msg) do {perror(msg); exit(EXIT_FAILURE);} while (0)
#define unused(x) (void)x
#define TRANSFER_PORT 6969
#define NB_SMILEY 13

extern client_t client_inf;


typedef struct s_window {
	GtkTextView *textView;
	GtkEntry *textType;
} window_t;

typedef struct s_smiley {
	char *name;
	char *pic;
} smiley_t;

struct s_client {
	int fd;
	int state;
	window_t window;
	char *received;
	int r_size;
	char *file;
};

//file handle
int try_send_file(char **cmd, char *line);
int send_file(char **cmd, client_t *client);

//local cmd
void handle_input_cmd(void);
void c_input_cmd(char *buff, client_t *client);
void handle_output_cmd(char *lines, client_t *client);

//client
void c_start_input_captation(client_t *client);
void start_client(int ac, char **av);

//gui
void start_gui(int ac, char **av);
GdkPixbuf *get_smiley(char *name);

//gui_w_main
GtkWidget *g_m_top(void);
GtkWidget *g_m_mid(void);

//actions
void a_send(GtkWidget *widget, gpointer data);

//tools
gchar *c_get_text(GtkEntry *textType);
char **split(char *line, char *delimiters);

//clien_IO
int c_send(char *msg);
char *c_receive(void);
void c_connect(int port, char *addr);
void c_disconnect(void);

static const smiley_t arr_smiley[NB_SMILEY] = {{":)", "smile.png"}, {"aaah", "aah.png"},
	{"chaud", "chaud.png"}, {"epitech", "epitech.png"}, {"fu", "fu.png"},
	{"nassim", "nassim.png"}, {"non", "non.png"}, {"think", "think.png"},
	{"tkt", "tkt.png"}, {"wtf", "wtf.png"}, {"jd", "jd.png"},
	{"imad", "imad.png"}, {"anthony", "anthony.png"}};

#endif
