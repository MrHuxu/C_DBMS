#include "structs.h"

void describe(char *edSql)
{
	FILE *pRead;
	int len=strlen(edSql);
	char tableName[10];	
	struct Table tmpTable[10];
	
	int i, j;
	for (i = 9, j = 0; i <= len && edSql[i] != '/'; i++, j++)
    	tableName[j] = edSql[i];   	
	tableName[j] = '\0';
	
	int size;
	if ((pRead = fopen(tableName, "rb"))) { 
		size = fgetc(pRead);	
		fgetc(pRead);		
		fread(tmpTable, sizeof(struct Table) * size,1 , pRead);		   
		fclose(pRead);
	}
		
	printf("%s(", tableName);
	for (i = 0; i < size; i++) {
		printf("%s ", tmpTable[i].name);
		switch (tmpTable[i].type) {
		case 0: 
			printf("int");
			break;			
		case 1:
			printf("float");
			break;
		case 2:
			printf("char(%d)", tmpTable[i].length);
			break;
		}
		if (i < size - 1)
			printf(", ");
	}
	printf(");\n");
}
