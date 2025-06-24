static int server_fd;
static struct sockaddr_in server_sockaddr_in;
static socklen_t server_sockaddr_in_bl = sizeof(server_sockaddr_in);

void nc_set()
{
	NALI_D_INFO("socket %d", server_fd = socket(AF_INET, SOCK_DGRAM, 0))
	NALI_D_LOG("%s", strerror(errno))

	NALI_D_INFO("fcntl %d", fcntl(server_fd, F_SETFL, fcntl(server_fd, F_GETFL, 0) | O_NONBLOCK))
	NALI_D_LOG("%s", strerror(errno))

	server_sockaddr_in.sin_family = AF_INET;
	server_sockaddr_in.sin_port = htons(NALI_SC_PORT);
	NALI_D_INFO("inet_pton %d", inet_pton(AF_INET, NALI_NC_IP, &server_sockaddr_in.sin_addr))
	NALI_D_LOG("%s", strerror(errno))

	lcu_send();
}

void nc_send()
{
	sendto(server_fd, lc_net_p, lc_net_bl, 0, (struct sockaddr *)&server_sockaddr_in, server_sockaddr_in_bl);
}

static ssize_t r;
void nc_get()
{
	r = recvfrom(server_fd, lc_net_p, NALI_LB_NET_BL, 0, (struct sockaddr*)&server_sockaddr_in, &server_sockaddr_in_bl);

	if (r > 0)
	{
		lc_read();
	}
}

static int errno_temp = 0;
void nc_check()
{
	if (errno != errno_temp)
	{
		NALI_D_INFO_A("c %d %s", errno, strerror(errno))
	}
	errno_temp = errno;
}

void nc_free()
{
	close(server_fd);
}