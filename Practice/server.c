#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 90
struct Student{
    char name[50];
    char mobile[10];
    char anum[50];
    char op[30];
};

struct Newval
{
    char num[10];
    char anum1[50];
};


main()
{
int sockfd,newsockfd,retval;
socklen_t actuallen;
int recedbytes,sentbytes;
struct sockaddr_in serveraddr,clientaddr;

char buff[MAXSIZE];
int a=0;
sockfd=socket(AF_INET,SOCK_STREAM,0);

if(sockfd==-1)
{
printf("\nSocket creation error");
}

serveraddr.sin_family=AF_INET;
serveraddr.sin_port=htons(3388);
serveraddr.sin_addr.s_addr=htons(INADDR_ANY);
retval=bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
if(retval==1)
{
printf("Binding error");
close(sockfd);
}

retval=listen(sockfd,1);
if(retval==-1)
{
close(sockfd);
}

actuallen=sizeof(clientaddr);
newsockfd=accept(sockfd,(struct sockaddr*)&clientaddr,&actuallen);


if(newsockfd==-1)
{
close(sockfd);
}
printf("Connected...\n");
struct Student st[3];
strcpy(st[0].name,"Sam");
strcpy(st[0].mobile,"12345678");
strcpy(st[0].anum,"abc123");
strcpy(st[1].name,"Sam");
strcpy(st[1].mobile,"12345678");
strcpy(st[1].anum,"abc123");
strcpy(st[2].name,"Sam");
strcpy(st[2].mobile,"12345678");
strcpy(st[2].anum,"abc123");

printf("Struct filled\n");
struct Newval nv[1];

    recedbytes=recv(newsockfd,buff,sizeof(buff),0);

    if(recedbytes==-1)
    {
    close(sockfd);
    close(newsockfd);
    }
    char ch = buff[0];
   

    char temp[20];
    char temp2[20];
    int j,flag;
    int k;
    int len_anum;
    char temp3;
    printf("Buff Received\n");
    switch(ch){
        case '1':
            printf("Option 1 selected\n");
            for(int i=0;i<3;i++){
                len_anum = strlen(st[i].anum);
                strcpy(temp,st[i].anum);
                for(j=0;j<len_anum-1;j++){
                    for(k=j+1;k<len_anum;k++){
                        if(temp[j]<temp[k]){
                            temp3 = temp[j];
                            temp[j] = temp[k];
                            temp[k] = temp3;
                        }
                    }
                }
                strcpy(st[i].anum,temp);
                
            }
            sentbytes=send(newsockfd,(struct Student *)&st,sizeof(st),0);
            if(sentbytes==-1)
            {
            close(sockfd);
            close(newsockfd);
            }
            break;
        case '2':
            printf("Option 2 selected..\n");
            recedbytes=recv(newsockfd,(struct Newval *)&nv,sizeof(nv),0);
            if(recedbytes==-1)
            {
            close(sockfd);
            close(newsockfd);
            }
            flag = 0;
            printf("%s\n",nv[0].num);
            for(int i=0;i<3;i++){
                printf("%s   %s\n", nv[0].num,st[i].mobile);
                if(strcmp(nv[0].num,st[i].mobile)==0){
                    printf("%d\n",strcmp(nv[0].num,st[i].mobile));
                    flag = 1;
                    strcpy(st[i].anum,nv[0].anum1);
                }
            }
            if(flag)
                strcpy(st[0].op,"Anum value updated\n");
            else    
                strcpy(st[0].op,"Number not found\n");
            sentbytes=send(newsockfd,(struct Student *)&st,sizeof(st),0);
            if(sentbytes==-1)
            {
            close(sockfd);
            close(newsockfd);
            }

            break;
    
        default:
            break;

    } 


close(sockfd);
close(newsockfd);
}

