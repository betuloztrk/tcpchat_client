

#ifndef SENDRECV_SENDRECV_H_
#define SENDRECV_SENDRECV_H_

/* İncludes **************************************************************/
#include <stdint.h>
#include <stdio.h>
#include "../msgprotocol/msgprotocol.h"

/* Functions **************************************************************/


extern void sendrecv_send(protocol_t *packet,int socket_desc,char *serialize);
//extern void sendrecv_recv(protocol_t *packet,int socket_desc,char *serialize);



//extern int comd,id;


#endif /* SENDRECV_SENDRECV_H_ */
