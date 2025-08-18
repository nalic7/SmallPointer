const uint32_t ns_u_p[NALI_LB_UM] =
{
	//.c client ip
	NALI_M_IP(127, 0, 0, 1)
};

static int server_fd;
NS ns_p[NALI_LB_UM];

void ns_set()
{
	NALI_D_INFO("socket %d", server_fd = socket(AF_INET, SOCK_DGRAM, 0))
	NALI_D_LOG("%s", strerror(errno))

	NALI_D_INFO("fcntl %d", fcntl(server_fd, F_SETFL, fcntl(server_fd, F_GETFL, 0) | O_NONBLOCK))
	NALI_D_LOG("%s", strerror(errno))

	struct sockaddr_in server_sockaddr_in;
	memset(&server_sockaddr_in, 0, sizeof(struct sockaddr_in));
	server_sockaddr_in.sin_family = AF_INET;
	server_sockaddr_in.sin_addr.s_addr = INADDR_ANY;
	server_sockaddr_in.sin_port = htons(NALI_SC_PORT);
	NALI_D_INFO("bind %d", bind(server_fd, (struct sockaddr*)&server_sockaddr_in, sizeof(server_sockaddr_in)))
	NALI_D_LOG("%s", strerror(errno))
}

void ns_send(NALI_LB_UT ui)
{
	sendto(server_fd, ls_net_p, ls_net_bl, 0, (struct sockaddr *)&ns_p[ui].client_sockaddr_in, ns_p[ui].client_sockaddr_in_bl);
}

static struct sockaddr_in client_sockaddr_in;
static socklen_t client_sockaddr_in_bl = sizeof(client_sockaddr_in);
static ssize_t r;
void ns_get()
{
	r = recvfrom(server_fd, ls_net_p, NALI_LB_NET_BL, 0, (struct sockaddr*)&client_sockaddr_in, &client_sockaddr_in_bl);

	if (r == sizeof(NALI_LB_PT))
	{
		for (NALI_LB_UT l_0 = 0; l_0 < NALI_LB_UM; ++l_0)
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
		NALI_D_INFO_A("ns_errno %d %s", errno, strerror(errno))
	}
	errno_temp = errno;
}

void ns_free()
{
	close(server_fd);
}
