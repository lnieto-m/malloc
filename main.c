#include "ft_malloc.h"
// #include <stdlib.h
#include <stdio.h>

int main(void)
{

	printf("%d\n", (((5000 + 24 + 31) / 4096) * 4096) + 4096);

	char *str;
	int i = 0;

	// str = NULL;
	str = (char *)malloc(4096);
	if (!str)
		return (printf("bjr vc rep\n"));
	while (i < 4096)
	{
		str[i] = 'i';
		write(1, &str[i], 1);
		i++;
	}
	// // munmap((void *)str, 1 * sizeof(char));
	// str[1] = '2';
	// str[2] = 'r';
	// str[3] = 0;
	// str[4] = 0;
	// // printf("%s\n", str);
	// // printf("%s\n",g_);
	// // printf("%s\n",str);
	return (0);
}
