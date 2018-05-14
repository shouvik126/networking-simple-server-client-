//programme for simple client
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/un.h>
void main()
{
	int client_sockid;//to store socket descriptor for client
	int client_len;    //to store client amd server structure size
	char out_buf[100],in_buf[100];//to store the sent and recieve message


	struct sockaddr_un client_address;//structure variable for client
	client_sockid=socket(AF_UNIX,SOCK_STREAM,0);//client descripter for client
	client_address.sun_family=AF_UNIX; //define the family EX-AF_UNIX(for local communication),AF_INET(ipv4)
	strcpy(client_address.sun_path,"server_socket");//assign "server_socket" file to current socket descriptor
	client_len=sizeof(client_address);//size of the structure sockaddr_un

	connect(client_sockid,(struct sockaddr *)&client_address,client_len);//connect to the server which is 
									     //in listen mode
	recv(client_sockid,in_buf,sizeof(in_buf),0);          //recieve message from server through client socket
							      //in 'in_buf'
	printf("recieve from server data......'%s'\n",in_buf);//printing recieved message
	strcpy(out_buf,"text message from client to server....");//store message at'out_buf' for sending to servr
	send(client_sockid,out_buf,(strlen(out_buf)+1),0);//message is sent to server descriptor through 'out_buf'
                                                          //and length is increase by 1 because to explicitely assign null 
                                                          //at the end of the stream
                                                                 
	close(client_sockid);//close client socket descriptor
}

