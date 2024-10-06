/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhugueno <mhugueno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 00:11:10 by mhugueno          #+#    #+#             */
/*   Updated: 2023/07/07 00:11:10 by mhugueno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	modeOp(std::vector<std::string> words, std::vector<Client*>& clients, int i, int y, std::vector<Channel*>& channels)
{
	if (words.size() < 4)
	{
		std::string error1 = ":" + clients[i]->getNickName() + " NOTICE " + channels[y]->getName() + " :Error: Please use this command as follow : /MODE channel +/-o targetNickname.\r\n";
		send(clients[i]->getId(), error1.c_str(), error1.length(), 0);
		return;
	}
	for (size_t x = 0; x < words[3].length(); x++)
	{
		words[3][x] = std::toupper(words[3][x]);
	}
	size_t c = 0;
	while (c < clients.size())
	{
		if (clients[c]->getNickName() == words[3])
			break;
		c++;
	}
	if (clients.empty() || c == clients.size())
	{
		std::string error2 = ":" + clients[i]->getNickName() + " NOTICE " + channels[y]->getName() + " :Error: This client does not exist.\r\n";
		send(clients[i]->getId(), error2.c_str(), error2.length(), 0);
		return;
	}
	if (words[2] == "+o")
	{
		channels[y]->addOp(clients[c]->getId());
		std::string op = ":" + clients[i]->getNickName() + "!" + clients[i]->getUserName() + "@127.0.0.1 MODE " + channels[y]->getName() + " +o " + words[3] + "\r\n";
		for (size_t x = 0; x < clients.size(); x++)
		{
			if (channels[y]->checkId(clients[x]->getId()) == true)
				send(clients[x]->getId(), op.c_str(), op.length(), 0);
		}
	}
	else if (words[2] == "-o")
	{
		channels[y]->eraseOp(clients[c]->getId());
		std::string op = ":" + clients[i]->getNickName() + "!" + clients[i]->getUserName() + "@127.0.0.1 MODE " + channels[y]->getName() + " -o " + words[3] + "\r\n";
		for (size_t x = 0; x < clients.size(); x++)
		{
			if (channels[y]->checkId(clients[x]->getId()) == true)
				send(clients[x]->getId(), op.c_str(), op.length(), 0);
		}
	}
}

void	modeTopic(std::vector<std::string> words, std::vector<Client*>& clients, int i, int y, std::vector<Channel*>& channels)
{
	if (words[2] == "+t")
	{
		channels[y]->addModeT(true);
		std::string modeT = ":" + clients[i]->getNickName() + "!~" + clients[i]->getUserName() + "@127.0.0.1 MODE " + channels[y]->getName() + " +t\r\n";
		for (size_t x = 0; x < clients.size(); x++)
		{
			if (channels[y]->checkId(clients[x]->getId()) == true)
				send(clients[x]->getId(), modeT.c_str(), modeT.length(), 0);
		}
	}
	else if (words[2] == "-t")
	{
		channels[y]->addModeT(false);
		std::string modeT = ":" + clients[i]->getNickName() + "!~" + clients[i]->getUserName() + "@127.0.0.1 MODE " + channels[y]->getName() + " -t\r\n";
		for (size_t x = 0; x < clients.size(); x++)
		{
			if (channels[y]->checkId(clients[x]->getId()) == true)
				send(clients[x]->getId(), modeT.c_str(), modeT.length(), 0);
		}
	}
}

void	modeInvit(std::vector<std::string> words, std::vector<Client*>& clients, int i, int y, std::vector<Channel*>& channels)
{
	if (words[2] == "+i")
	{
		channels[y]->addModeI(true);
		std::string modeT = ":" + clients[i]->getNickName() + "!~" + clients[i]->getUserName() + "@127.0.0.1 MODE " + channels[y]->getName() + " +i\r\n";
		for (size_t x = 0; x < clients.size(); x++)
		{
			if (channels[y]->checkId(clients[x]->getId()) == true)
				send(clients[x]->getId(), modeT.c_str(), modeT.length(), 0);
		}
	}
	else if (words[2] == "-i")
	{
		channels[y]->addModeI(false);
		std::string modeT = ":" + clients[i]->getNickName() + "!~" + clients[i]->getUserName() + "@127.0.0.1 MODE " + channels[y]->getName() + " -i\r\n";
		for (size_t x = 0; x < clients.size(); x++)
		{
			if (channels[y]->checkId(clients[x]->getId()) == true)
				send(clients[x]->getId(), modeT.c_str(), modeT.length(), 0);
		}
	}
}

void	modeLimite(std::vector<std::string> words, std::vector<Client*>& clients, int i, int y, std::vector<Channel*>& channels)
{
	if (words[2] == "+l")
	{
		if (words.size() < 4)
		{
		std::string error1 = ":" + clients[i]->getNickName() + " NOTICE " + channels[y]->getName() + " :Please use this command as follow : /MODE channel +l <limit>.\r\n";
		send(clients[i]->getId(), error1.c_str(), error1.length(), 0);
		return;
		}
		int num = atoi(words[3].c_str());
		if (num <= 0)
		{
			std::string error2 = ":" + clients[i]->getNickName() + " NOTICE " + channels[y]->getName() + " :Error: wrong argument.\r\n";
			send(clients[i]->getId(), error2.c_str(), error2.length(), 0);
			return;
		}
		channels[y]->addModeL(num);
		std::string modeL = ":" + clients[i]->getNickName() + "!" + clients[i]->getUserName() + "@127.0.0.1 MODE " + channels[y]->getName() + " +l " + words[3] + "\r\n";
		for (size_t x = 0; x < clients.size(); x++)
		{
			if (channels[y]->checkId(clients[x]->getId()) == true)
				send(clients[x]->getId(), modeL.c_str(), modeL.length(), 0);
		}
	}
	else if (words[2] == "-l")
	{
		channels[y]->addModeL(0);
		std::string modeL = ":" + clients[i]->getNickName() + "!" + clients[i]->getUserName() + "@127.0.0.1 MODE " + channels[y]->getName() + " -l\r\n";
		for (size_t x = 0; x < clients.size(); x++)
		{
			if (channels[y]->checkId(clients[x]->getId()) == true)
				send(clients[x]->getId(), modeL.c_str(), modeL.length(), 0);
		}
	}
}

void	modePassword(std::vector<std::string> words, std::vector<Client*>& clients, int i, int y, std::vector<Channel*>& channels)
{
	if (words[2] == "+k")
	{
		if (words.size() < 4)
		{
			std::string error1 = ":" + clients[i]->getNickName() + " NOTICE " + channels[y]->getName() + " :Please use this command as follow : /MODE channel +k <password>.\r\n";
			send(clients[i]->getId(), error1.c_str(), error1.length(), 0);
			return;
		}
		channels[y]->addPassword(words[3]);
		std::string modeK = ":" + clients[i]->getNickName() + "!" + clients[i]->getUserName() + "@127.0.0.1 MODE " + channels[y]->getName() + " +k " + words[3] + "\r\n";
		for (size_t x = 0; x < clients.size(); x++)
		{
			if (channels[y]->checkId(clients[x]->getId()) == true)
				send(clients[x]->getId(), modeK.c_str(), modeK.length(), 0);
		}
	}
	else if (words[2] == "-k")
	{
		channels[y]->addPassword("NONE");
		std::string modeK = ":" + clients[i]->getNickName() + "!" + clients[i]->getUserName() + "@127.0.0.1 MODE " + channels[y]->getName() + " -k\r\n";
		for (size_t x = 0; x < clients.size(); x++)
		{
			if (channels[y]->checkId(clients[x]->getId()) == true)
				send(clients[x]->getId(), modeK.c_str(), modeK.length(), 0);
		}
	}
}

void	mode(std::vector<std::string> words, std::vector<Client*>& clients, int i, std::vector<Channel*>& channels)
{
	if (words.size() < 3)
		return;
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
	if (channels[y]->checkOp(clients[i]->getId()) != true)
	{
		std::string error2 = ":" + clients[i]->getNickName() + " NOTICE " + channels[y]->getName() + " :Error: no permission to use this command.\r\n";
		send(clients[i]->getId(), error2.c_str(), error2.length(), 0);
		return;
	}
	std::string parse[10] = {"+t", "-t", "+i", "-i", "+o", "-o", "+l", "-l", "+k", "-k"};
	for (int x = 0; x < 10; x++)
	{
		if (parse[x] == words[2])
		{
			int	switchIndex;
			if (parse[x] == "+t" || parse[x] == "-t")
				switchIndex = 0;
			else if (parse[x] == "+i" || parse[x] == "-i")
				switchIndex = 2;
			else if (parse[x] == "+o" || parse[x] == "-o")
				switchIndex = 4;
			else if (parse[x] == "+l" || parse[x] == "-l")
				switchIndex = 6;
			else if (parse[x] == "+k" || parse[x] == "-k")
				switchIndex = 8;
			else
				switchIndex = x;
			switch (switchIndex)
			{
				case 0:
					modeTopic(words, clients, i, y, channels);
					break;
				case 2:
					modeInvit(words, clients, i, y, channels);
					break;
				case 4:
					modeOp(words, clients, i, y, channels);
					break;
				case 6:
					modeLimite(words, clients, i, y, channels);
					break;
				case 8:
					modePassword(words, clients, i, y, channels);
					break;
			}
		}
	}
}
