const uint32_t ns_u_p[_RB_UM] =
{
	//.c client ip
	NALI_M_IP(127, 0, 0, 1)
};

static int server_fd;
NS ns_p[_RB_UM];

void ns_set()
{
	_DB_R2L("socket %d", server_fd = socket(AF_INET, SOCK_DGRAM, 0))
//	_DB_N2L("%s", strerror(errno))

	_DB_R2L("fcntl %d", fcntl(server_fd, F_SETFL, fcntl(server_fd, F_GETFL, 0) | O_NONBLOCK))
//	_DB_N2L("%s", strerror(errno))

	struct sockaddr_in server_sockaddr_in;
	memset(&server_sockaddr_in, 0, sizeof(struct sockaddr_in));
	server_sockaddr_in.sin_family = AF_INET;
	server_sockaddr_in.sin_addr.s_addr = INADDR_ANY;
	server_sockaddr_in.sin_port = htons(NALI_SC_PORT);
	_DB_R2L("bind %d", bind(server_fd, (struct sockaddr*)&server_sockaddr_in, sizeof(server_sockaddr_in)))
//	_DB_N2L("%s", strerror(errno))
}

void ns_send(_RB_UT ui)
{
	sendto(server_fd, ls_net_p, ls_net_bl, 0, (struct sockaddr *)&ns_p[ui].client_sockaddr_in, ns_p[ui].client_sockaddr_in_bl);
}

static struct sockaddr_in client_sockaddr_in;
static socklen_t client_sockaddr_in_bl = sizeof(client_sockaddr_in);
static ssize_t r;
void ns_get()
{
	r = recvfrom(server_fd, ls_net_p, _RB_NET_BL, 0, (struct sockaddr*)&client_sockaddr_in, &client_sockaddr_in_bl);

	if (r == sizeof(_RB_PT))
	{
		for (_RB_UT l_0 = 0; l_0 < _RB_UM; ++l_0)
		{
			// client_sockaddr_in.sin_port;
			if (client_sockaddr_in.sin_addr.s_addr == ns_u_p[l_0])
			{
				ns_p[l_0].client_sockaddr_in = client_sockaddr_in;
				ns_p[l_0].client_sockaddr_in_bl = client_sockaddr_in_bl;
				ls_read(l_0);
				break;
			}
		}
	}
}

static int errno_temp = 0;
void ns_check()
{
	if (errno != errno_temp)
	{
		_DB_W2L("ns_errno %d %s", errno, strerror(errno))
	}
	errno_temp = errno;
}

void ns_free()
{
	close(server_fd);
}
