#define SIZE_OF_ht 10
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LOAD_FACTOR 0.75 
#include <limits.h>
#include "HashTable.h"


unsigned int GetHash(char*v,unsigned int size)
{
    int n =strlen(v);
    unsigned int sum=0;
    int i=0;
   
    unsigned int hash_value;
    for(i=0;i<n;i++)
    {
        sum=sum*37 +v[i];
    }
    hash_value=sum%size;
    return hash_value;
}
node* NewNode(char* key,char* value)
{
	node* nn=(node*)malloc(sizeof(node));
	nn->key=(char*)malloc(sizeof(char)*(strlen(key)+1));
	nn->value=(char*)malloc(sizeof(char)*(strlen(value)+1));
	strcpy(nn->key,key);
	strcpy(nn->value,value);
	nn->next=NULL;
	return nn;
}

void init_HashTable(HashTable* p_ht,unsigned int size)
{
	p_ht->size=size;
	p_ht->count =0;
    p_ht->n_array=(node**)malloc(sizeof(node*)*size);
    if(!p_ht->n_array)
    {
        return;
    }
    int i =0;
    for(i=0;i<size;i++)
    {
        p_ht->n_array[i]=NULL;
    }
    return;
          
}

void insert_HashTable(HashTable* p_ht,char* key,char* value)
{ 
	if (((double)p_ht->count/(double)p_ht->size)>0.9)
	{
		printf("The current Hashtable is:\n");
		printf("********************************************************************\n");
		print_HashTable(*p_ht);
		printf("********************************************************************\n");
		printf("Rehashing......\n");
		printf("********************************************************************\n");
		Rehash_HashTable(p_ht);
		print_HashTable(*p_ht);
	}   
    unsigned int k=GetHash(key,p_ht->size);
    

    int temp_len;
    node* temp;
    node* pnode=p_ht->n_array[k];
    if (!pnode)
    {
    
	    node* new_node=NewNode(key,value);	
        p_ht->n_array[k]=new_node;
        p_ht->count++;
    }
    else
    {
    	
        while(pnode)
        {
        	 //updating existing value of a given key
            if(strcmp(pnode->key,key)==0)
            {
            
                free(pnode->value);
                pnode->value=(char*)malloc(sizeof(char)*(strlen(value)+1));
                strcpy(pnode->value,value);
    			return;
            }
            temp=pnode;
            pnode=pnode->next;
        }
        node* new_node=NewNode(key,value);
        temp->next=new_node;
        p_ht->count++;
    }
    
}
void  Rehash_HashTable(HashTable* p_ht)
{
	node** temp=p_ht->n_array;
	int n =p_ht->size;
	p_ht->size=(p_ht->size)*2;
	int i;
	p_ht->n_array=(node**)malloc(sizeof(node*)*(n*2));
	for(i=0;i<n*2;i++)
	{
		p_ht->n_array[i]=NULL;
	}
	p_ht->count=0;
	node* pnode;
	node* next;
	for(i=0;i<n;i++)
	{
		pnode=temp[i];
		while(pnode)
		{
			next=pnode->next;
			insert_HashTable(p_ht,pnode->key,pnode->value);
			free(pnode);
			pnode=next;
		}
		
		
	}
	
}

void print_HashTable(HashTable ht)
{
    int i=0;
    node* pnode;
    
    for(i=0;i<ht.size;i++)
    {
        printf("-------------------------------------------------\n");
    	printf("SLOT[%d]",i);
    	
        node* pnode=ht.n_array[i];
        if(!pnode)
        {
        	printf(":NULL");
		}
		
       while(pnode)
       {
       		
       		printf(" :%s=>",pnode->key);
        	printf("%s",pnode->value);
        	printf("|");
            pnode=pnode->next;
            
       }
       printf("\n");
    
    }
    printf("-------------------------------------------------\n");
}
char* Remove_HashTable(HashTable* p_ht,char*key)
{   
    unsigned int k=GetHash(key,p_ht->size);
    node* pnode=p_ht->n_array[k];
    node*prev=p_ht->n_array[k];
    if(strcmp(pnode->key,key)==0)
    {
    	char*temp=(char*)malloc(sizeof(char)*(strlen(pnode->value)+1));
    	strcpy(temp,pnode->value);
    	free(pnode);
    	p_ht->n_array[k]=NULL;
    	return temp;
    	
	}
	while(pnode)
	{
		if(strcmp(pnode->key,key)==0)
		{
		    char*temp=(char*)malloc(sizeof(char)*(strlen(pnode->value)+1));
			strcpy(temp,pnode->value);
			prev->next=pnode->next;
			free(pnode);
			return temp;
		}
		prev=pnode;
		pnode=pnode->next;
	}
}
char* Search_Hashtable(HashTable ht ,char*key)
{
    unsigned int k=GetHash(key,ht.size);
    node* pnode=ht.n_array[k];
    while(pnode)
    {
        if(strcmp(pnode->key,key)==0)
        {
            return pnode->value;
        }
        pnode=pnode->next;
    }
    char* def="Wrong key entered !";
    return def;
    
}
void print_details(HashTable ht)
{
	printf("Number of Enteries in HashTable %d\n",ht.count);
	printf("Number of slots in HashTable %d\n",ht.size);
	float load_factor=(float)ht.count/(float)ht.size;
	printf("Load Factor of HashTable is %f\n",load_factor);
	
	return;
}
