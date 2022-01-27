
/* Includes **************************************************************/
#include "msgprotocol.h"
#include <stdio.h>
#include <sys/socket.h>
#include <stdint.h>
/* Frame **************************************************************
 * [ destination,cmd,source,length,data]
 */

// javadoc
/**
 * @return void
 */
/* Functions *************************************************************/

void msgprotocol_serialize(protocol_t *packet,char *serialize)
{
	serialize[0] = packet->destination;
	serialize[1] = packet->cmd;
	serialize[2] = packet->source;
	serialize[3] = packet->len;

	for(int i=0; i < packet->len; i++)
	{

		serialize[i+4] = packet->data[i];
	}
}

int msgprotocol_parse(protocol_t *packet,char *serialize)
{
	uint8_t i = 0;

	packet->destination = serialize[i++];
	packet->cmd = serialize[i++];
	packet->source = serialize[i++];
	packet->len= serialize[i++];

	for(int j=0; j < packet->len; j++)
	{
		packet->data[j] = serialize[i++];
	}

	return i;
}






