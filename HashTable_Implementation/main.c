#define SIZE_OF_ht 10
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LOAD_FACTOR 0.75 
#include <limits.h>
#include "HashTable.h"
int main()
{   
    HashTable ht;
    char value[30];
    char key[30];
    init_HashTable(&ht,5);
    insert_HashTable(&ht,"101","USA");
    insert_HashTable(&ht,"89","INDIA");
    insert_HashTable(&ht,"102","TAIWAN");
    insert_HashTable(&ht,"702","CHINA");
    insert_HashTable(&ht,"103","UK");
    int num;
    int x;
    while(1)
    {
        
        printf("1.Insert value in Hashtable\n");
        printf("2.Delete value from HashTable\n");
        printf("3.Print HashTable\n");
        printf("4.Get value by key from Hashtable\n");
        printf("5.Print details of Hashtable\n");
        
        
        scanf("%d",&num);
        switch(num)
        {
            case 1:
            printf("Enter key:");
            scanf("%s",key);
            printf("\n");
            printf("Enter Value:");
            scanf("%s",value);
            printf("\n");
            insert_HashTable(&ht,key,value);
            break;
            
            
            case 2:
            printf("Enter key:");
            scanf("%s",key);
            printf("\n");
            Remove_HashTable(&ht,key);
            break;
            
            case 3:
            print_HashTable(ht);
            break;
            
            case 4:
            printf("Enter key:");
            scanf("%s",key);
            printf("%s\n",Search_Hashtable(ht,key));
            break;
            
            case 5:
            print_details(ht);
            break;

            default:
            printf("wrong number !,Do you want to exit program ?:\n Y:1 \n N:0");
            scanf("%d",&x);
            if(x==0)
            {
                break;
            }
        }
    }
}