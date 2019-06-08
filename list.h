typedef struct node
{	
	char *type;
	char *valse;
	struct node *next;
}nodeType;

nodeType* createNode(char type[], char valse[]){
	nodeType *p = NULL;

	//printf("-%i-",strlen(valse));

	p = malloc(sizeof(nodeType));
	p->type = (char *)malloc(sizeof(char)*(signed)strlen(type));
	p->valse = (char *)malloc(sizeof(char)*(signed)strlen(valse));
	strcpy(p->type, type);
	strcpy(p->valse, valse);
	p->next = NULL;


	return p;
}

void deleteNode(nodeType **node){
	free(*node);
	*node = NULL;
}

void append(nodeType **head, char type[], char valse[]){
	nodeType *ptr = *head;
	nodeType *newNode = createNode(type, valse);

	if(ptr == NULL){
		*head = newNode;
	}else{
		while(ptr->next != NULL){
			ptr = ptr->next;
		}
		ptr->next = newNode;
	}
}

nodeType *get(nodeType *head, int index)
{
	nodeType *ptr = head;

	while(ptr->next != NULL && index > 0) {
		index--;
		ptr = ptr->next;
	}

	return ptr;
}