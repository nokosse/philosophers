/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:16:48 by kvisouth          #+#    #+#             */
/*   Updated: 2023/04/05 17:55:23 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/notlibft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{	
	if (!lst || !del)
		return ;
	(*del)(lst->content);
	free(lst);
}
