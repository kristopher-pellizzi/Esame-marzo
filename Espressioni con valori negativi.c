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

int eval(char* assign, char* expr){
	char* token;
	char* delim=strdup(";"), *name;
	int i=0,value,res=0;
	struct values* head, *find;
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
	delim="+-*";
	token=strtok(strdup(expr),delim);
	while(token!=NULL){
		find=head;
		while(strcmp(find->name,token)!=0 && find->next!=NULL)
			find=find->next;
		if(strcmp(find->name,token)==0)
			res+=find->value;
		token=strtok(NULL,delim);
	}
	return res;
}

int main(){
	printf("%d\n",eval("casa=98;albero=2;b=-10","albero+casa+b"));
	return 0;
}
