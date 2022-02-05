typedef struct node
{
    char* key;
    char* value;
    struct node* next;
}node;
typedef struct HashTable 
{
	unsigned int  count;
	unsigned int size;
    node** n_array;
}HashTable;
unsigned int GetHash(char*v,unsigned int size);
node* NewNode(char* key,char* value);
void init_HashTable(HashTable* p_ht,unsigned int size);
void insert_HashTable(HashTable* p_ht,char* key,char* value);
void  Rehash_HashTable(HashTable* p_ht);
void print_HashTable(HashTable ht);
char* Remove_HashTable(HashTable* p_ht,char*key);
char* Search_Hashtable(HashTable ht ,char*key);
void print_details(HashTable ht);