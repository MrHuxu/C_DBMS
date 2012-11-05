#pragma once

struct Table
{
	char name[10];
	unsigned int type; //int:0 float:1 char:2
	unsigned int length;
};


struct Attribute
{
	char name[10];
	char value[10];
	char isDeleted;
};
