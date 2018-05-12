#include<stdio.h>
int sum(int x);
// main function, program starts from here

int main()
{
	int a = 5;
	int b = 0;
	b = sum(a);
	printf("%d", b);
}

int sum(int x)   // function definition
{
	int y;
	y = x + 5;
	return (y);
}