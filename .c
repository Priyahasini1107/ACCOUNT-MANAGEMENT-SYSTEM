#include <stdio.h>
#include <string.h>

struct person 
{
    char userID[20];
    char password[20];
    int attempts;
    int locked;
};

struct person users[10];
int k = 0;

int create();
int login();
int deletee();
int display();
int unlockAcct();
int changePass();

int main() 
{
    int opt;
    char ch;

    do 
    {
        printf("\n\tOptions\n");
        printf("---------------\n");
        printf("1. Create Account\n");
        printf("2. Login\n");
        printf("3. Delete Account\n");
        printf("4. Display All Accounts\n");
        printf("5. Unlock Account\n");
        printf("6. Change Password\n");
        printf("Enter your option: ");
        scanf("%d", &opt);

        switch (opt) 
        {
            case 1: create();
                    break;
            case 2: login();
                    break;
            case 3: deletee();
                    break;
            case 4: display();
                    break;
            case 5: unlockAcct();
                    break;
            case 6: changePass();
                    break;
            default: printf("Wrong Option\nTry Again\n");
        }

        printf("Do you want to continue? (y/n): ");
        scanf(" %c", &ch);
    } while (ch == 'y' || ch == 'Y');

    return 0;
}

int create() 
{
    if (k >= 10) 
    {
        printf("Maximum number of accounts reached.\n");
        return 0;
    }

    char newUserID[20];
    int acctExists,i;

    do 
    {
        acctExists = 0;
        printf("Enter User ID: ");
        scanf("%s", newUserID);

        for (i = 0; i < k; i++) 
        {
            if (strcmp(users[i].userID, newUserID) == 0)
            {
                acctExists = 1;
                break;
            }
        }

        if (acctExists) 
        {
            printf("Account '%s' already exists. Please enter a different User ID.\n", newUserID);
        }
    } while (acctExists);  

    strcpy(users[k].userID, newUserID);

    printf("Enter Password: ");
    scanf("%s", users[k].password);

    users[k].attempts = 0;
    users[k].locked = 0;

    printf("Account Created Successfully\n");
    k++;
    return 0;
}

int login() 
{
    char id[20], pass[20];
    int i, found = 0;

    printf("Enter User ID: ");
    scanf("%s", id);

    for (i = 0; i < k; i++) 
    {
        if (strcmp(users[i].userID, id) == 0) 
        {
            found = 1;

            if (users[i].locked) 
            {
                printf("This account is locked due to multiple failed login attempts.\n");
                return 0;
            }

            printf("Enter Password: ");
            scanf("%s", pass);

            if (strcmp(users[i].password, pass) == 0)
            {
                printf("Login Successful\n");
                users[i].attempts = 0;
            } 
            else 
            {
                users[i].attempts++;
                printf("Incorrect password. Attempt %d of 3\n", users[i].attempts);
                if (users[i].attempts >= 3) 
                {
                    users[i].locked = 1;
                    printf("Account locked due to 3 failed attempts.\n");
                }
            }
            return 0;
        }
    }

    if (!found) 
    {
        printf("User ID not found.\n");
    }

    return 0;
}

int changePass() 
{
    char id[20], pass[20], newPass[20];
    int i, found = 0;

    printf("Enter User ID: ");
    scanf("%s", id);
    
    for (i = 0; i < k; i++) 
    {
        if (strcmp(users[i].userID, id) == 0) 
        {
            found = 1;
            
            if (users[i].locked) 
            {
                printf("This account is locked due to multiple failed login attempts.\n");
                return 0;
            }

            printf("Enter current Password: ");
            scanf("%s", pass);

            if (strcmp(users[i].password, pass) == 0)
            {
                printf("Enter new Password: ");
                scanf("%s", newPass);
                strcpy(users[i].password, newPass);
                printf("Password changed successfully.\n");
            } 
            else 
            {
                printf("Incorrect current password.\n");
            }
            break;
        }
    }

    if (!found) 
    {
        printf("User ID not found.\n");
    }

    return 0;
}

int deletee() 
{
    char id[20], pass[20];
    int i, j, found = 0;

    printf("Enter User ID: ");
    scanf("%s", id);

    printf("Enter Password: ");
    scanf("%s", pass);

    for (i = 0; i < k; i++) 
    {
        if (strcmp(users[i].userID, id) == 0 && strcmp(users[i].password, pass) == 0) 
        {
            for (j = i; j < k - 1; j++) 
            {
                users[j] = users[j + 1];
            }
            k--;
            printf("Account Has Been Deleted Successfully\n");
            found = 1;
            break;
        }
    }

    if (!found) 
    {
        printf("Account Not Found\n");
    }

    return 0;
}

int display() 
{
    if (k == 0) 
    {
        printf("No Accounts Available.\n");
    } 
    else 
    {
        printf("\nList of Accounts:\n");
        for (int i = 0; i < k; i++) 
        {
            printf("User ID: %s\n", users[i].userID);
            printf("Password: %s\n", users[i].password);
            printf("Status: %s\n", users[i].locked ? "Locked" : "Active");
            printf("-------------------\n");
        }
    }
    return 0;
}

int unlockAcct() 
{
    char id[20];
    int i, found = 0;

    printf("Enter the User ID to unlock: ");
    scanf("%s", id);

    for (i = 0; i < k; i++) 
    {
        if (strcmp(users[i].userID, id) == 0) 
        {
            users[i].locked = 0;
            users[i].attempts = 0;
            printf("Account '%s' has been unlocked.\n", users[i].userID);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("User ID not found.\n");
    }

    return 0;
}
