#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"
#include "tree.h"

nodeType* parse_expr(nodeType **node, treeType **tree);
nodeType* parse_term(nodeType **node, treeType **tree);
nodeType* parse_factor(nodeType **node, treeType **tree);
nodeType* parse_primary_expr(nodeType **node, treeType **tree);

nodeType* parse_expr(nodeType **node, treeType **ast){   //<expr> ::= <term> (("+" | "-") <term>)*
	
	nodeType* parsHead=NULL;
	nodeType* nextHead=NULL;
	nodeType* rightHead=NULL;

	parsHead = *node;  //parser point
	nextHead = *node;   //parser result point

	treeType* left = NULL;
	treeType* right = NULL;
	treeType* add = NULL;


	printf("<expr> -> ");

	parsHead = parse_term( &parsHead, &left);  //term parser
	nextHead = parsHead;

	//printf(" 11111 ");
 
	while(strcmp(parsHead->valse,"+")==0 || strcmp(parsHead->valse,"-")==0){

		if(strcmp(parsHead->valse,"+")==0 || strcmp(parsHead->valse,"-")==0){  // "+" | "-"
				//printf("\n%s:%s slice", parsHead->type, parsHead->valse);

			printf("\n%s\n", parsHead->valse);
			add = createTree("",parsHead->valse);

			rightHead = parsHead->next;   //<<term>>
			parsHead = parse_term(&rightHead,&right);
			nextHead = parsHead;

			addRight(add,right);
			addLeft(add,left);

			left = add;

			continue;
		}

		if(parsHead->next == NULL){     //<<term>>
			break;
		}

		parsHead = parsHead->next;
	}

	*ast = left;

	return nextHead; 
  
}

nodeType* parse_term(nodeType **node, treeType **ast){   //<term> ::= <factor> ("*" <factor>)*

	nodeType* parsHead=NULL;
	nodeType* rightHead=NULL;
	nodeType* nextHead=NULL;

	parsHead = *node;
	nextHead = *node;
	
	treeType* left = NULL;
	treeType* right = NULL;
	treeType* mul = NULL;

	printf("<term> -> ");

	parsHead = parse_factor( &parsHead, &left);
	nextHead = parsHead;

	//printf("%s",parsHead->valse);


	while(strcmp(parsHead->valse,"*")==0 || strcmp(parsHead->valse,"/")==0){

			if(strcmp(parsHead->valse,"*")==0 || strcmp(parsHead->valse,"/")==0){  // "/" | "*"
				//printf("\n%s:%s slice", parsHead->type, parsHead->valse);
				printf("\n%s\n", parsHead->valse);

				mul = createTree("",parsHead->valse);

				rightHead = parsHead->next;   //<factor>
				parsHead = parse_factor( &rightHead, &right);
				nextHead = parsHead;

				addRight(mul,right);
				addLeft(mul,left);

				left = mul;

				continue;

			}

			if(parsHead->next == NULL){     //<factor>
				break;	
			}

			parsHead = parsHead->next;
	}

	*ast = left;

	return nextHead;
}

nodeType* parse_factor(nodeType **node, treeType **ast){  //<factor> ::= <primary-expr> | ("+" | "-") <factor>

	nodeType* parsHead=NULL;
	nodeType* nextHead=NULL;
	nodeType* rightHead=NULL;

	parsHead = *node;
	//leftHead = *node;

	treeType* _ast = NULL;
	treeType* add = NULL;
	treeType* dum = NULL;

	printf("<factor> -> ");

	parsHead = parse_primary_expr(&parsHead,&_ast);   // <primary-expr>

	//printf("%s\n",parsHead->valse);
	if(parsHead != *node){
		//printf("%s\n",parsHead->valse);
		//addLeft(ast,left);
		*ast = _ast;
		//printf("%s",parsHead->valse);
		return parsHead;
	}else{
	                                     //  ("+" | "-") <factor>
		//parsHead = parsHead->next;

		if(strcmp(parsHead->valse,"+")==0 || strcmp(parsHead->valse,"-")==0){  // "+" | "-"
				//printf("\n%s:%s slice", parsHead->type, parsHead->valse);
			printf("\n%s\n", parsHead->valse);

			add = createTree("",parsHead->valse);
			dum = createTree("","0");

			parsHead = parsHead->next;
			parsHead = parse_factor(&parsHead,&_ast);   // <factor>

			addRight(add , _ast);
			addLeft(add , dum);

			*ast = add;
			//addLeft(ast,right);
		}

	}

	return parsHead;

}

nodeType* parse_primary_expr(nodeType **node, treeType **ast){  //<primary-expr> ::= <decimal> | "(" <expr> ")"

	nodeType* parsHead=NULL;
	nodeType* leftHead=NULL;
	nodeType* nextHead=NULL;

	parsHead = *node;
	nextHead = *node;

	treeType* _ast = NULL;
	//treeType* ast = NULL;
	//ast = *tree;

	//printf("<primary_expr> -> ");


	//parsHead = parsHead->next;
	//printf("\n%s:%s", parsHead->type, parsHead->valse);
	if(strcmp(parsHead->type,"digit")==0){  //  12
		printf("<primary_expr> -> ");
		printf("<decimal> -> %s\n", parsHead->valse);

		treeType* new = createTree("",parsHead->valse);

		*ast = new;

		nextHead = parsHead->next;
		return nextHead;
	}

	if(strcmp(parsHead->valse,"(")==0){     // (12...)
		printf("<primary_expr> -> ");
		//printf("<expr> ->");
		parsHead = parsHead->next;     // 12...

		parsHead = parse_expr( &parsHead, &_ast);
		//printf("%s-",parsHead->valse);
		nextHead = parsHead->next;   // ")"
		//nextHead = parsHead;
		//printf("%s-",nextHead->valse);
	
	
		*ast = _ast; 

		//printf("()");	
	}
	//else{
	//	return parsHead;
	//}

	return nextHead;


}


int isOperator(char c){
	char Operators[] = "[+-*/^%=(),]";
	int i=0;
	char temp;
	while(1){
		temp = Operators[i];
		if(temp == '\0'){
			break;
		}
		if(temp == c){
			return 1;
		}
		i++;
	}

	return 0;
}

int isDigit(char c){

	if( c<='9' &&  c>='0' ){
		return 1;
	}

	return 0;
}

int isWhiteSpace(char c){

	if( c==' ' ){
		return 1;
	}

	return 0;
}

int isIdentifier(char c){
	if( !isOperator(c) && !isDigit(c) && !isWhiteSpace(c)){
		return 1;
	}
	return 0;
}

char *charTostring(char in){
	static char str[2];
	str[0] = in;
	str[1] = '\0';
	// a\0 , b\0, c\0, d\0 .....
	return str;
}

int main(int argc, char *argv[]){
//int main(){
	//char input[] = "(1+2)+2";
	//char input[] = "12.1 + 21*23*111 - 13";
	//char (*Token)[256];
	char c;
	int i=0;

	//printf("%s\n",argv[1]);

	char *input = argv[1];

	//char o[4];

	nodeType *token = NULL;

	//char num[16] = "";
	char num[16] = "";
	char num2[16] = "";
	char str[]= "";
	char temp[2] = ""; 

	c = input[0];
	while(1){
		//char n[] = "";
		//c = input[i];
		//printf("%c", c);
		num[0]='\0';
		num2[0]='\0';
		str[0]='\0';
		temp[0]='\0';

		if(c == '\0'){
			printf("\ntoken parser ok\n");
			break;
		}  //end
 

		if(isWhiteSpace(c)){

			i++;
			c = input[i];
			//continue;
		}
		else if(isOperator(c)){
			//printf("%c", c);

			//printf("[%c]",c);
			//charTostring(c)
			//temp[2];
			temp[0]=c;
			temp[1]='\0';
			//printf("%s\n",temp);
			append(&token,"operator",temp);

			i++;
			c = input[i];

			//continue;
		}
		else if(isDigit(c)){
			//char num[16] = "";
			//num[0] = '\0';
			
			temp[0]=c;
			temp[1]='\0';
			strcat(num, temp);

			//sprintf(t,"%s",c);
			//strcat(num, t);

			while(1){               ///123.XXXX
				i++;
				c = input[i];
				
				if(isDigit(c)){

					temp[0]=c;
					temp[1]='\0';
					strcat(num, temp);

				}else{
					break;
				}

			}

			temp[0]='\0';

			if(c == '.'){   //XXX.1234
				
				char point[2];
				point[0]=c;
				point[1]='\0';
				strcat(num2, point);				

				while(1){
					i++;
					c = input[i];
					if(isDigit(c)){

						//char d2[2];
						temp[0]=c;
						temp[1]='\0';
						strcat(num2, temp);
						
					}else{
						break;
					}
				}
			}

			strcat(num, num2);
			//printf("[%s]",num);
			//printf("(%c)",c);
			append(&token,"digit",num);

		}
		else if(isIdentifier(c)){

			temp[0]=c;
			temp[1]='\0';
			strcat(str, temp);

			while(1){
				i++;
				c = input[i];
				if(isIdentifier(c)){

						//char d2[2];
					temp[0]=c;
					temp[1]='\0';
					strcat(str, temp);
						
				}else{
					break;
				}

			}
			//printf("[%s]",str);
			//printf("(%c)",c);
			append(&token,"id",str);
			//continue;
		}

		//printf("-");

		//printf+("%c",c);
		//i++;
	}

	append(&token,"(end)","");

	nodeType* output = NULL;
	output = token;

	printf("\n****token****");
	printf("\n%s:%s", output->type, output->valse);
	while(1){
		output = output->next;
		printf("\n%s:%s", output->type, output->valse);
		if(output->next == NULL){
			break;
		}
	}


	printf("\n\n");



	treeType *ast = NULL;

	nodeType *nextNode;
	nextNode = parse_expr(&token, &ast);
	//printf("\n%s--%s",nextNode->type,nextNode->valse);

	printf("\nast\n");
	printf("%s\n",input);
	float result = preOrder(ast);

	printf("\n********result*******");
	printf("\n%s = %f",input,result);
	printf("\n********result*******");


/*
	
	//append(&token,"plus2", "+");
	//append(&token,"plus3", "+");

	printf("\n****token paser****");
	printf("\n%s:%s", token->type, token->valse);
	while(1){
		token = token->next;
		printf("\n%s:%s", token->type, token->valse);
		if(token->next == NULL){
			break;
		}
	}
	//while(token->next != NULL) 

*/



	return 0;
}


