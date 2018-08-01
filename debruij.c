/*
* @Author: carl
* @Date:   2018-08-01 13:59:34
* @Last Modified by:   carl
* @Last Modified time: 2018-08-01 16:02:27
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int help(int ret_val)
{
	printf("debruij: usage: ./debruij (alpha with no repetitions) (key_length > 0)");
	return (ret_val);
}

int my_strlen(const char const * str)
{
	unsigned long int i = 0;

	if (str == NULL)
		return (0);
	for (; str[i] != '\0'; ++i);
	return (i);
}

void key_begin(char *res, int len, const char const * alpha)
{
	for (unsigned long int i = 0; i < len; ++i)
		res[i] = alpha[0];
}

char *charcat(const char const *str, char c)
{
	char *res = malloc(sizeof(char) * my_strlen(str) + 2);
	unsigned long int i = 0;

	for (; str && str[i] != '\0'; ++i)
		res[i] = str[i];
	res[i] = c;
	res[i + 1] = '\0';
	return (res);
}

void addchar(char *str, char c, unsigned long int *i)
{
	str[*i] = c;
	str[*i + 1] = '\0';
	(*i)++;
}

unsigned long int count_occurence(const char const * str, char c)
{
	unsigned long int i = 0;

	for (; str[i] !='\0' && str[i] == c; ++i);
	return (i);
}

int key(const char const *alpha, char *res, unsigned long int it, unsigned long int len)
{
	char *tmp = NULL;

	for (int i = 0; alpha[i] != '\0'; ++i) {
		tmp = charcat(&res[it - (len - 1)], alpha[i]);
		if (strstr(res, tmp) == NULL)
			addchar(res, alpha[i], &it);
		free(tmp);
		tmp = NULL;
		tmp = charcat(&res[it - (len - 1)], alpha[i]);
		if (strstr(res, tmp) == NULL &&
			count_occurence(&res[it - (len - 1)], alpha[i]) == len - 1)
			addchar(res, alpha[i], &it);
		free(tmp);
		tmp = NULL;
	}
	return (it);
}

char *genrate_key(const char const *alpha, int len)
{
	unsigned long int max_len = pow(my_strlen(alpha), len);
	// printf("%ld\n", max_len);
	char *res = malloc(sizeof(char) * (max_len + 1));
	unsigned long int it = len;

	if (res == NULL)
		return (NULL);
	res[it] = '\0';
	key_begin(res, len, alpha);
	while ((it = key(alpha, res, it, len)) != max_len) {
		// printf("%lld == %lld\n", it, max_len);
	}
	return (res);
}

int main(int ac, char **av)
{
	char *key = NULL;

	if (ac < 3)
		return help(84);
	int key_len = atoi(av[2]);

	if (key_len == 0) {
		return help(0);
	}
	key = genrate_key(av[1], key_len);
	printf("%s\n", key == NULL ? "NULL" : key);
	free(key);
	return (0);
}