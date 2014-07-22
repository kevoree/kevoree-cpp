#include "PortSocketDomainLocal.h"

#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <unistd.h>

PortSocketDomainLocal::PortSocketDomainLocal()
{




}
PortSocketDomainLocal::PortSocketDomainLocal(std::string name){
	struct sockaddr_un addr;
	char buf[100];
	int fd,cl,rc;

	const char *socket_path =name.c_str();
	//const char *socket_path = ""+port->path().c_str();

	if ( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("socket error");

	}

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);

	unlink(socket_path);

	if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
		perror("bind error");

	}

	if (listen(fd, 5) == -1) {
		perror("listen error");

	}

	while (1) {
		if ( (cl = accept(fd, NULL, NULL)) == -1) {
			perror("accept error");
			continue;
		}

		while ( (rc=read(cl,buf,sizeof(buf))) > 0) {
			printf("read %u bytes: %.*s\n", rc, rc, buf);
		}
		if (rc == -1) {
			perror("read");
			exit(-1);
		}
		else if (rc == 0) {
			printf("EOF\n");
			close(cl);
		}
	}

}
PortSocketDomainLocal::~PortSocketDomainLocal()
{

}

