#include "structs.h"
#include "join.h"
#include "project.h"

void mySelect(char *edSql)
{
	FILE *pRead;
	int len = strlen(edSql);
	char temp[10];	
	struct Table tmpTable[10];
	
	int i, j;
	i = 7;
	if (edSql[i] == '*') {
		i += 2;
		for (j = 0; i <= len && edSql[i] != '/'; i++, j++)
    		temp[j] = edSql[i];   	
		temp[j] = '\0';
		i++;
		
		if (!strcmp(temp, "from")) {
			for (j = 0; i <= len && edSql[i] != '/'; i++, j++)
    			temp[j] = edSql[i];   	
			temp[j] = '\0';
			i++;
			
			if (edSql[i] == ',') {
				join(edSql);
				return;
			}
			
			int size, nRecord;
			if ((pRead = fopen(temp, "rb"))) { 
				size = fgetc(pRead);
				nRecord = fgetc(pRead);		
				fread(tmpTable, sizeof(struct Table), size, pRead);	   
			}
			
			for (j = 0; j < size; j++)
				printf("%s\t", tmpTable[j].name);
			printf("\n");
			
			struct Attribute *pRecord = malloc(sizeof(struct Attribute) * size * 100);
			fread(pRecord, sizeof(struct Attribute) * size * nRecord, 1, pRead);
			
			int k, mark;
			for (j = 0; j < nRecord; j++) {
				mark = 0;
				for (k = j * size; k < (j + 1) * size; k++){
					if(pRecord[k].isDeleted == 'y')
						mark = 1;
				}
				
				if (mark == 1)
					continue;
				else	{
					for (k = j * size; k < (j + 1) * size; k++)	{
						printf ("%s\t", pRecord[k].value);
					}
				}
				printf("\n");
			}
		}
	}
	else 
		project(edSql);
}
