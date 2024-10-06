/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhugueno <mhugueno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 00:11:31 by mhugueno          #+#    #+#             */
/*   Updated: 2023/07/07 00:11:31 by mhugueno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_HPP
# define SERVEUR_HPP

class Serveur
{
	public:
		Serveur() {};
		Serveur(std::string port, std::string password) : _port(port), _password(password), _enable(false) {};
		Serveur(const Serveur& other) : _sockfd(other._sockfd), _serveur_address(other._serveur_address), _port(other._port), _password(other._password), _enable(other._enable) {};
		Serveur& operator=(const Serveur& other)
		{
			if (this == &other)
				return (*this);
			_sockfd = other._sockfd;
			_serveur_address = other._serveur_address;
			_port = other._port;
			_password = other._password;
			_enable = other._enable;
			return (*this);
		};
		~Serveur()
		{
			if (_enable == true)
				close (_sockfd);
		};

		int			getSockfd();
		sockaddr_in	getServeurAdress();
		std::string	getPort();
		std::string	getPassword();
		bool		getStatus();
		void		init();

	private:
		int			_sockfd;
		sockaddr_in	_serveur_address;
		std::string	_port;
		std::string	_password;
		bool		_enable;
};

#endif
