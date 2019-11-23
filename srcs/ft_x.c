/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 14:29:44 by obanshee          #+#    #+#             */
/*   Updated: 2019/11/23 16:11:13 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	x_minus(t_printf **p, char *str, int tab[4], char *trans)
{
	if ((*p)->hash)
	{
		str[tab[2]++] = '0';
		str[tab[2]++] = (char)tab[3];
	}
	tab[2] += for_precision(p, tab[0] - (*p)->hash * 2, &str[tab[2]]);
	ft_strcpy(&str[tab[2]], trans);
	if ((*p)->hash)
		tab[2] += tab[0] - 2;
	else
		tab[2] += tab[0];
	tab[2] += simvol_out(p, tab[0], ' ', &str[tab[2]]);
	str[tab[2]] = '\0';
}

void	x_zero(t_printf **p, char *str, int tab[4], char *trans)
{
	if ((*p)->hash)
	{
		str[tab[2]++] = '0';
		str[tab[2]++] = (char)tab[3];
	}
	tab[2] += simvol_out(p, tab[0], '0', &str[tab[2]]);
	ft_strcpy(&str[tab[2]], trans);
}

void	x_default(t_printf **p, char *str, int tab[4], char *trans)
{
	int	help;

	help = (*p)->precision + 2; //help = tab[0] + (*p)->precision - 1;
	if ((*p)->precision > tab[0])//if ((*p)->precision > 0)
		tab[2] += simvol_out(p, help, ' ', &str[tab[2]]);
	else
		tab[2] += simvol_out(p, tab[0], ' ', &str[tab[2]]);
	if ((*p)->hash)
	{
		str[tab[2]++] = '0';
		str[tab[2]++] = (char)tab[3];
		tab[0] -= 2;
	}
	tab[2] += for_precision(p, tab[0], &str[tab[2]]);
	ft_strcpy(&str[tab[2]], trans);
}

int		ft_x_universe(t_printf **p, char c, char x)
{
	uintmax_t	num;
	char		*str;
	char		*trans;
	int			tab[4];

	tab[3] = (int)x;
	tab[2] = 0;
	num = (*p)->uint_val;
	if (num == 0)
		(*p)->hash = 0;
	trans = ft_strnew(len_nbr(num) * 2);
	if (!trans)
		return (1);
	tab[0] = transform(num, 16, c, trans) + 1;
	tab[1] = max_val(tab[0], max_val((*p)->precision, (*p)->width));
	str = ft_strnew(tab[1] + (*p)->hash * 2 + 4);
	if (!str)
		return (1);
	if ((*p)->hash)
		tab[0] += 2;
	if (num == 0 && (*p)->precision == 0)
	{
		trans[0] = '\0';
		tab[0] = 0;
	}
	if ((*p)->minus)
		x_minus(p, str, tab, trans);
	else if ((*p)->zero && (*p)->precision < 0)
		x_zero(p, str, tab, trans);
	else
		x_default(p, str, tab, trans);
	if ((*p)->final_str[0] == '\0')
		(*p)->final_str = str;
	else
	{
		(*p)->final_str = ft_strjoin((*p)->final_str, str);
		free(str);
	}
	free(trans);
	return (0);
}

int		ft_x(t_printf **p)
{
	return (ft_x_universe(p, 'a', 'x'));
}

int		ft_x2(t_printf **p)
{
	return (ft_x_universe(p, 'A', 'X'));
}
