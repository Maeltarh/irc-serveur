/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhugueno <mhugueno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 00:11:49 by mhugueno          #+#    #+#             */
/*   Updated: 2023/07/07 00:11:49 by mhugueno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

int	main(int ac, char *ag[])
{
	if (ac != 3)
	{
		std::cerr << "[Error]: Wrong number of arguments.\nPlease use the program as follow : ./ircserv <port> <password>." << std::endl;
		return (-1);
	}
	Serveur serv(ag[1], ag[2]);
	serv.init();
	fd_set	master_set, read_set;
	FD_ZERO(&master_set);
	FD_SET(serv.getSockfd(), &master_set);
	int	max_fd = serv.getSockfd();
	running(master_set, read_set, max_fd, serv);
}
