#include "createTable.h"
#include "describe.h"
#include "delete.h"
#include "error.h"
#include "insert.h"
#include "mySelect.h"
#include "update.h"
#include "drop.h"

int isNum(char c)
{
	if (c >= '0' && c <= '9')
		return 1;
	else
		return 0;
}

int isAlpNum(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')
		return 1;
	else
		return 0;
}

int explainSQL(char *sql)
{
	char edSql[100];
	int len = strlen(sql);
	int i, j, k, m;
	
	i = j = k = 0;
	while (i <= len) {
		for (; sql[i] == ' ' && i <= len; i++);
		for (j = i; j <= len && isAlpNum(sql[j]); j++, k++)
			edSql[k] = sql[j];
						
		if (sql[j] == '.') {
			for (m = i; m < j && isNum(sql[m]); m++);	
			if (m == j) {
				edSql[k] = '.';
				k++;
				m++;
				for (; m <= len && isNum(sql[m]); m++, k++)
					edSql[k] = sql[m];
				j = m;
			}
		}
		
		edSql[k] = '/';
		k++;
		for (; sql[j] == ' ' && j <= len; j++);		
		while (j <= len && (!isAlpNum(sql[j])) && sql[j] != ' ') {
			   edSql[k] = sql[j];
			   if (edSql[k] == '>') {
				   if ((j + 1) <= len && sql[j + 1] == '=') {
					   k++;
					   j++;
					   edSql[k] = sql[j];
				   }
			   }
			   else if (edSql[k] == '<') {
				   if ((j + 1) <= len && sql[j + 1] == '=') {
					   k++;
					   j++;
					   edSql[k] = sql[j];
				   }
				   else if ((j + 1) <= len && sql[j + 1] == '>') {
					   k++;
					   j++;
					   edSql[k] = sql[j];
				   }
			   }
		       j++;
			   k++;
			   edSql[k] = '/';
	           k++;
		}
		for (; sql[j] == ' ' && j <= len; j++);
		i=j;
	}
	edSql[k] = '\0';
	
	if (len) {
		switch (edSql[0]) {
		case 'c':
			if (edSql[1] == 'r' && edSql[2] == 'e' && edSql[3] == 'a' && edSql[4] == 't' && edSql[5] == 'e' && edSql[6] == '/')
				createTable(edSql);
			else
				throwError(0);			
			break;
		case 'd':
			if (edSql[1] == 'e' && edSql[2] == 's' && edSql[3] == 'c' && edSql[4] == 'r' && edSql[5] == 'i' && edSql[6] == 'b' &&
					edSql[7] == 'e' && edSql[8] == '/')
				describe(edSql);
			else if (edSql[1] == 'e' && edSql[2] == 'l' && edSql[3] == 'e' && edSql[4] == 't' && edSql[5] == 'e' && edSql[6] == '/')
				delete (edSql);	
			else if (edSql[1] == 'r' && edSql[2] == 'o' && edSql[3] == 'p' && edSql[4] == '/')
                drop(edSql);
			else
				throwError(0);	
			break;
		case 'e':
			if (edSql[1] == 'x' && edSql[2] == 'i' && edSql[3] == 't' && edSql[4] == '/') {
				printf("Bye\n");	
				return 0;			
			}
			else
				throwError(0);
			break;
		case 'i':
			if (edSql[1] == 'n' && edSql[2] == 's' && edSql[3] == 'e' && edSql[4] == 'r' && edSql[5] == 't' && edSql[6] == '/')
				insert(edSql);			
			else
				throwError(0);
			break;
		case 's':
			if (edSql[1] == 'e' && edSql[2] == 'l' && edSql[3] == 'e' && edSql[4] == 'c' && edSql[5] == 't' && edSql[6] == '/')
				mySelect(edSql);			
			else
				throwError(0);
			break;
       	case 'u':
			if (edSql[1] == 'p' && edSql[2] == 'd' && edSql[3] == 'a' && edSql[4] == 't' && edSql[5] == 'e' )
				update(edSql);			
			else
				throwError(0);
			break;
		default:
			throwError(0);
		}
	}
	
	return 1;
}
