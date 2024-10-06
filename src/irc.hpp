/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhugueno <mhugueno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 00:11:54 by mhugueno          #+#    #+#             */
/*   Updated: 2023/07/07 00:11:54 by mhugueno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/select.h>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <cerrno>
#include <cctype>
#include <ctime>
#include <algorithm>
#include <string>
#include <fstream>
#include "serveur.hpp"
#include "client.hpp"
#include "channel.hpp"

class Serveur;
class Client;
class Channel;

void	running(fd_set master_set, fd_set read_set, int max_fd, Serveur serv);
int		parsing(std::vector<std::string> words, int newsockfd, std::vector<Client*>& clients, std::vector<Channel*>& channels);
void	chatting(std::vector<Client*>& clients, std::vector<Channel*>& channels, size_t i, std::vector<std::string>	words);
void	initChannel(std::vector<std::string> words, std::vector<Client*>& clients, size_t i, std::vector<Channel*>& channels);
void	joinChannel(std::vector<Channel*>& channels, std::vector<Client*>& clients, size_t i, size_t y);
void	leftChannel(std::vector<std::string> words, std::vector<Client*>& clients, size_t i, std::vector<Channel*>& channels);
void	quitChannel(std::vector<Client*>& clients, size_t i, std::vector<Channel*>& channels);
int		initClient(std::vector<std::string> words, std::vector<Client*>& clients, size_t i);
void	kickClient(std::vector<std::string> words, std::vector<Client*>& clients, int i, std::vector<Channel*>& channels);
void	inviteClient(std::vector<std::string> words, std::vector<Client*>& clients, int i, std::vector<Channel*>& channels);
void	topicChannel(std::vector<std::string> words, std::vector<Client*>& clients, int i, std::vector<Channel*>& channels);
void	mode(std::vector<std::string> words, std::vector<Client*>& clients, int i, std::vector<Channel*>& channels);
std::string	userListFt(std::vector<Channel*>& channels, std::vector<Client*>& clients, size_t y);

#endif
