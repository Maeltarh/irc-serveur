/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhugueno <mhugueno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 00:11:40 by mhugueno          #+#    #+#             */
/*   Updated: 2023/07/07 00:11:40 by mhugueno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

int	handleCommand(std::vector<std::string> words, std::vector<Client*>& clients, size_t i, std::vector<Channel*>& channels)
{
	std::string parse[11] = {"NICK", "JOIN", "PART", "QUIT","KICK", "INVITE", "TOPIC", "MODE", "USER","PRIVMSG", "SEND"};
	for (int y = 0; y < 11; y++)
	{
		if (parse[y] == words[0])
		{
			std::string	str = words[1];
			for (size_t i = 0; i < str.length(); i++)
			{
				str[i] = std::toupper(str[i]);
			}
			words[1] = str;
			switch (y)
			{
				case 0:
					if (initClient(words, clients, i) < 0)
						return (2);
					return (1);
					break;
				case 1:
					initChannel(words, clients, i, channels);
					return (1);
					break;
				case 2:
					leftChannel(words, clients, i, channels);
					return (1);
					break;
				case 3:
					quitChannel(clients, i, channels);
					return (1);
					break;
				case 4:
					kickClient(words, clients, i, channels);
					return (1);
					break;
				case 5:
					inviteClient(words, clients, i, channels);
					return (1);
					break;
				case 6:
					topicChannel(words, clients, i, channels);
					return (1);
					break;
				case 7:
					mode(words, clients, i, channels);
					return (1);
					break;
				case 8:
					clients[i]->setUpUserName(words[1]);
					return (1);
					break;
				case 9:
					return (0);
					break;
				case 10:
					return (0);
					break;
			}
			break;
		}
	}
	return (-1);
}

int	parsing(std::vector<std::string> words, int newsockfd, std::vector<Client*>& clients, std::vector<Channel*>& channels)
{
	size_t i = 0;
	while (i < clients.size())
	{
		if (clients[i]->getId() == newsockfd)
				break;
		i++;
	}

/*
	for (size_t y = 0; y < words.size(); y++)
	{
		std::cout << words[y] << " ";
	}
	std::cout << std::endl;
*/

	int x = handleCommand(words, clients, i, channels);
	if (x == 0)
		chatting(clients, channels, i, words);
	else if (x == 2)
		return (-1);
	return (0);
}
