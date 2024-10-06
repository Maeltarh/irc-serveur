/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhugueno <mhugueno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 00:12:00 by mhugueno          #+#    #+#             */
/*   Updated: 2023/07/07 00:12:00 by mhugueno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "irc.hpp"

class Client
{
	public:
		Client(int newsockfd, std::string nickName, std::string userName) : _id(newsockfd), _nickname(nickName), _username(userName), _operator(false), _password(false) {};
		Client(const Client& other) : _id(other._id), _nickname(other._nickname), _username(other._username), _operator(other._operator), _password(other._password) {};
		Client& operator=(const Client& other)
		{
			if (this == &other)
				return(*this);
			_id = other._id;
			_nickname = other._nickname;
			_username = other._username;
			_operator = other._operator;
			_password = other._password;
			return (*this);
		}
		~Client() {};

		int			getId();
		std::string	getNickName();
		std::string	getUserName();
		bool		getOperator();
		std::vector<std::string>	getChannels();
		bool		getPassword();
		void		addPassword(bool value);
		void		addChannels(std::string name);
		void		eraseChannels(std::string name);
		bool		checkChannels(std::string name);
		void		setUpNickName(std::string name);
		void		setUpUserName(std::string name);
		void		setUpOperator();

	private:
		int			_id;
		std::string	_nickname;
		std::string	_username;
		bool		_operator;
		std::vector<std::string>	_channels;
		bool		_password;
};

#endif
