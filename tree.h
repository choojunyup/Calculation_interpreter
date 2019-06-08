typedef struct tree
{	
	char *type;
	char *valse;
	struct tree *left;
	struct tree *right; 
	
}treeType;

treeType* createTree(char type[], char valse[]){
	treeType *p = NULL;

	p = malloc(sizeof(treeType)); 
	p->type = (char *)malloc(sizeof(char)*(signed)strlen(type));
	p->valse = (char *)malloc(sizeof(char)*(signed)strlen(type));

	strcpy(p->type, type);
	strcpy(p->valse, valse);

	p->left = NULL;
	p->right = NULL;

	return p;
}

int addLeft(treeType *head, treeType *newTree){
	treeType *p = head;

	if(p->left != NULL){
		return 0;
	}else{
		p->left = newTree;
	}

}

int addRight(treeType *head,treeType *newTree){
	treeType *p = head;


	if(p->right != NULL){
		return 0;
	}else{
		p->right = newTree;
	}

}

float preOrder(treeType *t){
	//printf("(%s)",t->valse );
	//printf("\n");

	float value = 0.0f;
	float valueL = 0.0f;
	float valueR = 0.0f;
	char *m;

	//if( t->left != NULL || t->right != NULL ){
		//printf("\n");
	//}
		//printf(">\n");

	m = t->valse ;
	printf("(%s)", m );


	if(t->left){
		//printf("\n");
		valueL = preOrder(t->left);
		//printf("\n",valueL);
	}
	//printf("(%s)",t->valse );
	if(t->right){
		//printf("\n");
		valueR = preOrder(t->right);
		//printf("\n");
	}


	
	if(!strcmp ("+",m)){

		value = valueL + valueR;

	}else if(!strcmp ("-",m)){

		value = valueL - valueR;

	}else if(!strcmp ("*",m)){

		value = valueL * valueR;

	}else if(!strcmp ("/",m)){

		value = valueL / valueR;

	}else {
		value = atof(m);
	}


	return	value;
}