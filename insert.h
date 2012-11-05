#include "structs.h"
#include "throwError.h"

void insert(char *edSql)
{
	FILE *fp;
	int len = strlen(edSql);
	char temp[10];	
	char tableName[10];
	struct Table tmpTable[10];
	
	int i, j;
	for (i = 12, j = 0; i <= len && edSql[i] != '/'; i++, j++)
    	tableName[j] = edSql[i];   	
	tableName[j] = '\0';
	i++;

	int size, nRecord;
	if ((fp = fopen(tableName, "rb+"))) { 
		size = fgetc(fp);
		nRecord = fgetc(fp);
		fread(tmpTable, sizeof(struct Table), size, fp);
	}
	
	int k;
	struct Attribute *pRecord = malloc(sizeof(struct Attribute) * size);
	if (edSql[i] == '(') {
		i += 2;
		k = 0;
		while (i < len) {
			if (edSql[i] == ')') {
				i += 2;
				break;
			}
			if (edSql[i] == ',') {
				i += 2;
				continue;
			}
			for (j = 0; i <= len && edSql[i] != '/'; i++, j++)
    			temp[j] = edSql[i];   	
			temp[j] = '\0';
			i++;
			
			strcpy(pRecord[k].name, temp);
			k++;
		}
	}
	else
		for (k = 0; k < size; k++)
			strcpy(pRecord[k].name, tmpTable[k].name);
	
	for (j = 0; i <= len && edSql[i] != '/'; i++, j++)
    	temp[j] = edSql[i];   	
	temp[j] = '\0';
	i++;
	
	if (!strcmp(temp, "values")) {
		if (i < len) {
			if (edSql[i] == '(') {
				i += 2;
				k = 0;
				while (i < len) {
					if (edSql[i] == ')')
						break;
					if (edSql[i] == ',') {
						i += 2;
						continue;
					}
					for (j = 0; i <= len && edSql[i] != '/'; i++, j++)
    					temp[j] = edSql[i];   	
					temp[j] = '\0';
					i++;

					strcpy(pRecord[k].value, temp);
					k++;
				}
			}
		}
	}

	struct Attribute *pExistRecord = malloc(sizeof(struct Attribute) * size * 100);
			fread(pExistRecord, sizeof(struct Attribute) * size * nRecord, 1, fp);

	int deleted, mark;
	mark = 0;
	for(i = 0; i < nRecord; i++){
		deleted = 0;
       for (j = i * size; j < (i + 1) * size; j++){
			if(pExistRecord[j].isDeleted == 'y'){
				deleted = 1;
			}
	   }
		if(deleted == 1)
			   continue;
		else{
			if(strcmp(pExistRecord[i * size].value, pRecord[0].value) == 0)
			mark = 1;
		}
	}

	if(mark == 1){
		throwError(2);
		return;
	}
	else{

	fseek(fp, 1, SEEK_SET);
	fputc(nRecord + 1, fp);
	fclose(fp);

		int l;
	if (k < size) 
		for (j = 0; j < size; j++) {
			for (l = 0; l < k; l++)	
				if (!strcmp(tmpTable[j].name, pRecord[l].name))
					break;
			if (l == k) {
				strcpy(pRecord[k].name, tmpTable[j].name);
				strcpy(pRecord[k].value, "null");
				k++;
			}
		}
		
	if ((fp = fopen(tableName, "ab"))) { 
		fwrite(pRecord, sizeof(struct Attribute) * size, 1, fp);	   
		fclose(fp);
		printf("This piece of record is inserted successfully!\n");
	}
	}
}
