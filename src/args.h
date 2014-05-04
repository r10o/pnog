#ifndef PNOG_ARGS
#define PNOG_ARGS

typedef struct Args {
	char *option_list;
	int count;
} Args_t;

void parse_args(int, char **);
void exec_args();

Args_t args;

#endif

