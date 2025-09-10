static int server_fd;
struct NS ns_p[SMPT_NWuU];

void ns_set()
{
//	SMPTTmE

	SMPT_DBmR2L("socket %d", server_fd = socket(AF_INET, SOCK_DGRAM, 0))
//	SMPTTmE

	SMPT_DBmR2L("fcntl %d", fcntl(server_fd, F_SETFL, fcntl(server_fd, F_GETFL, 0) | O_NONBLOCK))
////	SMPTTmE

	struct sockaddr_in server_sockaddr_in;
	memset(&server_sockaddr_in, 0, sizeof(struct sockaddr_in));
	server_sockaddr_in.sin_family = AF_INET;
	server_sockaddr_in.sin_addr.s_addr = INADDR_ANY;
	server_sockaddr_in.sin_port = SMPTuPORT;
	SMPT_DBmR2L("bind %d", bind(server_fd, (struct sockaddr*)&server_sockaddr_in, sizeof(server_sockaddr_in)))
//	SMPTTmE
}

void ns_send(SMPT_NWtU u)
{
	smptr_svMsend(u);
	sendto(server_fd, smptr_svPnet[u].Pnet, smptr_svPnet[u].Lnet, 0, (struct sockaddr *)&ns_p[u].client_sockaddr_in, ns_p[u].client_sockaddr_in_bl);
//	SMPTTmE
}

static struct sockaddr_in client_sockaddr_in = {0};
static socklen_t client_sockaddr_in_bl = sizeof(client_sockaddr_in);
void ns_get()
{
	if (recvfrom(server_fd, smptr_svPnet[0].Pnet, SMPTRlNET, 0, (struct sockaddr*)&client_sockaddr_in, &client_sockaddr_in_bl) > 0)
	{
		//SMPT_DBmN2L("S smptr_svPnet[0].Lnet %d", smptr_svPnet[0].Lnet)
		SMPT_DBmN2L("client_sockaddr_in.sin_addr.s_addr %d", client_sockaddr_in.sin_addr.s_addr)
		SMPT_DBmN2L("client_sockaddr_in.sin_port %d", client_sockaddr_in.sin_port)
		for (SMPT_NWtU l0 = 0; l0 < SMPT_NWuU; ++l0)
		{
			//SMPT_DBmN2L("smpt_nwPu[l0] %d", smpt_nwPu[l0])
			if (client_sockaddr_in.sin_addr.s_addr == smpt_nwPu[l0])
			{
				ns_p[l0].client_sockaddr_in = client_sockaddr_in;
				ns_p[l0].client_sockaddr_in_bl = client_sockaddr_in_bl;
				smptr_svMread();
				break;
			}
		}
	}
//	SMPTTmE
}

void ns_free()
{
	close(server_fd);
}
