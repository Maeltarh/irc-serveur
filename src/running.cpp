/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhugueno <mhugueno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 00:11:18 by mhugueno          #+#    #+#             */
/*   Updated: 2023/07/07 00:11:18 by mhugueno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	deleteClient(int newsockfd, std::vector<Client*>& clients)
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (clients[i]->getId() == newsockfd)
			{
				clients.erase(clients.begin() + i);
				break;
			}
	}
}

void	unlockClient(int newsockfd, std::vector<Client*>& clients)
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (clients[i]->getId() == newsockfd)
			{
				clients[i]->addPassword(true);
				break;
			}
	}
}

void	newClient(int newsockfd, std::vector<Client*>& clients)
{
	srand(time(0));
	int	randomDigit1 = rand() % 10;
	int	randomDigit2 = rand() % 10;
	int	randomDigit3 = rand() % 10;
	std::ostringstream	oss;
	oss << randomDigit1 << randomDigit2 << randomDigit3;
	std::string	number = oss.str();
	std::string	nickName = "guest" + number;
	std::string	userName = "guest" + number;
	Client* client = new Client(newsockfd, nickName, userName);
	clients.push_back(client);
}

void	running(fd_set master_set, fd_set read_set, int max_fd, Serveur serv)
{
	std::vector<Client*> clients;
	std::vector<Channel*> channels;
	std::vector<std::string> words;
	std::string	currentWord;
	while (true)
	{

/*
		std::cout << "//////////[List of clients]//////////" << std::endl;
		for (size_t i = 0; i < clients.size(); i++)
		{
			std::cout << clients[i]->getNickName() << " : " << clients[i]->getId() << std::endl;
		}
		std::cout << "//////////[List of channels]//////////" << std::endl;
		for (size_t i = 0; i < channels.size(); i++)
		{
			std::cout << channels[i]->getName() << " : \n";
			for (size_t y = 0; y < clients.size(); y++)
			{
				if (channels[i]->checkId(clients[y]->getId()) == true)
					std::cout << "* " << clients[y]->getNickName();
				if (channels[i]->checkOp(clients[y]->getId()) == true)
					std::cout << "-op";
				std::cout << "\n";
			}
			std::cout << std::endl;
		}
		std::cout << "/////////////////////////////////////\n" << std::endl;
*/

		read_set = master_set;
		if (select(max_fd + 1, &read_set, NULL, NULL, NULL) == -1)
		{
			std::cerr << "[Error]: Select failed." << std::endl;
			return;
		}
		for (int i = 0; i <= max_fd; i++)
		{
			if (FD_ISSET(i, &read_set))
			{
				if (i == serv.getSockfd())
				{
					sockaddr_in	client_address;
					socklen_t	client_len = sizeof(client_address);
					int	newsockfd = accept(serv.getSockfd(), (sockaddr *)&client_address, &client_len);
					FD_SET(newsockfd, &master_set);
					if (newsockfd > max_fd)
						max_fd = newsockfd;
					newClient(newsockfd, clients);
				}
				else
				{
					char	buffer[256];
					memset(buffer, 0, sizeof(buffer));
					if (recv(i, buffer, 255, 0) <= 0)
					{
						close (i);
						FD_CLR(i, &master_set);
					}
					else
					{

/*						
						std::cout << "//////////[Message received]//////////" << std::endl;
						std::cout << buffer << std::endl;
						std::cout << "/////////////////////////////////////\n" << std::endl;
*/

						size_t	length = strlen(buffer);
						for (size_t y = 0; y < length; y++)
						{
							char c = buffer[y];
							if (c == ' ' || c == '\n')
							{
								if (!currentWord.empty())
								{
									words.push_back(currentWord);
									currentWord.clear();
								}
								if (c == '\n')
								{
									if (words[0] == "PASS")
									{
										if (words[1] != serv.getPassword())
										{
											std::string	error = ":Guest NOTICE :Error: Incorrect password.\r\n";
											int bytesSent = send(i, error.c_str(), error.length(), 0);
											if (bytesSent < 0)
												std::cerr << "[Error]: Failed to send error message." << std::endl;
											FD_CLR(i, &master_set);
											close (i);
											deleteClient(i, clients);
										}
										else
											unlockClient(i, clients);
									}
									if (parsing(words, i, clients, channels) == -1)
									{
										FD_CLR(i, &master_set);
										close (i);
										deleteClient(i, clients);
									}
									words.clear();
								}
							}
							else if (c != '\r')
								currentWord.push_back(c);
						}
					}
				}
			}
		}
	}
}
