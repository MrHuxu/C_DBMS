#pragma once
void throwError(int errnum)
{
	switch (errnum) {
	case 0:
		printf("ERROR 0000: You have an error in your SQL syntax!\a\n");
		break;
	case 1:
		printf("ERROR 0001: This table already exists, please choose another name!\a\n");
		break;
	case 2:
		printf("ERROR 0002: This primary key conflicts with an existing one!\a\n");
		break;
	case 4:
		printf("ERROR 0004: The table doesn't exist!\a\n");
	}
}
