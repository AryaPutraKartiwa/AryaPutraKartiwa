#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct mbek
{
    char id[10];
    char name[100];
    char color[100];
    int weight;
    int age;
    int height;
    mbek* left;
    mbek* right;
};

mbek* genNode(char id[10],char name[100],char color[100],int weight,int age)
{
    mbek* newNode = (mbek*) malloc(sizeof(mbek));

    strcpy(newNode->id,id);
    strcpy(newNode->name,name);
    strcpy(newNode->color,color);
    newNode->weight = weight;
    newNode->age = age;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
    
}

int getHeight(mbek* root)
{
    if(!root)
    {
        return 0;
    }
    return root->height;
}

int max(int a,int b)
{
    if(a > b)
    {
        return a;
    }
    else if(a < b)
    {
        return b;
    }
    return NULL;
}
int balanceFactor(mbek* root)
{
    return getHeight(root->left) - getHeight(root->right);
}
void heightUpdate(mbek* root)
{
    root->height = max(getHeight(root->left),getHeight(root->right)) + 1;
}

mbek* rotateLeft(mbek* root)
{
    mbek* child = root->right;
    mbek* gchild = root->left;

    child->left = root;
    root->right = gchild;

    heightUpdate(root);
    heightUpdate(gchild);

    return child;
}

mbek* rotateRight(mbek* root)
{
    mbek* child = root->left;
    mbek* gchild = root->right;

    child->right = root;
    root->left = gchild;

    heightUpdate(root);
    heightUpdate(gchild);

    return child;
}

mbek* rebalance(mbek* root)
{
    int bfac = balanceFactor(root);

    if(bfac > 1)
    {
        if(balanceFactor(root->left) < 0)
        {
            root->left = rotateLeft(root->left);
        }

        root = rotateRight(root);
    }
    else if(bfac < -1)
    {
        if(balanceFactor(root->right) > 0)
        {
            root->right = rotateRight(root->right);
        }
        root = rotateLeft(root);
    }
    return root;
}

mbek* pushNode(mbek* root,char id[10],char name[100],char color[100],int weight,int age)
{
    if(!root)
    {
        return genNode(id,name,color,weight,age);
    }
    if(strcmp(name,root->name) < 0)
    {
        root->left = pushNode(root->left,id,name,color,weight,age);
    }
    else if(strcmp(name,root->name) > 0)
    {
        root->right = pushNode(root->right,id,name,color,weight,age);
    }

    heightUpdate(root);

    return rebalance(root);

}

mbek* search(mbek* root,char id[10])
{
    if(!root)
    {
        return NULL;
    }
    if(strcmp(id,root->id) < 0)
    {
        return search(root->left,id);
    }
    else if(strcmp(id,root->id) > 0)
    {
        return search(root->right,id);
    }
    else
    {
        return root;
    }
}
bool validId(mbek* root,char id[10])
{
    if(strlen(id) < 5 || strlen(id) > 5)
    {
        return false;
    }
    if(search(root,id))
    {
        return false;
    }
    return true;
}
void printMenu()
{
    printf("\nMbek Farm\n");
    printf("\n");
    printf("1.Insert New Goat\n");
    printf("2.Remove a Goat\n");
    printf("3.See All Goat\n");
    printf("4.Remove All Goat\n");
    printf("5.Exit\n");
    printf(">>");
}
mbek* insertMbek(mbek* root)
{
    char id[10];
    char name[100];
    char color[100];
    int weight;
    int age;
    char confirm;

    do
    {
        printf("Insert goat's id [5 digits number] : ");
        scanf("%[^\n]",id);
        getchar();
    } while (!validId(root,id));

    do
    {
        printf("Insert goat's name[2 chars or more]: ");
        scanf("%[^\n]",name);
        getchar();
        
    } while (strlen(name) < 2);

    do
    {
        printf("Insert goat's color[WHITE|BLACK|BROWN]: ");
        scanf("%[^\n]",color);
        getchar();
    } while (strcmpi(color,"brown")!=0 && strcmpi(color,"black")!=0 && strcmpi(color,"white")!=0);

    do
    {
        printf("Insert goat's weight in KG[2-150]: ");
        scanf("%d",&weight);
        getchar();
    } while (weight<2 || weight>150);
    do
    {
        printf("Insert goat's age in month(s)[2-150]: ");
        scanf("%d",&age);
        getchar();
    } while (age<0 || age>150);

    do
    {
        printf("ARE YOU SURE YOU WANT TO ADD %s GOAT? [Y|N]: ",name);
        scanf("%c",&confirm);
        getchar();
    } while (confirm != 'Y' && confirm != 'N');
    
    if(confirm =='Y')
    {
        root = pushNode(root,id,name,color,weight,age);
        printf("SUCESS ADD !\n");
        printf("Press enter to continue...");
        getchar();
    }
    else if(confirm =='N')
    {
        system("cls");
        printMenu();
    }
    
    return root;
    
}

void inOrder(mbek*root)
{
    if(!root)
    {
        return;
    }
    inOrder(root->left);
    printf("\n%s %5s   %-5s    %-5d     %d\n",root->id,root->name,root->color,root->weight,root->age);
    inOrder(root->right);
}

void preOrder(mbek*root)
{
    if(!root)
    {
        return;
    }
    printf("\n%s %5s   %-5s    %-5d     %d\n",root->id,root->name,root->color,root->weight,root->age);
    preOrder(root->left);
    preOrder(root->right);
}

void postOrder(mbek*root)
{
    if(!root)
    {
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    printf("\n%s %5s   %-5s    %-5d     %d\n",root->id,root->name,root->color,root->weight,root->age);
}

void viewMbek(mbek* root)
{
    if(!root)
    {
        printf("YOU DON'T HAVE ANY GOATS!\n");
    }
    int select = 0;

    do
    {
        printf("How do you want to see your goats?\n");
        printf("1.In Order\n");
        printf("2.Pre Order\n");
        printf("3.Post Order\n");
        scanf("%d",&select);
        getchar();
        system("cls");

        if(select==1)
        {
            printf("In Order\n");
            printf("ID    Name     Color    Weight    Age");
            inOrder(root);
        }
        else if(select==2)
        {
            printf("Pre Order\n");
            printf("ID    Name     Color    Weight    Age");
            preOrder(root);
        }
        else if(select==3)
        {
            printf("Post Order\n");
            printf("ID    Name     Color    Weight    Age");
            postOrder(root);
        }
    } while (select < 1 || select > 3);
    printf("\n");
    printf("Press enter when you are done...");
    getchar();
    system("cls");
}
void viewMbek2(mbek* root)
{
    if(!root)
    {
        printf("YOU DON'T HAVE ANY GOATS!\n");
    }
    int select = 0;

    do
    {
        printf("How do you want to see your goats?\n");
        printf("1.In Order\n");
        printf("2.Pre Order\n");
        printf("3.Post Order\n");
        scanf("%d",&select);
        getchar();
        system("cls");

        if(select==1)
        {
            inOrder(root);
        }
        else if(select==2)
        {

            preOrder(root);
        }
        else if(select==3)
        {
            postOrder(root);
        }
    } while (select < 1 || select > 3);

}


mbek* predecessor(mbek* root)
{
    root = root ->left;
    while (root->right)
    {
        root = root->right;
    }
    return root;
}

mbek* popGoat(mbek* root,char id[10])
{
    if(!root)
    {
        return NULL;
    }
    if(strcmp(id,root->id) < 0)
    {
        root->left = popGoat(root->left,id);
    }
    else if(strcmp(id,root->id) > 0)
    {
        root->right = popGoat(root->right,id);
    }
    else
    {
        if(!root->left && !root->right)
        {
            root=NULL;
            free(root);
            return NULL;
        }
        else if(!root->left)
        {
            mbek* child = root->right;
            root = NULL;
            return child;
        }
        else if(!root->right)
        {
            mbek* child = root->left;
            root = NULL;
            free(root);
            return child;
        }
        else
        {
            mbek* prede = predecessor(root);
            strcpy(root->id,prede->id);
            strcpy(root->name,prede->name);
            strcpy(root->color,prede->color);
            root->weight = prede->weight;
            root->age = prede->age;

            return popGoat(root->left,prede->name);
        }
    }
    return NULL;
}

mbek* removeMbek(mbek* root)
{
    if(!root)
    {
        printf("You don't have any goats\n");
        return NULL;
    }

    char id[10];
    mbek* find = NULL;

    viewMbek2(root);
    printf("\n");

    do
    {
        printf("Enter Goat ID to be removed! >");
        scanf("%[^\n]",id);
        getchar();
        find=search(root,id);
    } while (!find);

    printf("Success remove goat!\n");
    printf("Press enter to continue...");
    getchar();

    return popGoat(root,id);
    
}

mbek* removeAllMbek(mbek*root)
{
    if(!root)
    {
        printf("You don't have any mbek !");
        return NULL;
    }
    while(root)
    {
        root = popGoat(root,root->id);
    }
    return root;
}


int main()
{
    mbek* root=NULL;
    int menu = 0;

    do
    {
        printMenu();
        scanf("%d",&menu);
        getchar();
        if(menu == 1)
        {
            system("cls");
            root = insertMbek(root);
            system("cls");
        }
        else if(menu == 2)
        {
            system("cls");
            root = removeMbek(root);
            system("cls");
        }
        else if(menu == 3)
        {
            system("cls");
            viewMbek(root);
            printf("\n");
        }
        else if(menu == 4)
        {
            system("cls");
            root = removeAllMbek(root);

        }
    } while (menu!=5);
    
    return 0;
}