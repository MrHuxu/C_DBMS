/* 
 * File:   drop.h
 * Author: huxu
 *
 * Created on 2012年10月22日, 下午12:34
 */

#ifndef DROP_H
#define	DROP_H

void drop(char *edSql){
    char temp[10];
    int len = strlen(edSql);
    
    int i, j;
    for(i = 11, j = 0; i <= len && edSql[i] != '/'; i++, j++)
        temp[j] = edSql[i];  
	temp[j] = '\0';
	
    if(remove(temp) == 0)
        printf("The table is deleted successfully!\n");
	else
		throwError(4);
}
#endif	/* DROP_H */

