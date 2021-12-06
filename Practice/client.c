#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define MAXSIZE 50
struct Student{
    char name[50];
    char mobile[10];
    char anum[50];
    char op[30];
};
struct Newval{
    char mobile[10];
    char anum[50];
};

main()
{
int sockfd,retval;
int recedbytes,sentbytes;
struct sockaddr_in serveraddr;
char buff[MAXSIZE];
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd==-1)
{
printf("\nSocket Creation Error");

}
printf("%i",sockfd);
serveraddr.sin_family=AF_INET;
serveraddr.sin_port=htons(3388);
serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
retval=connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
if(retval==-1)
{
printf("Connection error");

}
struct Student st[3];
struct Newval nv[1];

    printf("Enter from following options:\n1.Display\n2.Serach&Replace\n3.Display socket address\n4.Exit\n");
    int n,i;
    char ch;
    scanf("%c",&ch);
    
    switch(ch){
        case '1':
            {
            buff[0] = '1';
            sentbytes=send(sockfd,buff,sizeof(buff),0);
            if(sentbytes==-1)
            {
            printf("!!");
            close(sockfd);
            }
            recedbytes=recv(sockfd,(struct Student *) &st,sizeof(st),0);
            
            n = sizeof(st);

            for(i=0;i<3;i++){
                printf("%s\n", st[i].name);
                printf("%s\n",st[i].mobile);
                printf("%s\n",st[i].anum);
            }

            close(sockfd);
            break;
            }
        case '2':
            {
                buff[0]='2';
                sentbytes=send(sockfd,buff,sizeof(buff),0);
                printf("Enter mobile number: ");
                scanf("%s",nv[0].mobile);
                //strcpy(nv[0].mobile,"12345678");
                printf("Enter alphanumeric value: ");
                scanf("%s",nv[0].anum);
                if(sentbytes==-1)
                {
                printf("!!");
                close(sockfd);
                }
                sentbytes=send(sockfd,(struct Newval *)&nv,sizeof(nv),0);
                if(sentbytes==-1)
                {
                printf("!!");
                close(sockfd);
                }

                recedbytes=recv(sockfd,(struct Student *) &st,sizeof(st),0);
                printf("%s\n",st[0].op);
                for(i=0;i<3;i++){
                    printf("%s\n", st[i].name);
                    printf("%s\n",st[i].mobile);
                    printf("%s\n",st[i].anum);
                }

                close(sockfd);

                break;
            }
        default:
            break;
    }
    
    




}
