/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhugueno <mhugueno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 00:12:05 by mhugueno          #+#    #+#             */
/*   Updated: 2023/07/07 00:12:05 by mhugueno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

int	Client::getId()
{
	return (this->_id);
}

std::string	Client::getNickName()
{
	return (this->_nickname);
}

std::string	Client::getUserName()
{
	return (this->_username);
}

bool	Client::getOperator()
{
	return (this->_operator);
}

bool	Client::getPassword()
{
	return (this->_password);
}

std::vector<std::string>	Client::getChannels()
{
	return (this->_channels);
}

void	Client::addPassword(bool value)
{
	_password = value;
}

void	Client::addChannels(std::string name)
{
	_channels.push_back(name);
}

void	Client::eraseChannels(std::string name)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i] == name)
		{
			_channels.erase(_channels.begin() + i);
			break;
		}
	}
}

bool	Client::checkChannels(std::string name)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i] == name)
			return (true);
	}
	return (false);
}

void	Client::setUpNickName(std::string name)
{
	this->_nickname = name;
}

void	Client::setUpUserName(std::string name)
{
	this->_username = name;
}

void	Client::setUpOperator()
{
	this->_operator = true;
}

////////////////////////////////////////////////////////////////////////////////

void	expulseClient(std::vector<Client*>& clients, size_t i, std::vector<Channel*>& channels, size_t y)
{
	std::string	msg = ":" + clients[i]->getNickName() + "!" + clients[i]->getUserName() + "@127.0.0.1" + " PART " + channels[y]->getName() + "\r\n";
	for (size_t x = 0; x < clients.size(); x++)
	{
		if (channels[y]->checkId(clients[x]->getId()) == true)
		{
			send(clients[x]->getId(), msg.c_str(), msg.length(), 0);
		}
	}
	channels[y]->eraseId(clients[i]->getId());
	clients[i]->eraseChannels(channels[y]->getName());
}

void	kickClient(std::vector<std::string> words, std::vector<Client*>& clients, int i, std::vector<Channel*>& channels)
{
	for (size_t x = 0; x < words[1].length(); x++)
	{
		words[1][x] = std::toupper(words[1][x]);
	}
	for (size_t x = 0; x < words[2].length(); x++)
	{
		words[2][x] = std::toupper(words[2][x]);
	}
	size_t y = 0;
	while (y < channels.size())
	{
		if (channels[y]->getName() == words[1])
			break;
		y++;
	}
	if (channels.empty() || y == channels.size())
	{
		std::string error1 = ":" + clients[i]->getNickName() + " NOTICE " + " :Error: This channel does not exist.\r\n";
		send(clients[i]->getId(), error1.c_str(), error1.length(), 0);
		return;
	}
	size_t c = 0;
	while (c < clients.size())
	{
		if (clients[c]->getNickName() == words[2])
			break;
		c++;
	}
	if (clients.empty() || c == clients.size())
	{
		std::string error2 = ":" + clients[i]->getNickName() + " NOTICE " + channels[y]->getName() + " :Error: This client does not exist.\r\n";
		send(clients[i]->getId(), error2.c_str(), error2.length(), 0);
		return;
	}
	if (channels[y]->checkOp(clients[i]->getId()) == true)
	{
		expulseClient(clients, c, channels, y);
		std::string kick = ":" + clients[i]->getNickName() + " NOTICE " + channels[y]->getName() + " " + words[2] + " has been kicked by " + clients[i]->getNickName();
		if (words.size() >= 5)
		{
			kick += " :";
			for (size_t x = 4; x < words.size(); x++)
			{
				kick += words[x];
				if ((x + 1) < words.size())
					kick += " ";
			}
		}
		kick += "\r\n";
		for (size_t x = 0; x < clients.size(); x++)
		{
			if (channels[y]->checkId(clients[x]->getId()) == true)
			{
				send(clients[x]->getId(), kick.c_str(), kick.length(), 0);
			}
		}
	}
	else
	{
		std::string error3 = ":" + clients[i]->getNickName() + " NOTICE " + channels[y]->getName() + " :Error: no permission to use this command.\r\n";;
		send(clients[i]->getId(), error3.c_str(), error3.length(), 0);
		return;
	}
}

void	inviteClient(std::vector<std::string> words, std::vector<Client*>& clients, int i, std::vector<Channel*>& channels)
{
	for (size_t x = 0; x < words[1].length(); x++)
	{
		words[1][x] = std::toupper(words[1][x]);
	}
	for (size_t x = 0; x < words[2].length(); x++)
	{
		words[2][x] = std::toupper(words[2][x]);
	}
	size_t y = 0;
	while (y < channels.size())
	{
		if (channels[y]->getName() == words[2])
			break;
		y++;
	}
	if (channels.empty() || y == channels.size())
	{
		std::string error1 = ":" + clients[i]->getNickName() + " NOTICE :Error: This channel does not exist.\r\n";
		send(clients[i]->getId(), error1.c_str(), error1.length(), 0);
		return;
	}
	size_t c = 0;
	while (c < clients.size())
	{
		if (clients[c]->getNickName() == words[1])
			break;
		c++;
	}
	if (clients.empty() || c == clients.size())
	{
		std::string error2 = ":" + clients[i]->getNickName() + " NOTICE " + channels[y]->getName() + " :Error: This client does not exist.\r\n";
		send(clients[i]->getId(), error2.c_str(), error2.length(), 0);
		return;
	}
	if (channels[y]->checkOp(clients[i]->getId()) != true)
	{
		std::string error3 = ":" + clients[i]->getNickName() + " NOTICE " + channels[y]->getName() + " :Error: No permission to use this command.\r\n";
		send(clients[i]->getId(), error3.c_str(), error3.length(), 0);
		return;
	}
	if (channels[y]->checkId(clients[c]->getId()) != true)
	{
		channels[y]->addInv(clients[c]->getId());
		std::string invite = ":" + clients[i]->getNickName() + "!~" + clients[i]->getUserName() + "@127.0.0.1 INVITE " + clients[c]->getNickName() + " :" + channels[y]->getName() + "\r\n";
		std::string notice = ":" + clients[i]->getNickName() + " NOTICE " + channels[y]->getName() + " :invitation send successfully\r\n";
		send(clients[c]->getId(), invite.c_str(), invite.length(), 0);
		send(clients[i]->getId(), notice.c_str(), notice.length(), 0);
	}
	else
	{
		std::string error4 = ":" + clients[i]->getNickName() + " NOTICE " + channels[y]->getName() + " :Error: This client is already in this channel.\r\n";
		send(clients[i]->getId(), error4.c_str(), error4.length(), 0);
		return;
	}
}

void	welcomeClient(std::vector<Client*>& clients, size_t i)
{
	std::string	nickName = clients[i]->getNickName();
	std::string	userName = clients[i]->getUserName();
	std::string	host = "127.0.0.1";
	std::string	welcomeMsg = ":server 001 " + nickName + " :Welcome to the Internet Relay Network " + nickName + "!" + userName + "@" + host + "\r\n";
	std::string	hostMsg = ":server 002 " + nickName + " :Your host is server, runing version version\r\n";
	std::string	createdMsg = ":server 003 " + nickName + " :This server was created date\r\n";
	std::string	infoMsg = ":server 004" + nickName + " :server version usermodes channelmodes\r\n";
	std::string	RPL = ":IfPeachill 005 " + nickName + " CHANTYPES=# PREFIX=(o)@ :are supported by this server\r\n";
	send(clients[i]->getId(), welcomeMsg.c_str(), welcomeMsg.length(), 0);
	send(clients[i]->getId(), hostMsg.c_str(), hostMsg.length(), 0);
	send(clients[i]->getId(), createdMsg.c_str(), createdMsg.length(), 0);
	send(clients[i]->getId(), infoMsg.c_str(), infoMsg.length(), 0);
	send(clients[i]->getId(), RPL.c_str(), RPL.length(), 0);
}

int	initClient(std::vector<std::string> words, std::vector<Client*>& clients, size_t i)
{
	if (clients[i]->getPassword() == false)
	{
		std::string	error = ":Guest NOTICE :Error: Incorrect password.\r\n";
		send(i, error.c_str(), error.length(), 0);
		return (-1);
	}
	clients[i]->setUpNickName(words[1]);
	welcomeClient(clients, i);
	return (0);
}
