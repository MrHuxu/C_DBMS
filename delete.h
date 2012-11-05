#include "structs.h"

void delete(char *edSql)
{
    FILE *pRead, *pWrite;
    int len = strlen(edSql);
    char temp[10];
    char tempAttribute[10];
    char tempValue[10];
    struct Table tmpTable[10];

    int i, j;
    for(i = 12, j = 0; i <= len && edSql[i] != '/'; i++, j++)
        temp[j] = edSql[i];                                     //��Ҫɾ��Ԫ��ı�
    temp[j] = '\0';
    for(i += 7, j = 0; i <= len && edSql[i] != '/'; i++, j++)
    	tempAttribute[j] = edSql[i];                            //�����жϵ�����
	tempAttribute[j] = '\0';
    for(i += 6, j = 0; i <= len && edSql[i] != '/'; i++, j++)
		tempValue[j] = edSql[i];                                //�����жϵ����Ե�ֵ
	tempValue[j] = '\0';
	
    int size, nRecord;
    	if ((pRead = fopen(temp, "rb"))) {
    		size = fgetc(pRead);
    		nRecord = fgetc(pRead);
    		fread(tmpTable, sizeof(struct Table), size, pRead);
    	}

	int mark;
	for (mark = 0; mark < size; mark++){
		if(tmpTable[mark].name == tempAttribute)
			break;
	}


	struct Attribute *pRecord = malloc(sizeof(struct Attribute) * size * 100);
			fread(pRecord, sizeof(struct Attribute) * size * nRecord, 1, pRead);
	fclose(pRead);

	int k;
			for (j = 0; j < nRecord; j++) {
				for (k = j * size; k < (j + 1) * size; k++){
					if(strcmp(pRecord[k].value, tempValue)== 0){
					pRecord[k].isDeleted = 'y';       //��ɾ����Ԫ��������жϵ�����isDeleted��Ϊy
					}
				}
			}
	if ((pWrite = fopen(temp, "wb"))) {
			fputc(size, pWrite);
			fputc(nRecord, pWrite);	
			fwrite(tmpTable, sizeof(struct Table), size, pWrite);
		fclose (pWrite);
		}
	
	if ((pWrite = fopen(temp, "ab"))) { 
		fwrite(pRecord, sizeof(struct Attribute) * size, nRecord, pWrite);	   
		fclose(pWrite);
		printf("The row is deleted successfully!\n");
	}
}

