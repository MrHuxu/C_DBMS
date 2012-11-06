#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "throwError.h"

void createTable(char *edSql)
{
	FILE *pWrite, *pRead;
	int len=strlen(edSql);
    char temp[10];
	char tableName[10];
	struct Table table[10];
	int i, j, k, l;
	
	for (i = 13, j = 0; i <= len && edSql[i] != '/'; i++, j++)
    	temp[j] = edSql[i];   	
	temp[j] = '\0';	
	
	i++;
	strcpy(tableName, temp);
	if ((pRead = fopen(tableName, "rb"))) {
		throwError(1);
		fclose(pRead);
		return;
	}
	
	if (edSql[i] == '(') {
		i = i + 2;
		k = 0;
        while (i <= len && edSql[i] != ';') {
			l = i;
			for (j = 0; l <= len && edSql[l] != '/'; j++, l++)
    			temp[j] = edSql[l];
			temp[j] = '\0';
					
			strcpy(table[k].name, temp);
			l++;					
			for (j = 0; l <= len && edSql[l] != '/'; j++, l++)
    			temp[j] = edSql[l];
			temp[j] = '\0';
			
			if (!strcmp(temp, "int")) {
				table[k].type = 0;
				table[k].length = 4; //int：4 byte
				l++;
			} 
			else if (!strcmp(temp, "float")) {
				table[k].type = 1;
				table[k].length = 4; //float：4 byte
				l++;
			} 
			else if (!strcmp(temp, "char")) {
             	table[k].type = 2;
				l++;
				if (edSql[l] == '(') {
					l += 2;
                    for (j = 0; l <= len && edSql[l] != '/'; j++, l++)
    					temp[j] = edSql[l];
					temp[j] = '\0';
					         
                    table[k].length = atoi(temp);
					l++;
				}		
				if (edSql[l] == ')') {
					l += 2;
                }
			}
			
			if (edSql[l] == ')') {
					k++;
					i = l + 2;
					break;
			} 
			else if (edSql[l] == ',') {
				k++;
				i = l + 2;
			}
		}

		if ((pWrite = fopen(tableName, "wb"))) {
			fputc(k, pWrite);
			fputc(0, pWrite);	
			fwrite(table, sizeof(struct Table), k, pWrite);		   
		    fclose(pWrite);
			printf("Table <%s> is created successfully!\n", tableName);
		}
	}
}
