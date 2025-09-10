static int server_fd;
static struct sockaddr_in server_sockaddr_in = {0};
static socklen_t server_sockaddr_in_bl = sizeof(server_sockaddr_in);

void nc_set()
{
//	SMPTTmE

	SMPT_DBmR2L("socket %d", server_fd = socket(AF_INET, SOCK_DGRAM, 0))
//	SMPTTmE

	SMPT_DBmR2L("fcntl %d", fcntl(server_fd, F_SETFL, fcntl(server_fd, F_GETFL, 0) | O_NONBLOCK))
//	SMPTTmE

	server_sockaddr_in.sin_family = AF_INET;
	server_sockaddr_in.sin_addr.s_addr = SMPT_NWuIP;
	server_sockaddr_in.sin_port = SMPTuPORT;
//	SMPTTmE
}

void nc_send()
{
	smptr_ceMsend();
	sendto(server_fd, smptr_cePnet, smptr_ceLnet, 0, (struct sockaddr *)&server_sockaddr_in, server_sockaddr_in_bl);
//	SMPTTmE
}

void nc_get()
{
	if (recvfrom(server_fd, smptr_cePnet, SMPTRlNET, 0, (struct sockaddr*)&server_sockaddr_in, &server_sockaddr_in_bl) > 0)
	{
		smptr_ceMread();
	}
}

void nc_free()
{
	close(server_fd);
}
