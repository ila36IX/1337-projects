#include "get_next_line.h"
char	*ft_strdup(const char *src)
{
	char	*str;
	int		i;

	i = 0;
	while (src[i])
		i++;
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (*src)
		str[i++] = *src++;
	str[i] = '\0';
	return (str);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static size_t	ft_calc_sz(char const *s1, char const *s2)
{
	size_t	size;

	size = 0;
	if (s1)
		size += ft_strlen(s1);
	if (s2)
		size += ft_strlen(s2);
	return (size + 1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*buff;

	buff = malloc(sizeof(char) * (ft_calc_sz(s1, s2)));
	if (!buff)
		return (NULL);
	i = 0;
	j = 0;
	if (s1)
		while (s1[j])
			buff[i++] = s1[j++];
	j = 0;
	if (s2)
		while (s2[j])
			buff[i++] = s2[j++];
	buff[i] = '\0';
	return (buff);
}

/*char *ft_substr_ptr(char const *start, char const *end)*/
/*{*/
/*	char *str;*/
/*	int i;*/
/**/
/*	if (start > end || !start || !end)*/
/*		return (NULL);*/
/*	str = malloc(sizeof(char) * (end - start + 1));*/
/*	if (!str)*/
/*		return (NULL);*/
/*	i = 0;*/
/*	while (start <= end)*/
/*		str[i++] = *(start++);*/
/*	str[i] = '\0';*/
/*	return (str);*/
/*}*/
char *ft_substr_ptr(char const *start, char const *end)
{
	size_t len;
	char *str;
	size_t i;

	if (!start || !end || end < start)
		return (NULL);
	len = end - start + 1;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
		str[i++] = *start++;
	str[len] = '\0';
	return (str);
}
