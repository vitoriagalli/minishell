// void	ft_lst_print(t_list *lst)
// {
// 	int count;

// 	count = 0;
// 	while (lst)
// 	{
// 		ft_printf("lst %i: %s\n", count, lst->content);
// 		lst = lst->next;
// 		count++;
// 	}
// }

// void	ft_cmd_print(t_cmd *lst)
// {
// 	int	count;
// 	int	i;

// 	i = 0;
// 	count = 0;
// 	while (lst)
// 	{
// 		ft_printf("-------- command %i ---------\n", count);
// 		ft_printf("cmd: %s\n", lst->cmd_name);
// 		ft_printf("sep: %i\n", lst->separator);
// 		while (lst->args[i])
// 		{
// 			ft_printf("arg %i: %s\n", i, lst->args[i]);
// 			i++;
// 		}
// 		ft_lst_print(lst->redirection);
// 		i = 0;
// 		lst = lst->next;
// 		count++;
// 	}
// }
