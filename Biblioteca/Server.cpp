#define _CRT_SECURE_NO_WARNINGS
#include "Server.h"
#include <iostream>
#include "UserScheduler.h"
#include "DataBaseConn.h"
#include "IException.h"
#include "Logger.h"
#include "SendMsg.h"

int Server::ClientSocket[64];

void Server::wsaInit()
{
	//The Windows Sockets WSAStartup function initiates use of WS2_32.DLL by a process
	//Allows an application or DLL to specify the version of Windows Sockets required and to retrieve details of the specific Windows Sockets implementation
	//If successful, the WSAStartup function returns zero
	RetValue = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (RetValue != 0)//NO_ERROR
	{
		Logger::getInstance()->showMsg("WSAStartup failed with error: " + std::to_string(WSAGetLastError()));
		WSACleanup();
		exit(EXIT_FAILURE);
	}
}

void Server::SocketInit()
{
	//	 Initializarea socket-ului
	nSocket = socket(AF_INET, SOCK_STREAM, 0);	//returns a descriptor referencing the new socket
	// AF_INET : se foloseste pentru conexiunea la o retea TCP 
	// SOCK_STREAM : pentru conexiune orientata ( foloseste TCP/IP )

	if (nSocket < 0)
	{
		Logger::getInstance()->showMsg("Socket failed with error: " + std::to_string(WSAGetLastError()));
		WSACleanup();
		exit(EXIT_FAILURE);
	}
}

void Server::SockaddrInit()
{
	//	 Initializarea mediului de lucru pentru structura sockaddr_in
	srv.sin_family = AF_INET;		// protocolul folosit pt transmiterea datelor in retea (TCP/UDP)
	srv.sin_port = htons(PORT);		// htons : host to network start 
	srv.sin_addr.s_addr = INADDR_ANY;
	// s_addr primeste adresa IP a calculatorului pe care deschid serverul (adresa IP este luata de INADDR_ANY)
	// analog cu inet_addr(".....") -> IP-ul se introduce manual 
	memset(&(srv.sin_zero), 0, 8);	//pad care se completeaza pt a aduce marimea lui sockaddr_in la sockaddr, care este folosit in internet
}

void Server::SocketOptions()
{
	RetValue = setsockopt(nSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&nOptVal, sizeof(nOptVal));
	// SOL_SOCKET -> nivelul la care setam optiunile socket-ului
	// SO_REAUSEADDR -> optiunea pentru a putea reutiliza portul
	//nOptVal ->  valoarea pentru opțiunea solicitată

	if (RetValue != 0)
	{
		Logger::getInstance()->showMsg("Setsockopt failed with error: " + std::to_string(WSAGetLastError()));
		WSACleanup();
		exit(EXIT_FAILURE);
	}
}

void Server::Bind()
{
	//	 Legarea socket-ului la portul local
	RetValue = bind(nSocket, (sockaddr*)&srv, sizeof(sockaddr));
	if (RetValue != 0)
	{
		Logger::getInstance()->showMsg("Bind failed with error: " + std::to_string(WSAGetLastError()));
		WSACleanup();
		exit(EXIT_FAILURE);
	}
}

void split(const std::string& str, const std::string& delim, std::vector<std::string>& parts) {
	size_t start, end = 0;
	while (end < str.size()) {
		start = end;
		while (start < str.size() && (delim.find(str[start]) != std::string::npos))
			start++;  // skip initial delims
		end = start;
		while (end < str.size() && (delim.find(str[end]) == std::string::npos)) {
			end++; // skip to end of word
		}
		if (end - start != 0) {  // ignore zero-length strings.
			parts.push_back(std::string(str, start, end - start));
		}
	}
}

void Server::ProcessNewMsg(int Socket)
{
	char buff[257] = { 0, };
	RetValue = recv(Socket, buff, 256, 0);
			//Returns the number of bytes received
			//If the connection has been gracefully closed, the return value is zero




	/*******************************************************/
	if (buff[strlen(buff) - 1] == '\n')
		strcpy(buff - 2 + strlen(buff), buff + strlen(buff));
	//PUTTY ONLY
	/*******************************************************/




	if (buff[0] == '\0')
		return;

	if (RetValue == 0)	//connection gracefully closed
	{
		for (int i = 0; i < MaxClienti; i++)
			if (ClientSocket[i] == Socket)
			{
				SendMsg::getInstance()->Send(Socket, { "Deconectare cu succes!" });
				closesocket(Socket);
				ClientSocket[i] = 0;

				UserScheduler::destroyInstance(Socket);
				break;
			}
		return;
	}

	if (RetValue < 0)	//error
	{
		SendMsg::getInstance()->Send(Socket, { "Eroare la primirea mesajului!" });
		closesocket(Socket);
		for (int i = 0; i < MaxClienti; i++)
		{
			if (ClientSocket[i] == Socket)
			{
				ClientSocket[i] = 0;
				UserScheduler::destroyInstance(Socket);
				break;
			}
		}
		return;
	}
	
	// RetValue > 0

	std::string msg(buff);
	if (msg == "Exit" || msg == "Exit\r\n")
	{
		UserScheduler::getInstance(Socket)->deconectare();
		closesocket(Socket);
		for (int i = 0; i < MaxClienti; i++)
		{
			if (ClientSocket[i] == Socket)
			{
				ClientSocket[i] = 0;
				UserScheduler::destroyInstance(Socket);
				break;
			}
		}
		return;
	}
	
	std::vector<std::string> MsgParts;
	split(msg, "/", MsgParts);
	
	try
	{
		switch (std::stoi(MsgParts[0]))
		{
		case 1:
			//logare user
			try
			{
				UserScheduler::login(Socket, MsgParts);
			}
			catch (IException& e)
			{
				e.handleException(Socket);
			}
			break;

		case 2:
			//inregistrare user
			try
			{
				UserScheduler::inregistrare(Socket, MsgParts);
			}
			catch (IException& e)
			{
				e.handleException(Socket);
			}
			break;

		case 3:
			//afisare profil user
			try
			{
				UserScheduler::getInstance(Socket)->afisareProfil();
			}
			catch (IException& e)
			{
				e.handleException(Socket);
			}
			break;

		case 4:
			//afisare carti imprumutate de user
			try
			{
				UserScheduler::getInstance(Socket)->afisareCartiImprumutate();
			}
			catch (IException& e)
			{
				e.handleException(Socket);
			}
			break;

		case 5:
			//buton prelungire termen
			try
			{
				UserScheduler::getInstance(Socket)->prelungireTermen(MsgParts[1]);
			}
			catch (IException& e)
			{
				e.handleException(Socket);
			}
			break;

		case 6:
			//modificare parola
			try
			{
				UserScheduler::getInstance(Socket)->schimbaParola(MsgParts[1]);
			}
			catch (IException& e)
			{
				e.handleException(Socket);
			}
			break;

		case 7:
			//modificare email
			try
			{
				UserScheduler::getInstance(Socket)->schimbaEmail(MsgParts[1]);
			}
			catch (IException& e)
			{
				e.handleException(Socket);
			}
			break;

		case 8:
			//modificare nr telefon
			try
			{
				UserScheduler::getInstance(Socket)->schimbaTelefon(MsgParts[1]);
			}
			catch (IException& e)
			{
				e.handleException(Socket);
			}
			break;

		case 9:
			//cautare carte
			try
			{
				UserScheduler::getInstance(Socket)->cauta(MsgParts[1]);
			}
			catch (IException& e)
			{
				e.handleException(Socket);
			}
			break;

		case 10:
			//afiseaza detalii carte
			try
			{
				UserScheduler::getInstance(Socket)->afiseazaDetaliiArticol(MsgParts[1]);
			}
			catch (IException& e)
			{
				e.handleException(Socket);
			}
			break;

		case 11:
			//imprumuta carte fizic
			try
			{
				UserScheduler::getInstance(Socket)->rezervaCarte(MsgParts[1]);
			}
			catch (IException& e)
			{
				e.handleException(Socket);
			}
			break;

		case 12:
			//returneaza carte
			try
			{
				UserScheduler::getInstance(Socket)->returneazaCarte(MsgParts[1]);
			}
			catch (IException& e)
			{
				e.handleException(Socket);
			}
			break;

		case 13:
			//descarca carte in format online
			try
			{
				UserScheduler::getInstance(Socket)->descarcaArticol(MsgParts[1]);
			}
			catch (IException& e)
			{
				e.handleException(Socket);
			}
			break;


		case 14:
			//bibliotecar adauga articol
			try
			{
				UserScheduler::getInstance(Socket)->adaugaArticol_B(MsgParts);
			}
			catch (IException& e)
			{
				e.handleException(Socket);
			}
			break;

		case 15:
			//afisare imprumuturi depasite
			try
			{
				UserScheduler::getInstance(Socket)->afiseazaImprumuturiExp_B();
			}
			catch (IException& e)
			{
				e.handleException(Socket);
			}
			break;

		case 16:
			//bibliotecar modifica carte
			try
			{
				UserScheduler::getInstance(Socket)->modificaArticol_B(MsgParts);
			}
			catch (IException& e)
			{
				e.handleException(Socket);
			}
			break;

		case 17:
			try
			{
				//bibliotecar elimina carte
				UserScheduler::getInstance(Socket)->eliminaArticol_B(MsgParts[1]);
			}
			catch (IException& e)
			{
				e.handleException(Socket);
			}
			break;

		case 18:
			try
			{
				//program
				UserScheduler::getInstance(Socket)->afisareProgram();
			}
			catch(IException& e)
			{
				e.handleException(Socket);
			}
			break;

		case 19:
			try
			{
				//contact
				UserScheduler::getInstance(Socket)->afisareContact();
			}
			catch (IException& e)
			{
				e.handleException(Socket);
			}
			break;

		default:
			SendMsg::getInstance()->Send(Socket, { "Invalid command" });
		}
	}
	catch (std::invalid_argument)
	{
		SendMsg::getInstance()->Send(Socket, { "No command" });
	}

}

void Server::ProcessNewRequest()
{// Cererea noua de conectare

	//FS_ISSET verif daca un socket din fr,fw sau fe vrea sa faca ceva (conectare sau trimitere msg)
	if (FD_ISSET(nSocket, &fr))
	{				//atunci avem o noua conexiune
		int nLen = sizeof(struct sockaddr);
		int nClientSocket = accept(nSocket, NULL, &nLen);
		// accepta conexiunile noi (incercate din partea clientului catre server)
		// astfel vom avea un nou socket ID (nClientSocket)
		if (nClientSocket > 0)
		{
			// putem pune clientul in fd_set (mai precis in fread)
			int index = 0;
			for (index = 0; index < MaxClienti; index++)
			{
				if (ClientSocket[index] == 0)
				{
					ClientSocket[index] = nClientSocket;
					break;
				}
			}
			if (index >= MaxClienti)
				Logger::getInstance()->showMsg("Nu mai este loc pentru o noua conexiune!");
		}
	}
	else		//altfel unul sau mai multi sockets au trimis un mesaj
	{
		for (int i = 0; i < MaxClienti; i++)
		{
			if (FD_ISSET(ClientSocket[i], &fr))
				// am primit mesajul de la client
				ProcessNewMsg(ClientSocket[i]);
		}
	}
}

void Server::Listen()
{
	DataBaseConn* ptr;

	ptr = DataBaseConn::createInstance(L"POO"); //se face conexiunea la baza de date numita POO
	int counter = 60; //secunde pana se inchide serverul
	int aux = 0;
	//	 Ascultarea solicitarilor de la client (solicitarile sunt puse la coada)

	RetValue = listen(nSocket, 5);
	// 5 reprezinta backlog-ul (cate cereri active putem avea in acelasi timp catre server)
	// daca avem mai mult de 5 deodata, celelalte vor astepta 
	if (RetValue != 0)
	{
		Logger::getInstance()->showMsg("Listen failed with error: " + std::to_string(WSAGetLastError()));
		WSACleanup();
		exit(EXIT_FAILURE);
	}

	maxFd = nSocket;
	struct timeval time {};
	// timpul de asteptare pentru a vedea care dintre socket descriptori sunt pregatiti (contin sau nu ceva)
	time.tv_sec = 1;
	time.tv_usec = 0;


	while (TRUE)
		// continua asteptarea conectarilor pana cand se conecteaza cineva
	{
		FD_ZERO(&fr);
		FD_ZERO(&fw);
		FD_ZERO(&fe);
		// golim socket descriptorii

		FD_SET(nSocket, &fr);
		FD_SET(nSocket, &fe);

		for (int i = 0; i < MaxClienti; i++)
		{
			if (ClientSocket[i] != 0)
			{
				FD_SET(ClientSocket[i], &fr);
				// astfel vom comunica cu clientul (primim si trimitem mesaje)
				FD_SET(ClientSocket[i], &fe);
			}
		}

		RetValue = select(maxFd + 1, &fr, &fw, &fe, &time);	// cati socket descriptori sunt gata de
		// citit(fread),scris(fwrite) si cati trimit exceptii(fexception)

		//asteapta o activitate de la unul dintre socket, &tv este timpul de asteptare

		// !!!! cand apelezi functia select , inainte ca aceasta sa returneze,
		// imi goleste socket descriptorii , deci trebuie sa ii setez iar (setare mai sus)

		if (RetValue < 0)
		{
			// daca functia select esueaza , aceasta returneaza -1
			Logger::getInstance()->showMsg("Select failed with error: " + std::to_string(WSAGetLastError()));
			WSACleanup();
			exit(EXIT_FAILURE);
		}

		if (RetValue > 0)	// nr de socket care desfasoara o activitate (conectare sau trimitere semnal)
		{
			if (aux == 0)
			{
				std::cout << std::endl;
				Logger::getInstance()->showMsg("Se proceseaza datele din port... ");
			}
			// cand cineva se conecteaza sau comunica un mesaj folosind o conexiune dedicata

			aux = 1;
			// procesarea cererilor
			ProcessNewRequest();
		}
		if (RetValue == 0)	//nu s-a inregistrat nicio activitate iar limita de timp s-a terminat
		{
			if (aux == 0)
			{
				std::cout << "\rDaca nu se conecteaza nimeni, serverul se va inchide in: " << counter << " secunde" << std::flush;
				Sleep(2);
				counter--;
				if (counter == -1)
				{
					std::cout << std::endl;
					DataBaseConn::getInstance()->destroyInstance();
					Logger::getInstance()->showMsg("Server inchis cu succes!");
					WSACleanup();
					exit(EXIT_FAILURE);
				}
			}
		// nu exista conexiune sau cereri de comunicare sau
		// socket descriptorii nu sunt pregatiti ( ready )
		}
	}
}

void Server::startServer()
{
	wsaInit();
	SocketInit();
	SockaddrInit();
	SocketOptions();
	Bind();
	Listen();
}
