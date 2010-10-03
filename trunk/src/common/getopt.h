#ifndef _GETOPT_H__
#define _GETOPT_H__

#include "hashtable.h"
#include "dgc_vector.h"

typedef struct getopt_option getopt_option_t;

struct getopt_option
{
	char *sname;
	char *lname;
	const char *svalue;

	char *help;
	int type;
	
	int spacer;
};

typedef struct getopt getopt_t;

struct getopt
{
	hashtable_t *lopts;
	hashtable_t *sopts;
	dgc_vector_t *extraargs;
	dgc_vector_t *options;
};

getopt_t *getopt_create();
void getopt_destroy(getopt_t *gopt);

int getopt_parse(getopt_t *gopt, int argc, char *argv[], int showErrors);
void getopt_do_usage(getopt_t *gopt);

void getopt_add_spacer(getopt_t *gopt, const char *s);
void getopt_add_bool(getopt_t *gopt, char sopt, const char *lname, int def, const char *help);
void getopt_add_int(getopt_t *gopt, char sopt, const char *lname, const char *def, const char *help);
void getopt_add_string(getopt_t *gopt, char sopt, const char *lname, const char *def, const char *help);

const char *getopt_get_string(getopt_t *gopt, const char *lname);
int getopt_get_int(getopt_t *getopt, const char *lname);
int getopt_get_bool(getopt_t *getopt, const char *lname);


#endif
