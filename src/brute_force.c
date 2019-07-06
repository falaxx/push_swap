#include "push_swap.h"

char *next_try(char *try)
{
	int i = 0;
	int j = 0;

	while (try[i + 1] != '\0')
		i++;
	try[i] += 1;
	if (try[i] == 'd' && i == 0)
	{
		try[i + 1] = 'a';
		try[i] = 'a';
	}
	else if(try[i] == 'd' && i > 0)
	{
		try[i] = 'a';
		j = i - 1;
		try[j] += 1;
		while (try[j] == 'd' && j > 0)
		{
			try[j] = 'a';
			j--;
			try[j] += 1;
		}
		if (j == 0)
		{
			i = 0;
			while (try[i + 1] != '\0')
				i++;
			try[i + 1] = 'a';
		}
	}
	return (try);
}

t_p apply_try(char *str, t_p *p, int mode)
{
	int i = 0;
	while(str[i] != '\0')
		i++;
	while(i >= 0)
	{
		if (str[i] == 'a')
			*p = sa(p, mode);
		if (str[i] == 'b')
			*p = rra(p, mode);
		if (str[i] == 'c')
			*p = ra(p, mode);
		i--;
	}
	return (*p);
}

t_p brute_force(t_p *p)
{
	int i = 0;
	char *try = NULL;
	if (!(try = (char *)malloc(sizeof(char) * 20)))
		exit(0); //ft_exit
	ft_bzero(try, 20);
	try[0] = 'a';
	while(i < p->size)
	{
		p->clone[i] = p->a[i];
		i++;
	}
	if (is_sorted(p->size, p->a) == 1 && p->b[p->size -1] == 10000000000)
		ft_exit(p, 1);
	while(1)
	{
		while(i < p->size)
		{
			p->a[i] = p->clone[i];
			p->b[i] = 10000000000;
			i++;
		}
		i = 0;
		apply_try(try, p, 0);
		// printf("try = %s\n",try);
		if (is_sorted(p->size, p->a) == 1 && p->b[p->size -1] == 10000000000)
			break;
		i = 0;
		try = next_try(try);
		// sleep(1);
	}
	i = 0;

	while(i < p->size)
	{
		p->a[i] = p->clone[i];
		p->b[i] = 10000000000;
		i++;
	}
	// printf("%s",try);
	// exit(0);
	// if (try[0] != 'a' && try[1] != '\0')
	apply_try(try, p, 1);
	return(*p);
}
