/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhugueno <mhugueno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 00:11:25 by mhugueno          #+#    #+#             */
/*   Updated: 2023/07/07 00:11:25 by mhugueno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

int	Serveur::getSockfd()
{
	return (this->_sockfd);
}

sockaddr_in	Serveur::getServeurAdress()
{
	return (this->_serveur_address);
}

std::string	Serveur::getPort()
{
	return (this->_port);
}

std::string	Serveur::getPassword()
{
	return (this->_password);
}

bool	Serveur::getStatus()
{
	return (this->_enable);
}

void	Serveur::init()
{
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	_serveur_address.sin_family = AF_INET;
	_serveur_address.sin_port = htons(atoi(_port.c_str()));
	_serveur_address.sin_addr.s_addr = INADDR_ANY;
	bind(_sockfd, (struct sockaddr *)&_serveur_address, sizeof(_serveur_address));
	listen(_sockfd, 10);
	_enable = true;
}
