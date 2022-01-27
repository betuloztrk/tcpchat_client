#include <stdio.h>
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>
#include <sys/syscall.h>
#include "msgprotocol/msgprotocol.h"
#include "sendrecv/sendrecv.h"
#include "userbase/userbase.h"


void *receive_msg(void *ptr);
void *send_msg(void *ptr);
int system_exit(void);
void sig_handler(int signal);
int socket_desc;
struct sockaddr_in server_addr;
int server_struct_length = sizeof(server_addr);
char serialize[100];
protocol_t packet;
protocol_t *p = &packet;
pthread_t thread_recv,thread_send;
char data_buff[100] = {0};
char groupdata_buff[100] = {0};
//int my_id = 0xFF;

int cli_sock;
char nick_name[100];
char choice_name[100];
char group_name[100];
int group_id = 0;
char ch_one[100];

userinfo_t *userdata = NULL;

void *receive_msg(void *ptr)
{
	int packet_lenght = 0;
	int parsed_length = 0;
	int list_index = -1;

	while(1)
	{
		packet_lenght = recv(socket_desc,serialize,100,0);
		if(packet_lenght <= 0)
		{
			close(socket_desc);
			pthread_cancel(thread_recv);
			pthread_cancel(thread_send);
		}

		while((packet_lenght - parsed_length) > 0)
		{
			parsed_length += msgprotocol_parse(p, &serialize[parsed_length]);

			if(p->cmd == REGISTER)
			{
				printf("my id = %d\n", p->data[0]);
			}
			else if(p->cmd == USERDATA)
			{
				lastinsert(p->data[0],&p->data[1]);
				printf("%d sock : %s nick_name\n",p->data[0],&p->data[1]);
				memset(&p->data[1],0,sizeof(p->data));

			}
			else if(p->cmd == MESSAGE)
			{
				list_index = search(p->destination);
				if(list_index > -1)
				{
				    userdata = get_node_data(list_index-1);
					printf("message from %s for me : %s\n",userdata->nick_name,p->data);

				}
				memset(p->data,0,sizeof(p->data));
			}
			else if (p->cmd == GROUP_MSG)
			{
				printf("messsage from %d group for me : %s \n",p->data[0],&p->data[1]);
				//memset(p->data,0,sizeof(p->data));
			}

		}
		parsed_length = 0;
		memset(p,0,sizeof(protocol_t));
	}

}

void *send_msg(void *ptr)
{
	int comd;

	while(1)
	{
		printf("enter the cmd 1 :register 2: choıce 3 :message 6:group 7: group choice 8: group message\n");
		scanf("%d",&comd);
		//getchar();

		if(comd == REGISTER)
		{
			//my_id = 0xFF;
			printf("enter the nickname:");
			scanf("%s",&nick_name);

			p->destination = 0;

			p->len = strlen(nick_name);
			memcpy(p->data,nick_name,p->len);

		}
		else if(comd == MESSAGE)
		{
			printf("enter the message:\n");
			gets(data_buff);

			p->len= strlen(data_buff);
			memcpy(p->data,data_buff,p->len);
		}
		else if(comd == CHOICE)
		{
			printf("want you which client to message?\n");
			scanf("%s",choice_name);

			p->len = strlen(choice_name);
			memcpy(p->data,choice_name,p->len);
		}
		else if(comd == GROUP)
		{
			printf("enter the group name?\n");
			scanf("%s",group_name);

			p->len = strlen(group_name);
			memcpy(p->data,group_name,p->len);
		}
		else if(comd == GROUP_CHOICE)
		{
			printf("want you which clients make group?\n");
			scanf("%d",&cli_sock);

			printf("want you which group add client?\n");
			scanf("%d",&group_id);

			p->data[0] = cli_sock;
			p->data[1]= group_id;

			p->len = 2;

		}
		else if(comd == GROUP_MSG)
		{
			printf("want you which group send message ?\n");
			scanf("%d",&group_id);

			printf("enter the message:\n");
			gets(groupdata_buff);

			p->data[0]= group_id;

			p->len= strlen(groupdata_buff);
			memcpy(&p->data[1],groupdata_buff,p->len);
		}

		p->cmd = comd;
		//p->source = socket_desc;
		//memcpy(p->data,nick_name,p->len);

		sendrecv_send(p,socket_desc,serialize);

	}
}

void sig_handler(int signal)
{
	if(signal == SIGHUP)
	{
		printf("\nreceived SIGHUP\n");
	}
	else if(signal == SIGINT)
	{
		printf("\nreceived SIGINT\n");

		p->cmd = DELETE;
		p->destination = 0;

		p->len = strlen(nick_name);
		memcpy(p->data,nick_name,p->len);

		sendrecv_send(p,socket_desc,serialize);

		memset(p->data,0,p->len);
		system_exit();

	}
	else if(signal == SIGKILL)
	{
		printf("\nreceived SIGKILL\n");
	}
	else if(signal == SIGPIPE)
	{
		printf("\nreceived SIGPIPE\n");
		system_exit();
	}
	else if(signal == SIGQUIT)
	{
		printf("\nreceived SIGQUIT\n");
	}
}


int main()
{
		socket_desc = socket(AF_INET , SOCK_STREAM , 0);
		if(socket_desc < 0)
		{
			printf("Error while creating socket\n");
			return -1;
		}

		printf("Socket created successfully\n");

		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(2005);
		server_addr.sin_addr.s_addr = inet_addr("192.168.43.153");

		if (connect(socket_desc ,(struct sockaddr *)&server_addr , sizeof(server_addr)) < 0)
		{
			printf("connect failed. Error");
			return 1;
		}

		printf("Connected\n");

		pthread_create( &thread_send, NULL, send_msg, NULL);
		pthread_create( &thread_recv, NULL, receive_msg, NULL);

		signal(SIGHUP,sig_handler);
		signal(SIGINT,sig_handler);
		signal(SIGKILL,sig_handler);
		signal(SIGPIPE,sig_handler);
		signal(SIGQUIT,sig_handler);

		pthread_join(thread_send ,NULL);
		pthread_join(thread_recv ,NULL);

		return 0;
}

int system_exit(void)
{
	pthread_cancel(thread_recv);
	pthread_cancel(thread_send);
	close(socket_desc);
	shutdown(socket_desc,3);
	printf("closing socket\n");

	return 0;
}

