//
//  UCupiD.c
//  
//
//  Created by github.com/foolsparadise on 2018/6/1.
//

#include "UCupiD.h"
#include "string.h"
#include "stdlib.h"

#include <stdio.h>

typedef struct _UCupiD_Node {
	struct _UCupiD_Node *next;
    struct _UCupiD_Node *prev;
	char SID[64];
	char Firstname[64];
    char Sex[64];
    char Orientation[64];
    char Age[64];
    char PoliticalLeaning[64];
    char MajorHobby[64];
    char MinorHobby[64];
    char Height[64];
    char Weight[64];
}UCupiD_Node;

typedef struct {
    UCupiD_Node node;
    int count;
}UCupiD_List;

void UCupiD_List_Init(UCupiD_List* pList);
int UCupiD_List_Count(UCupiD_List* pList);
void UCupiD_List_Push(UCupiD_List* pList, UCupiD_Node* pNode);
UCupiD_Node* UCupiD_List_Pop(UCupiD_List* pList);
UCupiD_Node* UCupiD_List_Popry(UCupiD_List* pList);
void UCupiD_List_Destroy();

static UCupiD_List _UCupiDList;
static UCupiD_List _UCupiDList4Find;

void UCupiD_List_Init(UCupiD_List* pList)
{
    memset(pList, 0, sizeof(UCupiD_List));
}
int UCupiD_List_Count(UCupiD_List* pList)
{
    return pList->count;
}
void UCupiD_List_Push(UCupiD_List* pList, UCupiD_Node* pNode)
{
    UCupiD_Node *pNext;
    UCupiD_Node *pPrev = pList->node.prev;    
    if (pPrev == NULL)
    {
        pNext = pList->node.next;
        pList->node.next = pNode;
    }
    else
    {
        pNext = pPrev->next;
        pPrev->next = pNode;
    }    
    if (pNext == NULL)
        pList->node.prev = pNode;
    else
        pNext->prev = pNode;
    pNode->next = pNext;
    pNode->prev = pPrev;    
    pList->count++;
}
UCupiD_Node* UCupiD_List_Pop(UCupiD_List* pList)
{
    UCupiD_Node* pNode = pList->node.next;   
    if (pNode->prev == NULL)
        pList->node.next = pNode->next;
    else
        pNode->prev->next = pNode->next;
    if (pNode->next == NULL)
        pList->node.prev = pNode->prev;
    else
        pNode->next->prev = pNode->prev;
    pList->count--;
    
    return pNode;
}
UCupiD_Node* UCupiD_List_Pop_try(UCupiD_List* pList)
{
    return pList->node.next;
}
void UCupiD_List_Destroy() {
    //
    int count = UCupiD_List_Count(&_UCupiDList);
    int i=0;
    for (i = 0; i < count; i++)
    {
        UCupiD_Node* pNode  = (UCupiD_Node*)malloc(sizeof(UCupiD_Node));
        pNode = UCupiD_List_Pop(&_UCupiDList);
        memset(pNode, 0, sizeof(UCupiD_Node));
        free(pNode);
    }
    //
    count = UCupiD_List_Count(&_UCupiDList4Find);
    i=0;
    for (i = 0; i < count; i++)
    {
        UCupiD_Node* pNode  = (UCupiD_Node*)malloc(sizeof(UCupiD_Node));
        pNode = UCupiD_List_Pop(&_UCupiDList4Find);
        memset(pNode, 0, sizeof(UCupiD_Node));
        free(pNode);
    }
}
int getFindingCount() {
    return UCupiD_List_Count(&_UCupiDList);
} 
int getFindingCount4Find() {
    return UCupiD_List_Count(&_UCupiDList4Find);
} 
int UCupiD_ReadsEachEntryFromDatabaseFile(const char* path) {
    UCupiD_List_Init(&_UCupiDList);
    FILE* filein = fopen(path,"r");
    if(!filein) {
        //printf("Error: cannot open %s\n", path);
        return 1;
    }    
    char get1ineTxt[1024]; 
    while(fgets(get1ineTxt, 1024, filein)) {
        //printf("__LINE__%d: %s", __LINE__, get1ineTxt);
        UCupiD_Node* pNode = (UCupiD_Node*)malloc(sizeof(UCupiD_Node));
        memset(pNode, 0, sizeof(UCupiD_Node));     
        char *entry = get1ineTxt;
        char get1Value[64]; memset(get1Value, 0, 64);
        int count=0;
        for(count=0; count<10; count++) {
            sscanf(entry, "%[^,]", get1Value);
                 if(count==0) strncpy(pNode->SID, get1Value,strlen(get1Value));
            else if(count==1) strncpy(pNode->Firstname, get1Value,strlen(get1Value));
            else if(count==2) strncpy(pNode->Sex, get1Value,strlen(get1Value));
            else if(count==3) strncpy(pNode->Orientation, get1Value,strlen(get1Value));
            else if(count==4) strncpy(pNode->Age, get1Value,strlen(get1Value));
            else if(count==5) strncpy(pNode->PoliticalLeaning, get1Value,strlen(get1Value));
            else if(count==6) strncpy(pNode->MajorHobby, get1Value,strlen(get1Value));
            else if(count==7) strncpy(pNode->MinorHobby, get1Value,strlen(get1Value));
            else if(count==8) strncpy(pNode->Height, get1Value,strlen(get1Value));
            else if(count==9) {
                //最后一个需要对回车换行符的处理
                char*p=strtok(get1Value,"\n");
                p=strtok(p,"\r");
                strncpy(pNode->Weight, p,strlen(p));
            }
            entry = entry +strlen(get1Value) +1;
        }
        UCupiD_List_Push(&_UCupiDList, pNode);
        //printf("__LINE__%d: %d %s %s %s\n", __LINE__, _UCupiDList.count, pNode->SID, pNode->Firstname, pNode->Sex);
        //free(pNode);
    }
    int count = getFindingCount();
    if (0 == count) return 1;

    return 0;
}
int UCupiD_FindsAnIndividualInLinkedList(const char* sid) {
    UCupiD_List_Init(&_UCupiDList4Find);
    int count=0;
    int listcount = getFindingCount();
    if (0 == listcount) return 1;
    //printf("__LINE__%d: %d\n", __LINE__, listcount);
    UCupiD_Node* sidNode = (UCupiD_Node*)malloc(sizeof(UCupiD_Node));
    memset(sidNode, 0, sizeof(UCupiD_Node));
    UCupiD_Node* sidNode4Find = _UCupiDList.node.next;
    for(count=0; count<listcount; count++) {
        //printf("__LINE__%d: %s %s %s\n", __LINE__, sidNode4Find->SID, sidNode4Find->Firstname, sidNode4Find->Sex);
        if(!strncmp(sidNode4Find->SID, sid, strlen(sid))) {
            sidNode = sidNode4Find;
        }
        sidNode4Find = sidNode4Find->next;
    }
    if(strlen(sidNode->SID)<1) return 1;
    //printf("__LINE__%d: %s %s %s %s %s %s %s %s\n", __LINE__, sidNode->SID, sidNode->Firstname, sidNode->Sex, sidNode->Orientation, sidNode->MajorHobby, sidNode->MinorHobby, sidNode->Height, sidNode->Weight);

    char matchtxt[48]; memset(matchtxt, 0, 48);
    sprintf(matchtxt, "match_%s.txt", sid);
    FILE* fileout = fopen(matchtxt,"w");
    UCupiD_Node* sidNode4Fin2 = _UCupiDList.node.next;
    int i=0;
    for(count=0; count<listcount; count++) {
        //printf("__LINE__%d: %s %s %s %s %s %s\n", __LINE__, sidNode->Firstname, sidNode->Sex, sidNode->Orientation, sidNode4Fin2->Firstname, sidNode4Fin2->Sex, sidNode4Fin2->Orientation);        
        if( strncmp(sidNode->SID,sidNode4Fin2->SID,strlen(sidNode->SID)) &&
            (!strncmp(sidNode->Sex,sidNode4Fin2->Orientation,strlen(sidNode->Sex)) && 
            !strncmp(sidNode->Orientation,sidNode4Fin2->Sex,strlen(sidNode->Orientation)) && 
            !strncmp(sidNode->Orientation,sidNode->Orientation,strlen(sidNode->Orientation)))
          ) {
            if(i==0) {               
                char text[128]; memset(text, 0, 128);
                sprintf(text, "Matches for user %s (%s):\n", sidNode->SID, sidNode->Firstname);
                fputs(text, fileout);
                i++;
            }
            // 如果两个人(不同的两个人，不能是自已匹配自已)，他们性取向是匹配的比如（例如，一个女性寻找男性将与男性寻找女性匹配，或男性寻找男性将兼容另一个男性寻找男性等），并且满足下面3个中的一个，就算匹配
            // 1.年龄10岁之内 用小于等于吧..我也不确定...     政治倾向2分之内
            // 2.两个人拥有共同的主要兴趣和次要兴趣爱好
            // 3.两个人身高体重 10%之内
            if( abs(atoi(sidNode->Age)-atoi(sidNode4Fin2->Age))<10 ) 
            {
                printf("__LINE__%d: %s %s %s %s\n", __LINE__, sidNode->Firstname, sidNode->Age, sidNode4Fin2->Firstname, sidNode4Fin2->Age);
                fprintf(fileout, "- %s (%s)\n", sidNode4Fin2->SID, sidNode4Fin2->Firstname);            
                sidNode4Fin2 = sidNode4Fin2->next;
                continue;
            }   
            if(!strncmp(sidNode->MajorHobby, sidNode4Fin2->MajorHobby, strlen(sidNode->MajorHobby)) &&
                 !strncmp(sidNode->MinorHobby, sidNode4Fin2->MinorHobby, strlen(sidNode->MinorHobby))
                 ) 
            {
                printf("__LINE__%d: %s %s %s %s %s %s\n", __LINE__, sidNode->Firstname, sidNode->MajorHobby, sidNode->MinorHobby, sidNode4Fin2->Firstname, sidNode4Fin2->MajorHobby, sidNode4Fin2->MinorHobby);
                fprintf(fileout, "- %s (%s)\n", sidNode4Fin2->SID, sidNode4Fin2->Firstname);            
                sidNode4Fin2 = sidNode4Fin2->next;
                continue;   
            } 
            int sidHeight =         atoi(sidNode->Height);
            int sidWeight =         atoi(sidNode->Weight);
            int sid4FindHeight =    atoi(sidNode4Fin2->Height);
            int sid4FindWeight =    atoi(sidNode4Fin2->Weight);
            if( (float)sidHeight/sid4FindHeight>0.9 && 
                (float)sidHeight/sid4FindHeight<1.1 &&
                (float)sidWeight/sid4FindWeight>0.9 &&
                (float)sidWeight/sid4FindWeight<1.1 
            )                    
            {
                printf("__LINE__%d: %s (%s) (%d) (%s) (%d) %s (%s) (%d) (%s) (%d)\n", __LINE__, sidNode->Firstname, sidNode->Height, sidHeight, sidNode->Weight, sidWeight, sidNode4Fin2->Firstname, sidNode4Fin2->Height, sid4FindHeight, sidNode4Fin2->Weight, sid4FindWeight);
                fprintf(fileout, "- %s (%s)\n", sidNode4Fin2->SID, sidNode4Fin2->Firstname);            
                sidNode4Fin2 = sidNode4Fin2->next;
                continue;
            }               
            
        }
        sidNode4Fin2 = sidNode4Fin2->next;
    }


/*  // 一次性的出入栈方式遍历，代码弃用
    printf("__LINE__%d: %d\n", __LINE__, listcount);
    for(count=0; count<listcount; count++) {
        UCupiD_Node* pNode = (UCupiD_Node*)malloc(sizeof(UCupiD_Node));
        memset(pNode, 0, sizeof(UCupiD_Node));
        pNode = UCupiD_List_Pop(&_UCupiDList);
        printf("__LINE__%d: %s %s %s\n", __LINE__, pNode->SID, pNode->Firstname, pNode->Sex);
        if(!strncmp(pNode->SID, sid, strlen(sid))) {
            UCupiD_List_Push(&_UCupiDList4Find, pNode);
        }        
        //free(pNode);
    }
    //printf("__LINE__%d: %d\n", __LINE__, listcount);
    listcount = getFindingCount4Find();
    if(listcount==0) return 1;
    //printf("__LINE__%d: %d\n", __LINE__, listcount);
    char matchtxt[48]; memset(matchtxt, 0, 48);
    sprintf(matchtxt, "match_%s.txt", sid);
    FILE* fileout = fopen(matchtxt,"w");
    for(count=0; count<listcount; count++) {        
        UCupiD_Node* pNode = (UCupiD_Node*)malloc(sizeof(UCupiD_Node));
        memset(pNode, 0, sizeof(UCupiD_Node));
        pNode = UCupiD_List_Pop(&_UCupiDList4Find);
        //printf("__LINE__%d: %s %s %s\n", __LINE__, pNode->SID, pNode->Firstname, pNode->Sex);        
        if(count==0) {               
            char text[128]; memset(text, 0, 128);
            sprintf(text, "Matches for user %s (%s):\n", pNode->SID, pNode->Firstname);
            fputs(text, fileout);
        }
        fprintf(fileout, "- %s (%s)\n", pNode->SID, pNode->Firstname);        
        //free(pNode);
    }
*/
    //if(sidNode) free(sidNode);
    if(fileout) fclose(fileout);

    return 0;
}


int main(int argc, char ** argv) {
    /*
    printf("__LINE__(%d): UCupiD %d\n", __LINE__, argc);
    int i;
    for (i=0; i < argc; i++)
        printf("__LINE__(%d): Argument %d is %s.\n", __LINE__, i, argv[i]);
    */
   
    if(argc!=3) {
        printf("Usage: ./UCupiD db_file SID\n");
        return 1;
    }    
    if(1 == UCupiD_ReadsEachEntryFromDatabaseFile(argv[1])) {
        printf("Error: cannot open %s\n", argv[1]);
        return 1;
    }
    if(1 == UCupiD_FindsAnIndividualInLinkedList(argv[2])) {
        printf("User with SID %s not found\n", argv[2]);
        return 0;
    }    
    UCupiD_List_Destroy();

    /* 一坨代码只完成检索功能，代码弃用
    FILE* filein = fopen(argv[1],"r");
    if(!filein) {
        printf("Error: cannot open %s\n", argv[1]);
        return 1;
    }

    char matchtxt[48]; memset(matchtxt, 0, 48);
    sprintf(matchtxt, "match_%s.txt", argv[2]);
    FILE* fileout = fopen(matchtxt,"w");
    if(fileout) {
        fseek(fileout,0,SEEK_SET);
    }

    char get1ineTxt[1024]; 
    int count=0;
    while(fgets(get1ineTxt, 1024, filein)) {
        //printf("__LINE__(%d): %s\n", __LINE__, get1ineTxt);
        char *entry = get1ineTxt;
        char sid[20];
        sscanf(entry, "%[^,]", sid);
        //printf("__LINE__(%d): (%s) %s\n", __LINE__, entry, sid);
        if(!strncmp(argv[2], sid, strlen(argv[2]))) {
            entry = entry +strlen(argv[2]) +1;
            char name[128]; memset(name, 0, 128);
            sscanf(entry, "%[^,]", name);
            count++;
            char text[128]; memset(text, 0, 128);
            if(ftell(fileout)<1) {               
                memset(text, 0, 128);
                sprintf(text, "Matches for user %s (%s):\n", sid, name);
                //printf("__LINE__(%d): %s\n", __LINE__, text);
                fputs(text, fileout);
            }
            memset(text, 0, 128);
            sprintf(text, "- %s (%s)\n", sid, name);
            //printf("__LINE__(%d): %s\n", __LINE__, text);
            fputs(text, fileout);
        }
    }
    if(count==0)
        printf("User with SID %s not found\n", argv[2]);

    if(filein) fclose(filein);
    if(fileout) fclose(fileout);
    */

    return 0;
}
