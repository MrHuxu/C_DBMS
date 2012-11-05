#include "structs.h"

void join(char *edSql)
{
	FILE *pRead;
	int len = strlen(edSql);
	char temp[20];
	char attr1[20], attr2[20];
	char tableName1[20], tableName2[20];
	struct Table table1[10];
	struct Table table2[10];
	int size1, nRecord1;
	int size2, nRecord2;
	int i, j, k;
	
	i = 14;
	for (j = 0; i <= len && edSql[i] != '/'; i++, j++)
    	tableName1[j] = edSql[i];   	
	tableName1[j] = '\0';
	i++;
	
	if ((pRead = fopen(tableName1, "rb"))) { 
		size1 = fgetc(pRead);
		nRecord1 = fgetc(pRead);		
		fread(table1, sizeof(struct Table), size1, pRead); 
	}
	
	struct Attribute *pRecord1 = malloc(sizeof(struct Attribute) * size1 * nRecord1);
	fread(pRecord1, sizeof(struct Attribute) * size1 * nRecord1, 1, pRead);
	
	i += 2;
	for (j = 0; i <= len && edSql[i] != '/'; i++, j++)
    	tableName2[j] = edSql[i];   	
	tableName2[j] = '\0';
	i++;

	if ((pRead = fopen(tableName2, "rb"))) { 
		size2 = fgetc(pRead);
		nRecord2 = fgetc(pRead);		
		fread(table2, sizeof(struct Table), size2, pRead);
	}

	struct Attribute *pRecord2 = malloc(sizeof(struct Attribute) * size2 * nRecord2);
	fread(pRecord2, sizeof(struct Attribute) * size2 * nRecord2, 1, pRead);	
	
	for (j = 0; i <= len && edSql[i] != '/'; i++, j++)
    	temp[j] = edSql[i];   	
	temp[j] = '\0';
	i++;
	for (j = 0; i <= len && edSql[i] != '/'; i++, j++)
    	temp[j] = edSql[i];   	
	temp[j] = '\0';
	i++;
	for (j = 0; i <= len && edSql[i] != '/'; i++, j++)
    	temp[j] = edSql[i];   	
	temp[j] = '\0';
	i++;
	for (j = 0; i <= len && edSql[i] != '/'; i++, j++)
    	attr1[j] = edSql[i];   	
	attr1[j] = '\0';
	i++;
	for (j = 0; i <= len && edSql[i] != '/'; i++, j++)
    	temp[j] = edSql[i];   	
	temp[j] = '\0';
	i++;
	for (j = 0; i <= len && edSql[i] != '/'; i++, j++)
    	temp[j] = edSql[i];   	
	temp[j] = '\0';
	i++;
	for (j = 0; i <= len && edSql[i] != '/'; i++, j++)
    	temp[j] = edSql[i];   	
	temp[j] = '\0';
	i++;
	for (j = 0; i <= len && edSql[i] != '/'; i++, j++)
    	attr2[j] = edSql[i];   	
	attr2[j] = '\0';
	i++;
	int pos1, pos2;
	for (j = 0; j < size1; j++) {
		pos1 = j;
		if (!strcmp(table1[j].name, attr1))
			break;
	}
	for (j = 0; j < size2; j++) {
		pos2 = j;
		if (!strcmp(table2[j].name, attr2))
			break;
	}
	for (j = 0; j < size1; j++)
		printf("%s\t", table1[j].name);
	for (j = 0; j < size2; j++)
		printf("%s\t", table2[j].name);
	printf("\n");

	int m, n;
	for (j = 0; j < nRecord1; j++) {
		for (m = 0; m < nRecord2; m++) {
			if (!strcmp(pRecord1[j * size1 + pos1].value, pRecord2[m * size2 + pos2].value)) {
				for (k = j * size1; k < (j + 1) * size1; k++)
					printf("%s\t", pRecord1[k].value);
				for (n = m * size2; n < (m + 1) * size2; n++)
					printf("%s\t", pRecord2[n].value);
				printf("\n");
			}
		}
	}
}
