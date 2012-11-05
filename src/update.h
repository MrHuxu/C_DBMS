#include "structs.h"
#include "throwError.h"

void update(char *edSql)
{
        FILE *pRead;
	int len = strlen(edSql);
	char temp[10];	
	struct Table tmpTable[10];
	char name[20];
	char name1[20];
	char value[20];
	char value1[20];
	
int i, j;
	for (i = 7, j = 0; i <= len && edSql[i] != '/'; i++, j++)
    	temp[j] = edSql[i];   	
	temp[j] = '\0';
	i++;   
	int size, nRecord;
	if ((pRead = fopen(temp, "rb"))) { 
		size = fgetc(pRead);
		nRecord = fgetc(pRead);		
		fread(tmpTable, sizeof(struct Table), size, pRead);	   
	}
	struct Attribute *pRecord = malloc(sizeof(struct Attribute) * size * nRecord);
	fread(pRecord, sizeof(struct Attribute) * size * nRecord, 1, pRead);
        fclose(pRead);

    	int k=0;
	int z=0,c=0;
	for(i=i-1;i<len;i++){
	if(edSql[i]=='/') k++;
	if(k==2) {name1[z]=edSql[i+1]; z++;}		//提取更改属性的name								
	else if(k==4) {value1[c]=edSql[i+1];c++;}       //提取更改属性的value
	else if(k==5) {z--;c--;break;}
	}
	name1[z]='\0';
	value1[c]='\0';
	i=i+7;
	
	int w;
	for(w=0;edSql[i+w]!='/';w++){
	name[w]=edSql[i+w];           //提取条件属性的name
	}
	i=i+w+3;
	int v;
	for(v=0;edSql[i+v]!='/';v++) {
	value[v]=edSql[i+v];          //提取条件属性的value
	}
	value[v]='\0';
	name[w]='\0';
        int q,p,g;

	int mark, m, n, deleted1, deleted2;
	for(q=0;q<nRecord;q++) {
		deleted1 = 0;
		for(p = q * size; p < (q + 1) * size; p++){
            if(pRecord[p].isDeleted == 'y')
				deleted1 = 1;
		}
		if(deleted1 == 1){
			continue;
		}else{
		for(p=q*size;p<(q+1)*size;p++) {
			if(strcmp(pRecord[p].name,name)==0) {
				if(p == q * size){
				if(strcmp(pRecord[p].value,value)==0) {
					for(g=q*size;g<(q+1)*size;g++) {
						 if(strcmp(pRecord[g].name,name1)==0) {
							strcpy(pRecord[g].value,value1);     //找出所需更改的内容，将新内容复制  
						}
					}
				}
				}else {
					if(strcmp(pRecord[p].value,value)==0) {
					for(g=q*size;g<(q+1)*size;g++) {
						 if(strcmp(pRecord[g].name,name1)==0) {
							 if(g != q * size)
							strcpy(pRecord[g].value,value1);//找出所需更改的内容，将新内容复制
							 else{mark = 0;
								 for(m = 0; m < nRecord; m++){
									 deleted2 = 0;
									for(n = m * size; n < (m + 1) * size; n++){
										if(pRecord[n].isDeleted == 'y')
											deleted2 = 1;
									}
									if(deleted2 == 1)
										 continue;
									 else{
										 if(strcmp(pRecord[m * size].value, value1) == 0)
											 mark = 1;
									 }
								 }
								 if(mark == 1){
									 throwError(2);
									 goto out1;
								 }
								 else
									 strcpy(pRecord[g].value,value1);
							 }
						}
					}
				}
				
			}
		}
	}
	}
	}
		
out1:	if ((pRead = fopen(temp, "wb"))) { 
		fputc(size,pRead);
		fputc(nRecord,pRead);		
		fwrite(tmpTable, sizeof(struct Table), size, pRead);	   
	}
	fwrite(pRecord, sizeof(struct Attribute) * size * nRecord, 1, pRead);
	fclose(pRead);
	/*
	   update student set age = 20 where name = hyq;
	   select * from student
	*/

}
