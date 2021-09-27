#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct Voters{
    char name[100];
    long int Roll;
    int count;
    struct Voters *next;
};
struct Candidates{
    char name[100];
    char symbol[10];
    int count;
    struct Candidates *next;
};
//Load Candidates To Programme
typedef struct Candidates candi;
candi* headc=NULL,*lastc,*tempc,*temp1c,*temp2c,*temp3c;
int count1=0;
char str[100];
void LoadCandidates(){
    FILE *fp;
    fp=fopen("Candidates.txt","r");
    while(fgets(str,19,fp)!=NULL){
        if(count1%2==0){ 
            tempc=(candi *)malloc(sizeof(candi));
            strcpy(tempc->name,str);
            tempc->next=NULL;
            if(headc==NULL){
                headc=tempc;
                lastc=tempc;
            }
            else{
                lastc->next=tempc;
                lastc=tempc;
                tempc->count=0;
            }
        }
        else{
            char x[10];
            sscanf(str,"%s",x);
            strcpy(tempc->symbol,x);
        }
        count1++;
    }
    fclose(fp);
    return;
}
//For Display Current Candidates
void displayCandidates(){
    tempc=headc;
    printf("\n\n");
    while(tempc!=NULL){
        printf("\t\t\t\t\t\t\t\t\t\t\tCandidate: %s\t\t\t\t\t\t\t\t\t\t\tSymbol: %s\n",tempc->name,tempc->symbol);
        printf("\n\n");
        tempc=tempc->next;
    }
    return;
}
//Loading Voters List into thr Programme
typedef struct Voters vot;
vot* head2=NULL,*temp3,*temp4,*last2;
int countV=0;
void LoadVotersList(){
    FILE *fp;
    int count=0;
    fp=fopen("Voters.txt","r");
    while(fgets(str,50,fp)!=NULL){
        fflush(stdin);
        if(countV%2==0){ 
            temp3=(vot *)malloc(sizeof(vot));
            strcpy(temp3->name,str);
            temp3->next=NULL;
            if(head2==NULL){
                head2=temp3;
                last2=temp3;
            }
            else{
                last2->next=temp3;
                last2=temp3;
            }
        }
        else{
            long int x;
            sscanf(str,"%ld",&x);
            temp3->Roll=x;
            temp3->count=0;
        }
        countV++;
    }
    fclose(fp);
    return;
}
void displayVoter(){
    temp3=head2;
    printf("\n\n");
    while(temp3!=NULL){
        printf("\t\t\t\t\t\t\t\t\t\t\tVoters Name: %s\t\t\t\t\t\t\t\t\t\t\tROll Number: %ld   \n\t\t\t\t\t\t\t\t\t\t\tVoting Count:%d\n",temp3->name,temp3->Roll,temp3->count);
        printf("\n\n");
        temp3=temp3->next;
    }
    return;
}
int countVoter=0;
void Voting(){
    printf("\n\t\tKindly First Enter Your Number(Roll Number):");
    long int x,y;
    char sym[10];
    scanf("%ld",&x);
    temp3=head2;
    while(temp3!=NULL){
        if(temp3->Roll==x){
            if(temp3->count==0){
                printf("\n\n\t\tWhich One Of Them Do you want To Vote:");
                displayCandidates();
                printf("\n\n\t\tPlease Enter Your Choice(Symbol):");
                fflush(stdin);
                scanf("%s",sym);
                tempc=headc;
                int countc=0;
                while(tempc!=NULL){
                    int l=strcmp(tempc->symbol,sym);
                    if(l==0){
                        printf("\n\n\t\tYour Vote Has Been Counted To coreesponding to Candidate Name:%s",tempc->name);
                        tempc->count++;
                        countc++;
                        countVoter++;
                        temp3->count++;
                    }
                    tempc=tempc->next;
                }
                if(countc==0){
                    printf("\n\n\t\t\tYou Have Enter Wrong Symbol:");
                    return;
                }
            }
            else{
                printf("\n\n\t\tYou HAve Voted Earlier Now You Are BlackListed.");
                temp3->count++;
            }
        }
        temp3=temp3->next;
    }
}
//Sorting On the Basis Of count
void Sorting(){
    int i,j;
    tempc=headc;
    int count=count1/2;
    for ( i = 0; i < count; i++)
    {
        count1=0;
        tempc=headc;
        temp1c=tempc->next;
        for (j = 0; j < count-i-1; j++)
        {
            if ((tempc->count)>(temp1c->count))
            {
                if (count1==0)
                {
                    tempc->next=temp1c->next;
                    temp1c->next=tempc;
                    headc=temp1c;
                    tempc=headc;
                    temp1c=tempc->next;
                }
                else
                {
                    temp2c=headc;
                    while ((temp2c->next)!=tempc)
                    {
                        temp2c=temp2c->next;
                    }
                    temp2c->next=temp2c->next->next;
                    tempc->next=temp1c->next;
                    temp1c->next=tempc; 
                    temp2c=temp1c;
                    temp3c=tempc;
                    temp1c=temp3c;
                    tempc=temp2c;          
                }  
            }
            count1++;
            tempc=tempc->next;
            temp1c=temp1c->next;   
        }  
    }
}
//Now Winner
void Winner(){
    tempc=headc;
    while(tempc->next!=NULL){
        printf("Candidate Name:%s Candidate Total Votes:%d\n\n\n\n\n\n\n\n\n\n",tempc->name,tempc->count);
        tempc=tempc->next;
    }
    printf("\t\t\t\t\t\t\t\t\t\t\tWinner Winner Chicken Dinner\n\n");
    printf("Candidate Name:%s  Total Vote Count: %d",tempc->name,tempc->count);
    printf("\n\n\n\n\n\n\n\n\n\n");
    return;
}
//vot* head2=NULL,*temp3,*temp4,*last2;
void FraudVoters(){
    printf("Printing Fraud Voters Name:\n\n\n\n\n\n");
    temp3=head2;
    while(temp3!=NULL){
        if(temp3->count>1){
            printf("\t\t\t\tVoter's Name:%s\n\t\t\t\tVoter's Roll Number:%ld\n\t\t\t\tNumber Of Votes Given By him:%d",temp3->name,temp3->Roll,temp3->count);
            printf("\n\n");
        }
        temp3=temp3->next;
    }
}
//NonVoting Voters
void NonVotingVoters(){
    printf("Printing Voter's Name Who not give any vote:\n\n\n\n\n\n");
    temp3=head2;
    while(temp3!=NULL){
        if((temp3->count)==0){
            printf("\t\t\t\tVoter's Name:%s\n\t\t\t\tVoter's Roll Number:%ld\n\t\t\t\tNumber Of Votes Given By him:%d",temp3->name,temp3->Roll,temp3->count);
            printf("\n\n");
        }
        temp3=temp3->next;
    }
}
//Genuine Voters
void GenunineVoters(){
    printf("Printing Voter's Name Who Are Genuine:\n\n\n\n\n\n");
    temp3=head2;
    while(temp3!=NULL){
        if((temp3->count)==1){
            printf("\t\t\t\tVoter's Name:%s\n\t\t\t\tVoter's Roll Number:%ld\n\t\t\t\tNumber Of Votes Given By him:%d",temp3->name,temp3->Roll,temp3->count);
            printf("\n\n");
        }
        temp3=temp3->next;
    }
}
//Total voters List count
void VotersFinal(){
    FILE *fo;
    fo=fopen("VotersFinal.txt","w");
    temp3=head2;
    while ( temp3!=NULL )
    {
        fprintf ( fo, "%s \n", temp3->name) ;
        fprintf(fo,"%ld \n",temp3->Roll);
        fprintf(fo,"%d \n\n",temp3->count);
        fflush (stdin);
        temp3=temp3->next;
    } 
    fclose(fo);
    return ;
}
//Non Voting Candidates in to the file name NonVotingCandidates
void NonVotingCandidates(){
    FILE *fo;
    fo=fopen("NonVotingCandidates.txt","w");
    temp3=head2;
    while ( temp3!=NULL )
    {
        if(temp3->count==0){
            fprintf ( fo, "%s \n", temp3->name) ;
            fprintf(fo,"%ld \n",temp3->Roll);
            fprintf(fo,"%d \n\n",temp3->count);
            fflush ( stdin ) ;
        }
        temp3=temp3->next;
    } 
    fclose(fo);
    return ;
}
//MAin Function
int main(){
    LoadCandidates();
    printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\tNow Printing Candidates Name:");
    displayCandidates();    //For Displaying Candidates
    LoadVotersList();
    fflush(stdin);
    printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\tNow Printing Voters Name:");
    displayVoter();
    fflush(stdin);
    printf("\n\n\t\t\t\t\t\t\t\t\t\t\tNow Voting is Going To STart:\n\n");
    int choice;
    do{
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
        Voting();
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("\n\n\t\tEnter 0(Zero)To STop Votting else Press ANy Integer:");
        scanf("%d",&choice);
    }while(choice);
    Sorting();
    countV=countV/2;
    float z=(float)countVoter/countV;
    z=z*100;
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\tVoting Percentage is: %f\n\n\n\n\n\n\n\n\n\n\n\n\n",z);
    Winner();
    printf("\n\n\n\n\n\n");
    NonVotingVoters();
    printf("\n\n\n\n\n\n");
    GenunineVoters();
    FraudVoters();
    VotersFinal();
    NonVotingCandidates();
    printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t***********END***********\n\n");
    return 0;
}
