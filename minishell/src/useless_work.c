
int	bs_sections(char *del)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (del[i])
	{
		while (del[i] == '\\' && del[i])
			i++;
		if (del[i - 1] == '\\' && del[i])
			count++;
		while (del[i] != '\\' && del[i])
			i++;
	}
	if (del[i - 1] == '\\')
		return (-1);
	return (count);
}

int	format_each_bs_sections(char **format)
{
	int		i;
	int		j;
	int		bs_nb;
	char	*tmp;
	
	i = 0;
	while (format[i])
	{
		bs_nb = 0;
		j = -1;
		while (format[i][++j] == '\\')
			bs_nb++;
		tmp = format[i];
		format[i] = ft_substr(format[i], (bs_nb / 2)
			, ft_strlen(format[i]) - (bs_nb / 2)) + 1;
		free(tmp);
		i++;
	}
	return (0);
}

int	format_backslash(char *del)
{
	int		i;
	int		j;
	int		k;
	int		size;
	char	**format;

	i = 0;
	j = 0;
	k = 0;
	size = bs_sections(del);
	if (size == -1)
	{
		printf("Bad del format\n");	
		return (1);
	}
	format = malloc(sizeof(char *) * (size + 1));
	while (del[i])
	{
		if (del[i] == '\\')
		{
			j = i;
			while (del[i] == '\\' && del[i])
				i++;
			while (del[i] != '\\' && del[i])
				i++;
			format[k] = ft_substr(del, j, (i - j));
			k++;
		}
	}
	format[k] = 0;
	format_each_bs_sections(format);
	return (0);
}