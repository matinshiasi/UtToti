#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "header.h"

#define TRUE 1

int main()
{
    int order_num, quit, flag, postid = 1;
    user *head = NULL;

    while (TRUE)
    {
        // declare our variables with dynamic array
        char *order = (char *)malloc(sizeof(char));
        char *username = (char *)malloc(sizeof(char));
        char *password = (char *)malloc(sizeof(char));
        char *text = (char *)malloc(sizeof(char));
        int *postnumber = (int *)malloc(sizeof(int));
        user *user1;

        strInput(order); // gets onput order
        order_num = ordernum(order); // then convert it to number

        switch (order_num)
        {
        case 1: // signup
            strInput(username);
            strInput(password);
            signup(&head, username, password); 
            printf("\n");
            break;

        case 2: // login
            strInput(username);
            strInput(password);

            user1 = login(head, username, password);
            if (user1 == NULL)
                quit = 0; // not allowed to continue
            else
                quit = 1; // allowed to continue
            printf("\n");
            break;

        case 10: // print list of users
            printList(head);
            break;
        }
        while (quit)
        {
            strInput(order);
            order_num = ordernum(order);

            switch (order_num)
            {
            case 3: // post
                postInput(text); // press enter at the end
                postf(user1, text, postid);
                break;

            case 4: // like
                strInput(username);
                strInput(postnumber);
                like(head, username, postnumber);
                break;

            case 5: // logout
                printf("\nyou logged out\n");
                quit = 0;
                break;

            case 6: // delete
                strInput(postnumber); // it just gets the number
                delete (user1, postnumber);
                break;

            case 7: // info
                info(user1);
                break;

            case 8: // find user
                strInput(username);
                find_user(head, username);

            case 9: // unvalid order
                quit = 1;
                break;
            }
        }
    }
    return 0;
}