/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chat.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhugueno <mhugueno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 00:12:14 by mhugueno          #+#    #+#             */
/*   Updated: 2023/07/07 00:12:14 by mhugueno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

int	whichChannel(std::vector<Channel*>& channels, std::string name)
{
	size_t	y = 0;
	for (size_t i = 0; i < name.length(); i++)
	{
		name[i] = std::toupper(name[i]);
	}
	while (y < channels.size())
	{
		if (channels[y]->getName() == name)
			return (y);
		y++;
	}
	return (-1);
}

std::string	isolateMsg(char* buffer)
{
	std::string	msg = buffer;
	size_t	pos = msg.find(':');
	if (pos != std::string::npos)
	{
		std::string	result = msg.substr(pos + 1);
		return (result);
	}
	return (NULL);
}

int	privMsg(std::vector<Client*>& clients, std::vector<Channel*>& channels, size_t y, std::string name)
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (clients[i]->getNickName() == name)
		{
			if (channels[y]->checkId(clients[i]->getId()) == true)
				return (clients[i]->getId());
		}
	}
	return (-1);
}

void	chatting(std::vector<Client*>& clients, std::vector<Channel*>& channels, size_t i, std::vector<std::string> words)
{
	if (channels.size() > 0)
	{
		int	y = whichChannel(channels, words[1]);
		if (y < 0)
		{
			size_t c = 0;
			while (c < clients.size())
			{
				if (clients[c]->getNickName() == words[1])
					break;
				c++;
			}
			if (clients.empty() || c == clients.size())
			{
				std::string error1 = ":" + clients[i]->getNickName() + " NOTICE " + " :Error: This client does not exist.\r\n";
				send(clients[i]->getId(), error1.c_str(), error1.length(), 0);
				return;
			}
			for (size_t x = 0; x < words[1].length(); x++)
			{
				words[1][x] = toupper(words[1][x]);
			}
			std::string	msg = words[2];
			for (size_t x = 3; x < words.size(); x++)
			{
				if (!msg.empty())
					msg += " ";
				msg += words[x];
			}
			if (words[0] == "SEND")
			{
				std::ifstream file(words[2], std::ifstream::ate | std::ifstream::binary);
				long size = 0;
				if (!file.is_open())
				{	
					std::cerr << "Failed to open file." << std::endl;
					return;
				}
				else
				{
					file.seekg(0, std::ios::end);
					size = file.tellg();
					file.close();
				}
				std::string filesize = std::to_string(size);
				std::string PRIVMSG = "PRIVMSG " + words[1] + " :\001DCC SEND " + words[2] + " 2130706433 6667 " + filesize + "\001\r\n";
				send(clients[c]->getId(), PRIVMSG.c_str(), PRIVMSG.length(), 0);
				std::cout << PRIVMSG << std::endl;
			}
			else
			{
				std::string PRIVMSG = ":" + clients[i]->getNickName() + "!" + clients[i]->getUserName() + "@127.0.0.1 PRIVMSG " + words[1] + " " + msg + "\r\n";
				send(clients[c]->getId(), PRIVMSG.c_str(), PRIVMSG.length(), 0);
				std::cout << PRIVMSG << std::endl;
			}
			return;
		}
		if (channels[y]->checkId(clients[i]->getId()) == false)
			return;
		size_t	pos = words[2].find(':');
		std::string	msg = words[2].substr(pos + 1);
		for (size_t x = 3; x < words.size(); x++)
		{
			if (!msg.empty())
				msg += " ";
			msg += words[x];
		}
		std::string	nickName = clients[i]->getNickName();
		std::string	userName = clients[i]->getUserName();
		std::string	host = "127.0.0.1";
		std::string	channelName = channels[y]->getName();
		std::string	PRIVMSG = ":" + nickName + "!" + userName + "@" + host + " PRIVMSG " + channelName + " :" + msg + "\r\n";
		for (size_t x = 0; x < clients.size(); x++)
		{
			if ((channels[y]->checkId(clients[x]->getId()) == true) && (x != i))
			{
				int	bytes = send(clients[x]->getId(), PRIVMSG.c_str(), PRIVMSG.length(), 0);
				if (bytes < 0)
					std::cerr << ("[Error]: message could not be sent.") << std::endl;
			}
		}
	}
}
