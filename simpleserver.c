//programme for simple server
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/un.h>
void main()
{
	int server_sockid, client_sockid;//to store socket descriptor for server and client
	int server_len,client_len;       //to store client amd server structure size
	char out_buf[100],in_buf[100];   //to store the sent and recieve message
	struct sockaddr_un server_address;//structure variable for server
	struct sockaddr_un client_address;//structure variable for client

	unlink("server_socket");          //deleate the name from the file system
					  //means the name or process which  last
					  //link to the file"server_socket" and ensure 
					  //that no other process also opened that file
					  //then the space used by that name or process
					  //is deleated 
	server_sockid=socket(AF_UNIX, SOCK_STREAM, 0);//socket descripter for server
	server_address.sun_family=AF_UNIX;            //define the family EX-AF_UNIX(for local communication),AF_INET(ipv4)
	strcpy(server_address.sun_path,"server_socket");//assign "server_socket" file to current socket descriptor
	server_len=sizeof(server_address);              //size of the structure sockaddr_un
	bind(server_sockid,(struct sockaddr *)&server_address,server_len);//bind the server socket with the family
									  //and path defined above
	
	listen(server_sockid,5);                        //server goes to listen mode and wait for client
	client_len=sizeof(client_address);              //size of the structure sockaddr_un
	client_sockid=accept(server_sockid, (struct sockaddr *)&client_address, &client_len);//connection established
											     //store the client descriptor at 
											     //'client_sockid'
	strcpy(out_buf, "A text message from server to client");//store message at'out_buf' for sending to client
	send(client_sockid, out_buf, (strlen(out_buf)+1), 0);   //message is sent to client descriptor through 'out_buf'
								//and length is increase by 1 because to explicitely assign null 
								//at the end of the stream
	recv(client_sockid,in_buf,sizeof(in_buf),0);            //recieving message from client socket descriptor through 'in_buf'
	printf("Recieved from client----data=%s\n",in_buf);     //printing message

	close(server_sockid);//closing 2 descriptor
	close(client_sockid);
}
