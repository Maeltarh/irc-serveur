/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhugueno <mhugueno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 00:12:28 by mhugueno          #+#    #+#             */
/*   Updated: 2023/07/07 00:12:28 by mhugueno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

std::string	Channel::getName()
{
	return (this->_name);
}

std::string	Channel::getTopic()
{
	return (this->_topic);
}

bool	Channel::getModeI()
{
	return (this->_modeI);
}

bool	Channel::getModeT()
{
	return (this->_modeT);
}

std::string	Channel::getPassword()
{
	return (this->_password);
}

int	Channel::getModeL()
{
	return (this->_modeL);
}

std::vector<int>	Channel::getId()
{
	return (this->_id);
}

int	Channel::getIdSize()
{
	return (this->_id.size());
}

std::vector<int>	Channel::getOp()
{
	return (this->_op);
}

std::vector<int>	Channel::getInv()
{
	return (this->_inv);
}

void	Channel::addTopic(std::string topic)
{
	_topic = topic;
}

void	Channel::addModeI(bool value)
{
	_modeI = value;
}

void	Channel::addModeT(bool value)
{
	_modeT = value;
}

void	Channel::addPassword(std::string password)
{
	_password = password;
}

void	Channel::addModeL(int range)
{
	_modeL = range;
}

void	Channel::addId(int newsockfd)
{
	_id.push_back(newsockfd);
}

void	Channel::eraseId(int newsockfd)
{
	for (size_t i = 0; i < _id.size(); i++)
	{
		if (_id[i] == newsockfd)
			{
				_id.erase(_id.begin() + i);
				break;
			}
	}
}

bool	Channel::checkId(int newsockfd)
{
	for (size_t i = 0; i < _id.size(); i++)
	{
		if (_id[i] == newsockfd)
			return (true);
	}
	return (false);
}

void	Channel::addOp(int newsockfd)
{
	_op.push_back(newsockfd);
}

void	Channel::eraseOp(int newsockfd)
{
	for (size_t i = 0; i < _op.size(); i++)
	{
		if (_op[i] == newsockfd)
			{
				_op.erase(_op.begin() + i);
				break;
			}
	}
}

bool	Channel::checkOp(int newsockfd)
{
	for (size_t i = 0; i < _op.size(); i++)
	{
		if (_op[i] == newsockfd)
		{
			return (true);
		}
	}
	return (false);
}

void	Channel::addInv(int newsockfd)
{
	_inv.push_back(newsockfd);
}

void	Channel::eraseInv(int newsockfd)
{
	for (size_t i = 0; i < _inv.size(); i++)
	{
		if (_inv[i] == newsockfd)
			{
				_inv.erase(_op.begin() + i);
				break;
			}
	}
}

bool	Channel::checkInv(int newsockfd)
{
	for (size_t i = 0; i < _inv.size(); i++)
	{
		if (_inv[i] == newsockfd)
		{
			return (true);
		}
	}
	return (false);
}

////////////////////////////////////////////////////////////////////////////////

void	topicChannel(std::vector<std::string> words, std::vector<Client*>& clients, int i, std::vector<Channel*>& channels)
{
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
	if (words.size() == 2)
	{
		if (channels[y]->getTopic() == "NONE")
		{
			std::string topic = ":" + clients[i]->getNickName() + " NOTICE " + channels[y]->getName() + " :No topic is set\r\n";
			send(clients[i]->getId(), topic.c_str(), topic.length(), 0);
		}
		else
		{
			std::string topic = ":" + clients[i]->getNickName() + " NOTICE " + channels[y]->getName() + " :Channel topic :" + channels[y]->getTopic() + "\r\n";
			send(clients[i]->getId(), topic.c_str(), topic.length(), 0);
		}
	}
	if (words.size() > 2)
	{
		if (channels[y]->checkOp(clients[i]->getId()) == true || channels[y]->getModeT() == false)
		{
			words[2].erase(0, 1);
			std::string newTopic;
			for (size_t x = 2; x < words.size(); x++)
			{
				newTopic += words[x];
			}
			std::string topic = ":" + clients[i]->getNickName() + "!~" + clients[i]->getUserName() + "@127.0.0.1 TOPIC " + channels[y]->getName() + " :" + newTopic + "\r\n";
			for (size_t x = 0; x < clients.size(); x++)
			{
				if (channels[y]->checkId(clients[x]->getId()) == true)
					send(clients[x]->getId(), topic.c_str(), topic.length(), 0);
			}
			channels[y]->addTopic(newTopic);
		}
		else
		{
			std::string error2 = ":" + clients[i]->getNickName() + " NOTICE " + channels[y]->getName() + " :Error: no permission to use this command.\r\n";
			send(clients[i]->getId(), error2.c_str(), error2.length(), 0);
			return;
		}
	}
}

std::string	userListFt(std::vector<Channel*>& channels, std::vector<Client*>& clients, size_t y, size_t x)
{
	std::string	userList;
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (channels[y]->checkId(clients[i]->getId()) == true && clients[i]->getId() != clients[x]->getId())
		{
			if (!userList.empty())
				userList += " ";
			if (channels[y]->checkOp(clients[i]->getId()) == true)
				userList += "@";
			userList += clients[i]->getNickName();
		}
	}
	return (userList);
}

void	joinChannel(std::vector<Channel*>& channels, std::vector<Client*>& clients, size_t i, size_t y)
{
	std::string	nickName = clients[i]->getNickName();
	std::string	userName = clients[i]->getUserName();
	std::string	host = "127.0.0.1";
	std::string	serverName = "IfPeachill";
	std::string	channelName = channels[y]->getName();
	std::string	joinMsg = ":" + nickName + "!" + userName + "@" + host + " JOIN " + channelName + "\r\n";
	std::string	userList = ":" + serverName + " 353 " + nickName + " = " + channelName + " :";
	if (channels[y]->checkOp(clients[i]->getId()) == true)
		userList += "@";
	userList += nickName + " " + userListFt(channels, clients, y, i) + "\r\n";
	std::string	endUserList = ':' + serverName + " 366 " + nickName + " " + channelName + " :End of /NAMES list.\r\n";
	std::string	channelTopic = ":" + serverName + " 332 " + nickName + " " + channelName + " :" + channels[y]->getTopic() + "\r\n";
	for (size_t x = 0; x < clients.size(); x++)
	{
		if (channels[y]->checkId(clients[x]->getId()) == true)
		{
			send(clients[x]->getId(), joinMsg.c_str(), joinMsg.length(), 0);
			send(clients[x]->getId(), userList.c_str(), userList.length(), 0);
			send(clients[x]->getId(), endUserList.c_str(), endUserList.length(), 0);
			send(clients[x]->getId(), channelTopic.c_str(), channelTopic.length(), 0);
		}
	}
}

void	quitChannel(std::vector<Client*>& clients, size_t i, std::vector<Channel*>& channels)
{
	if (channels.empty())
	{
		delete (clients[i]);
		clients.erase(clients.begin() + i);
		return;
	}
	for (size_t y = 0; y < channels.size(); y++)
	{
		std::string	msg = ":" + clients[i]->getNickName() + "!" + clients[i]->getUserName() + "@127.0.0.1" + " PART " + channels[y]->getName() + "\r\n";
		for (size_t x = 0; x < clients.size(); x++)
		{
			if (clients[i]->checkChannels(channels[y]->getName()) == true && x != i)
			{
				send(clients[x]->getId(), msg.c_str(), msg.length(), 0);
			}
		}
		channels[y]->eraseId(clients[i]->getId());
	}
	delete (clients[i]);
	clients.erase(clients.begin() + i);
}

void	leftChannel(std::vector<std::string> words, std::vector<Client*>& clients, size_t i, std::vector<Channel*>& channels)
{
	if (words.size() < 2)
	{
		std::string error1 = ":" + clients[i]->getNickName() + " NOTICE " + " :Error: Please use the command PART as follow : PART <channel>\r\n";
		send(clients[i]->getId(), error1.c_str(), error1.length(), 0);
		return;
	}
	size_t	y = 0;
	while (y < channels.size())
	{
		if (channels[y]->getName() == words[1])
			break;
		y++;
	}
	if (channels.empty() || y == channels.size())
	{
		std::string error2 = ":" + clients[i]->getNickName() + " NOTICE " + " :Error: This channel does not exist.\r\n";
		send(clients[i]->getId(), error2.c_str(), error2.length(), 0);
		return;
	}
	if (channels[y]->checkId(clients[i]->getId()) == true)
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
	else
	{
		std::string error3 = ":" + clients[i]->getNickName() + " NOTICE " + channels[y]->getName() + " :Error: Client is not in this channel.\r\n";
		send(clients[i]->getId(), error3.c_str(), error3.length(), 0);
	}
}

void	initChannel(std::vector<std::string> words, std::vector<Client*>& clients, size_t i, std::vector<Channel*>& channels)
{
	size_t	y = 0;
	while (y < channels.size())
	{
		if (channels[y]->getName() == words[1])
			break;
		y++;
	}
	if (channels.empty() || y == channels.size())
	{
		Channel* channel = new Channel(words[1]);
		channels.push_back(channel);
		channels[y]->addOp(clients[i]->getId());
	}
	if ((channels[y]->getModeL() > 0) && (channels[y]->getModeL() <= channels[y]->getIdSize()))
	{
		std::string error0 = ":" + clients[i]->getNickName() + " NOTICE " + channels[y]->getName() + " :Error: This channel is full.\r\n";
		send(clients[i]->getId(), error0.c_str(), error0.length(), 0);
		return;
	}
	if (words.size() > 3)
	{
		std::string error1 = ":" + clients[i]->getNickName() + " NOTICE " + channels[y]->getName() + " :Error: Please use the command JOIN as follow : JOIN <channel>.\r\n";
		send(clients[i]->getId(), error1.c_str(), error1.length(), 0);
		return;
	}
	if (channels[y]->getPassword() != "NONE" && channels[y]->getPassword() != words[2])
	{
		std::string error4 = ":" + clients[i]->getNickName() + " NOTICE " + channels[y]->getName() + " :Error: Incorrect password.\r\n";
		send(clients[i]->getId(), error4.c_str(), error4.length(), 0);
		return;
	}
	if (channels[y]->checkId(clients[i]->getId()) == true)
	{
		std::string error2 = ":" + clients[i]->getNickName() + " NOTICE " + channels[y]->getName() + " :Error: Client already in this channel.\r\n";
		send(clients[i]->getId(), error2.c_str(), error2.length(), 0);
		return;
	}
	if (channels[y]->getModeI() == true && channels[y]->checkInv(clients[i]->getId()) != true)
	{
		std::string error3 = ":IfPeachill 473 " + clients[i]->getNickName() + " " + channels[y]->getName() + " :Error: You have not been invited to this channel.\r\n";
		send(clients[i]->getId(), error3.c_str(), error3.length(), 0);
		return;
	}
	channels[y]->addId(clients[i]->getId());
	clients[i]->addChannels(words[1]);
	joinChannel(channels, clients, i, y);
}
