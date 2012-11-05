#include "structs.h"

void project(char *edSql)
{
	FILE *pRead;
	int len = strlen(edSql);
	char temp[10];
	char attr[10][10];
	struct Table tmpTable[10];
	int size, nRecord;	
	int i, j, k, l;
	
	i = 7;
	k = 0;
	while (i < len) {
		if (edSql[i] == ',') {
			i += 2;
			continue;
		}
		for (j = 0; i <= len && edSql[i] != '/'; i++, j++)
    		temp[j] = edSql[i];   	
		temp[j] = '\0';
		i++;
			
		if (!strcmp(temp, "from"))
			break;
		strcpy(&attr[k][0], temp);
		k++;
	}

	for (j = 0; i <= len && edSql[i] != '/'; i++, j++)
    	temp[j] = edSql[i];   	
	temp[j] = '\0';
	i++;

	if ((pRead = fopen(temp, "rb"))) { 
		size = fgetc(pRead);
		nRecord = fgetc(pRead);		
		fread(tmpTable, sizeof(struct Table), size, pRead);	   
	}
		
	for (j = 0; j < size; j++) {
		for (l = 0; l < k; l++)
			if (!strcmp(tmpTable[j].name, &attr[l][0]))
				break;
		if (l < k)
			printf("%s\t", tmpTable[j].name);
	}
	printf("\n");
		
	struct Attribute *pRecord = malloc(sizeof(struct Attribute) * size * 100);
	fread(pRecord, sizeof(struct Attribute) * size * nRecord, 1, pRead);
		
	int nAttr = k;
	int deleted;
	for (j = 0; j < nRecord; j++) {
		deleted = 0;
		for (k = j * size; k < (j + 1) * size; k++) {
			if(pRecord[k].isDeleted == 'y')
				deleted = 1;
		}

		if(deleted == 1)
			continue;
		else{
		for (k = j * size; k < (j + 1) * size; k++) {
			
		for (l = 0; l < nAttr; l++) {
			if (!strcmp(pRecord[k].name, &attr[l][0]))
			if (l < nAttr)
				printf("%s\t", pRecord[k].value);
		}
		}
		}
		printf("\n");
	}	
}
