#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "args.h"

void parse_args(int argc, char *argv[])
{
	char *temp;

	args.option_list = malloc(argc * 1024);
	args.count = 0;

	if (argc > 1) {
		for (int i = 1; i < argc; i++) {
			temp = argv[i];
			if (temp[0] == '-') {
				for (unsigned long j = 0; j < strlen(temp); j++) {
					args.option_list[args.count] = temp[j];
					args.count++;
				}
			}
		}
	}
}

void exec_args()
{
	for (int i = 0; i < args.count; i++) {
		switch (args.option_list[i]) {
			case 'h':
				printf("Usage: pnog -[hv]\n \
						\t-h\tShow this text.\n \
						\t-v\tPrint program version.\n");
				break;
			case 'v':
				printf("pnog version %s\n", VERSION);
				break;
			default:
				printf("pnog version %s\n", VERSION);
				break;
		}
	}
}

