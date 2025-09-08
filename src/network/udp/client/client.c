static int server_fd;
static struct sockaddr_in server_sockaddr_in;
static socklen_t server_sockaddr_in_bl = sizeof(server_sockaddr_in);

void nc_set()
{
	SMPT_DBmR2L("socket %d", server_fd = socket(AF_INET, SOCK_DGRAM, 0))
	//SMPT_DBmN2L("%s", strerror(errno))

	SMPT_DBmR2L("fcntl %d", fcntl(server_fd, F_SETFL, fcntl(server_fd, F_GETFL, 0) | O_NONBLOCK))
	//SMPT_DBmN2L("%s", strerror(errno))

	server_sockaddr_in.sin_family = AF_INET;
	server_sockaddr_in.sin_port = htons(SMPTuPORT);
	server_sockaddr_in.sin_addr.s_addr = NALI_NC_IP;
	// SMPT_DBmR2L("inet_pton %d", inet_pton(AF_INET, NALI_NC_IP, &server_sockaddr_in.sin_addr))
	//SMPT_DBmN2L("%s", strerror(errno))

	lcu_send();
}

void nc_send()
{
	sendto(server_fd, smptr_cePnet, smptr_ceLnet, 0, (struct sockaddr *)&server_sockaddr_in, server_sockaddr_in_bl);
}

void nc_get()
{
	if (recvfrom(server_fd, smptr_cePnet, SMPTRB_NET_BL, 0, (struct sockaddr*)&server_sockaddr_in, &server_sockaddr_in_bl) > 0)
	{
		lc_read();
	}
}

static int errno_temp = 0;
void nc_check()
{
	if (errno != errno_temp)
	{
		SMPT_DBmW2L("c %d %s", errno, strerror(errno))
	}
	errno_temp = errno;
}

void nc_free()
{
	close(server_fd);
}
