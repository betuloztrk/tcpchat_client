/*
 * msgprotocol.h
 *
 *  Created on: Dec 3, 2021
 *      Author: user
 */

#ifndef MSGPROTOCOL_MSGPROTOCOL_H_
#define MSGPROTOCOL_MSGPROTOCOL_H_

/* İncludes **************************************************************/
#include <stdint.h>
#include <stdio.h>


/* Defines **************************************************************/
typedef enum
{
	REGISTER = 1,
	CHOICE = 2,
	MESSAGE = 3,
	USERDATA = 4,
	DELETE = 5,
	GROUP =6,
	GROUP_CHOICE =7,
	GROUP_MSG,


};


/*Types *****************************************************************/
typedef struct protocol_t
{
	uint8_t destination;
	uint8_t source;
	uint8_t cmd;
	uint8_t len;
	char data[255];
}protocol_t;


/* Functions **************************************************************/

extern void msgprotocol_serialize(protocol_t *packet,char *serialize);
extern int msgprotocol_parse(protocol_t *packet,char *serialize);

/*Variables *************************************************************/

#endif /* MSGPROTOCOL_MSGPROTOCOL_H_ */
