/*
	1. 어떤 문자열이 들어옴.
	2. 해당 문자열을 split으로 자르기.
	3. 잘라진 값들을 가지고 노드로 만들기.
	4. 각 노드들을 해쉬리스트에 추가해주기.
*/

int	export(t_hash_list *export_list[], char	*str)
{
	char	**new_export_list;
	int		flag;
	int		region;
	int		i;

	i = 0;
	flag = 0;
	new_export_list = ft_split(str);
	// if (export_list == NULL)
		// error handling.
	while (new_export_list[i])
	{
		region = new_export_list[i][0] - 'A';
		if (0 <= region && region <= 26)
		{
			//export_list[region]에 추가하기.
		}
		else if (32 <= region && region <= 58)
		{
			//export_list[region]에 추가하기.
		}
		else
		{
			write(2, "bash: export: ", 15);
			write(2, export_list[i], ft_strlen(export_list));
			flag = 1;
		}
	}
	if (flag == 1)
		return (1);
	else
		return (0);
}
