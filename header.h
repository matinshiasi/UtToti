struct post
{
    int post_id;
    int like;
    char *text;
    struct post *next;
};

struct user
{
    char *username;
    char *password;
    struct users *next;
    struct post *pnext;
};

typedef struct post post;
typedef struct user user;

void strInput(char *order) // this function helps to get input into dynamic array
{
    int length = 0, ch;
    while ((ch = getche()) != ' ') // spilit words with space
    {
        *(order + length) = ch;
        order = (char *)realloc(order, sizeof(char) * (length + 2));
        length++;
    }
    *(order + length) = '\0'; 
}

void signup(user **head, char *username, char *password)
{
    user *newuser = (user *)malloc(sizeof(user));
    newuser->username = username;
    newuser->password = password;
    newuser->next = NULL;
    newuser->pnext = NULL;
    if (*head == NULL) // if it was first signup
        *head = newuser;
    else // otherwise it joins at the end of list
    {
        user *lastuser = *head;
        while (lastuser->next != NULL)
        {
            lastuser = lastuser->next;
        }
        lastuser->next = newuser;
    }
}

user *login(user *head, char *username, char *password) // the type of function should be user
{
    user *temp = head;
    while (temp != NULL) // search between usernames
    {
        if (strcmp(temp->username, username) == 0)
        {
            if (strcmp(temp->password, password) == 0) // check password
            {
                printf("\nlogin sucsesful");
                return temp; // if login was sucsesful we return the user value
            }
            else
            {
                printf("\nwrong password");
                return NULL;
            }
        }
        temp = temp->next;
    }
    printf("\nusername not found");
    return NULL;
}

void find_user(user *head, char *username)
{
    int flag = 0;
    user *temp = head;
    post *pnode = temp->pnext;
    while (temp != NULL) // search between usernames
    {
        if (strcmp(temp->username, username) == 0)
        {
            flag = 1;
            // print the datas
            printf("\nusername: %s\n", temp->username);
            printf("-------------------------\n");
            while (pnode != NULL)
            {
                printf("caption: %s\n", pnode->text);
                printf("post id: %d\n", pnode->post_id);
                printf("likes: %d\n", pnode->like);
                printf("-------------------------\n");
                pnode = pnode->next;
            }
        }
        temp = temp->next;
    }
    if (flag == 0)
        printf("user not found. try again!\n");
}

int ordernum(char *order) // this function convert the input order into number
{
    int order_num;
    if (strcmp(order, "signup") == 0)
        order_num = 1;
    else if (strcmp(order, "login") == 0)
        order_num = 2;
    else if (strcmp(order, "post") == 0)
        order_num = 3;
    else if (strcmp(order, "like") == 0)
        order_num = 4;
    else if (strcmp(order, "logout") == 0)
        order_num = 5;
    else if (strcmp(order, "delete") == 0)
        order_num = 6;
    else if (strcmp(order, "info") == 0)
        order_num = 7;
    else if (strcmp(order, "find_user") == 0)
        order_num = 8;
    else if (strcmp(order, "print") == 0)
        order_num = 10;
    else
    {
        printf("\nUnvalid order. try again!\n");
        order_num = 9;
    }
    return order_num;
}

void printList(user *head) // print the list of users that signed up before
{
    user *temp = head;
    while (temp != NULL)
    {
        printf("\nusername: %s\tpassword: %s", temp->username, temp->password);
        temp = temp->next;
    }
    printf("\n");
}

void postf(user *user1, char *text, int postid) 
{
    post *newpost = (post *)malloc(sizeof(post));
    newpost->next = NULL;
    if (user1->pnext == NULL)
    {
        user1->pnext = newpost;
    }
    else
    {
        post *lastpost = user1->pnext;
        while (lastpost->next != NULL) // at the post to the end of the list
        {
            lastpost = lastpost->next;
        }
        lastpost->next = newpost;
    }
    // put all input vlues for post
    newpost->text = text;
    newpost->post_id = postid;
    newpost->like = 0;
    postid++;
}

void postInput(char *order) // helps to get input string into dynamic array
{
    int length = 0, ch;
    while ((ch = getchar()) != '\n') // at the end of line press enter
    {
        *(order + length) = ch;
        order = (char *)realloc(order, sizeof(char) * (length + 2));
        length++;
    }
    *(order + length) = '\0';
}

void delete(user *user1, int *postnumber)
{
    int flag = 0;
    post *current = user1->pnext;
    while (current->next != NULL)
    {
        if (current->next->post_id == postnumber) // when reach to the post
        {
            current->next = current->next->next; // connect it to the next node
            free(current->next);
            printf("\npost deleted\n");
            flag = 1;
            break;
        }
        else
            current = current->next;
    }
    if (flag == 0)
        printf("\npost id unvalid\n");
}

void like(user *head, char *username, int *postnumber)
{
    int flag = 0;
    user *temp = head;
    while (temp != NULL) // check the userames
    {
        if (strcmp(temp->username, username) == 0) // untill reach to that
        {
            while (temp->pnext->post_id != postnumber) // find the postnumber
            {
                temp->pnext = temp->pnext->next;
            }
            (temp->pnext->like)++; // add one like to the post
            printf("\nyou liked %dth post\n", temp->pnext->post_id);
            flag = 1;
        }
        temp = temp->next;
    }
    if (flag == 0)
        printf("user not found. try again!\n");
}

void info(user *user1)
{
    post *pnode;
    pnode = user1->pnext; // temporary variable
    printf("\n");
    // print the datas
    printf("username: %s\n", user1->username);
    printf("password: %s\n", user1->password);
    printf("-------------------------\n");
    while (pnode != NULL)
    {
        printf("caption: %s\n", pnode->text);
        printf("post id: %d\n", pnode->post_id);
        printf("likes: %d\n", pnode->like);
        printf("-------------------------\n");

        pnode = pnode->next;
    }
}
