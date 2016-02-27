#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct values{
	char* name;
	int value;
	struct values* next;};

int is_in(char carat, char* lista){
	int i=0;
	while(lista[i]!='\0'){
		if(carat==lista[i])
			return 1;
		i++;
	}
	return 0;
}

int conta_operazioni(char* expr){
	int i=0,conta=0;
	while(expr[i]!='\0'){
		if(is_in(expr[i],"+-/*"))
			conta++;
		i++;
	}
	return conta;
}

void insert(char* name, int value, struct values** head){
	struct values* new;
	if(*head==NULL || strcmp(name,(*head)->name)<0){
		new=(struct values*)malloc(sizeof(struct values));
		new->name=strdup(name);
		new->value=value;
		new->next=(*head);
		(*head)=new;
	}
	else 
		if(strcmp(name,(*head)->name)==0)
			(*head)->value=value;
		else
			insert(name,value,&((*head)->next));
}

char* nxt_sign(char* expr){
	int i=1;
	while(!is_in(expr[i],"+-") && expr[i]!='\0'){
		i++;
	}
	if(expr[i]!='\0')
		return expr+i;
	return NULL;
}

char* nxt_prod(char* expr){
	int i=1;
	while(!is_in(expr[i],"*/+-") && expr[i]!='\0'){
		i++;
	}
	if(expr[i]!='\0')
		return expr+i;
	return NULL;
}

int eval(char* assign, char* expr){
	char* token;
	char* delim=strdup(";"), *name;
	int i=0,value,res=0;
	struct values* head, *find, *prod;
	char* sign, *nxt_op;
	int tmp, prodotto;
	sign=NULL;
	head=NULL;
	token=strtok(strdup(assign),delim);
	while(token!=NULL){
		i=0;
		name=(char*)malloc(sizeof(char)*10);
		while(token[i]!='='){
			name[i]=token[i];
			i++;}
		token+=i+1;
		if(token[i]=='-'){
			token++;
			value=atoi(token)*(-1);
		}
		else
			value=atoi(token);
		insert(name,value,&head);
		name=strdup("\0");
		free(name);
		name=NULL;
		token=strtok(NULL,delim);
	}
	find=head;
	while(find!=NULL){
		printf("%s --> %d\n",find->name,find->value);
		find=find->next;
	}
	delim="+-*/";
	token=strtok(strdup(expr),delim);
	if(expr[0]=='-')
		sign=expr;
	nxt_op=expr;
	while(token!=NULL){
		find=head;
		tmp=0;
		while(strcmp(find->name,token)!=0 && find->next!=NULL)
			find=find->next;
		
		nxt_op=nxt_prod(nxt_op);
		tmp=find->value;
		name=token;
		prodotto=find->value;
		while(nxt_op!=NULL && is_in(*nxt_op,"*/")){
			token=strtok(NULL,delim);
			prod=head;
			while(strcmp(prod->name,token)!=0 && prod->next!=NULL)
				prod=prod->next;
			if(strcmp(prod->name,token)==0){
				if(*nxt_op=='*')
					prodotto=prodotto*prod->value;
				else
					prodotto=prodotto/prod->value;
			}
			nxt_op=nxt_prod(nxt_op);
		}
		find->value=prodotto;
		if(strcmp(find->name,name)==0){
			if(sign==NULL || *sign=='+')
				res+=find->value;
			else
				res-=find->value;}
		find->value=tmp;
		tmp=0;
		
		token=strtok(NULL,delim);
		if(sign==NULL)
			sign=expr;
		sign=nxt_sign(sign);
	}
	return res;
}

int main(){
	printf("%d\n",eval("casa=7;albero=2;b=-10","-albero*albero/albero*casa*albero-b*albero*casa/casa*albero"));
//	char* expr=strdup("albero+casa-b");
//	char* sign;
//	sign=expr;
//	printf("%p\n", nxt_prod(sign));
	//printf("%c\n", *nxt_sign(sign));
//	sign=nxt_prod(sign);
//	printf("%p\n", nxt_sign(sign));
	/*printf("%c\n", *nxt_sign(sign));
	sign=nxt_sign(sign);
	printf("%p\n", nxt_sign(sign));
	printf("%c\n", *nxt_sign(sign));
	sign=nxt_sign(sign);
	printf("%p\n", nxt_sign(sign));*/
	return 0;
}
