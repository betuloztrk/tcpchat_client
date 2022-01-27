
#ifndef USERBASE_USERBASE_H_
#define USERBASE_USERBASE_H_

#include <string.h>


/*Types *****************************************************************/
typedef struct {
	int sock;
	char group_name[100];
	char nick_name[100];

}userinfo_t;


struct node
{
	userinfo_t data;
    struct node *next;
};



extern int lastinsert(int sock , char name[100]);
extern int display(void);
extern int search(int sock);
extern userinfo_t *get_node_data(int index);
extern int insert_group(char groupname[100]);


#endif /* USERBASE_USERBASE_H_ */
