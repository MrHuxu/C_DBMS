#include <stdio.h>
#include "explainSQL.h"

int main(int argc, char **argv)
{	
	char sql[100];
	do {
		printf("mysql> ");
		gets(sql);
	}
	while (explainSQL(sql));
	
	return 0;
}