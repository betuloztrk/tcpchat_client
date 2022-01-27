#include<stdio.h>
#include<stdlib.h>
#include "userbase.h"


struct node *head = NULL;

int lastinsert(int sock , char name[100])
{
    struct node *newnode,*temp;
    newnode = (struct node*)malloc(sizeof(struct node));
    if(newnode == NULL)
    {
        printf("OVERFLOW\n");
        return -1;
    }
    else
    {
    	//memcpy(&newnode->data,userinfo,sizeof(userinfo_t));
        newnode->data.sock = sock;
        strcpy(newnode->data.nick_name,name);
        if(head == NULL)
        {
            newnode -> next = NULL;
            head = newnode;
           // printf("Node inserted\n");
        }
        else
        {
            temp = head;
            while (temp -> next != NULL)
            {
                temp = temp -> next;
            }
            temp->next = newnode;
            newnode->next = NULL;
            //printf("Node inserted\n");
        }
    }
    return 0;
}

int insert_group(char groupname[100])
{
    struct node *newnode,*temp;
    newnode = (struct node*)malloc(sizeof(struct node));
    if(newnode == NULL)
    {
        printf("OVERFLOW\n");
        return -1;
    }
    else
    {
    	//memcpy(&newnode->data,userinfo,sizeof(userinfo_t));
        strcpy(newnode->data.group_name,groupname);
        if(head == NULL)
        {
            newnode -> next = NULL;
            head = newnode;
           // printf("Node inserted\n");
        }
        else
        {
            temp = head;
            while (temp -> next != NULL)
            {
                temp = temp -> next;
            }
            temp->next = newnode;
            newnode->next = NULL;
            //printf("Node inserted\n");
        }
    }
    return 0;
}

int search(int sock)
{
    struct node *newnode;
    int i=0;
    int flag=1;
    newnode = head;
    if(newnode == NULL)
    {
        printf("Empty List\n");
    }
    else
    {
        while (newnode!=NULL)
        {
            if((newnode->data.sock == sock))
            {
                printf("sock found at location %d\n",i+1);
                flag=0;
                return i+1;
            }
            else
            {
                //flag=1;
            }
            i++;
            newnode = newnode-> next;
        }

        if(flag==1)
        {
        	printf("nick_name not found\n");
        }
    }
    return -1;
}

userinfo_t *get_node_data(int index)
{
    struct node *newnode;
    int i=0;

    newnode = head;
    if(newnode == NULL)
    {
        printf("Empty List\n");
    }
    else
    {
        for(i=0; i <= index ; i++)
        {
        	  if(i == index)
        	  {
        		  return &newnode->data;

        	  }
        	  else
        	  {
        		  newnode = newnode-> next;
        	  }
        }
    }
    return NULL;
}

int display(void)
{
    struct node *newnode;
    newnode = head;
    if(newnode == NULL)
    {
        printf("all node deleted,nothing to print\n");
        return -1;
    }
    else
    {
        printf("socket numbers and member ıd :\n");
        while (newnode!=NULL)
        {
            printf("%u sock : %s\n",newnode->data.sock,newnode->data.nick_name);
            newnode = newnode -> next;
        }

    }
    return 0;
}
