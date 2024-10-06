/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhugueno <mhugueno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 00:12:19 by mhugueno          #+#    #+#             */
/*   Updated: 2023/07/07 00:12:19 by mhugueno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "irc.hpp"

class Channel
{
	public:
		Channel() {};
		Channel(std::string name) : _name(name), _topic("NONE"), _modeI(false), _modeT(true), _password("NONE"), _modeL(0) {};
		Channel(const Channel& other) : _name(other._name), _topic(other._topic), _modeI(other._modeI), _modeT(other._modeT), _password(other._password), _modeL(other._modeL), _id(other._id), _op(other._op), _inv(other._inv) {};
		Channel& operator=(const Channel& other)
		{
			if (this == &other)
				return (*this);
			_name = other._name;
			_topic = other._topic;
			_modeI = other._modeI;
			_modeT = other._modeT;
			_password = other._password;
			_modeL = other._modeL;
			_id = other._id;
			_op = other._op;
			_inv = other._inv;
			return (*this);
		};
		~Channel() {};

		std::string			getName();
		std::string			getTopic();
		bool				getModeI();
		bool				getModeT();
		std::string			getPassword();
		int					getModeL();
		std::vector<int>	getId();
		int					getIdSize();
		std::vector<int>	getOp();
		std::vector<int>	getInv();
		void				addTopic(std::string topic);
		void				addModeI(bool value);
		void				addModeT(bool value);
		void				addPassword(std::string password);
		void				addModeL(int range);
		void				addId(int newsockfd);
		void				eraseId(int newsockfd);
		bool				checkId(int newsockfd);
		void				addOp(int newsockfd);
		void				eraseOp(int newsockfd);
		bool				checkOp(int newsorckfd);
		void				addInv(int newsockfd);
		void				eraseInv(int newsockfd);
		bool				checkInv(int newsorckfd);

	private:
		std::string			_name;
		std::string			_topic;
		bool				_modeI;
		bool				_modeT;
		std::string			_password;
		int					_modeL;
		std::vector<int>	_id;
		std::vector<int>	_op;
		std::vector<int>	_inv;
};

#endif
