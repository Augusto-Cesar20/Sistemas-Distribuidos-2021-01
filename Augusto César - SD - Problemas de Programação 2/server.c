#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4455

void reajusta_salario (char *nome, char *cargo, char *salario, char *resp);
void maioridade (char *nome, char *sexo, char *idade, char *resp);
void media_aprovado (char *nota1, char *nota2, char *nota3, char *resp);
void peso_ideal (char *altura, char *sexo, char *resp);
void categoria_nadador (char *idade, char *resp);
void salario_liquido(char *nome, char *nivel, char *salario_bruto, char *numero, char *resp);
void aposentadoria (char *idade, char *tempo_serv, char *resp);
void credito (char *saldo_medio, char *resp);

int main() {

	// Variables and structures
	int server_fd, client_fd;
	struct sockaddr_in server_addr, client_addr;
	socklen_t addr_size;
	char buffer[1024];
	char *hello = "Hello from server";

	// Server socket
	server_fd = socket(AF_INET, SOCK_STREAM, 0);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	listen(server_fd, 5);
	printf("[LISTENING] Port Number: %d\n", PORT);

	while (1) 
	{
		char mensagem_original[300];
		char *aux[5];
		int i, exe;
		char resp[300];	
		
		client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_size);
		printf("[CONNECTED] New Connection\n");
		
		memset(buffer, '\0', sizeof(buffer));
		recv(client_fd, buffer, 1024, 0);
		printf("[CLIENT] %s\n", buffer);
		
		strcpy(mensagem_original, buffer);
    
    		int tamanho = strlen(mensagem_original);
		char *token = strtok(mensagem_original, "; ");
		
		i = 0;
		while(token != NULL) 
		{
			aux[i] = token;
			token = strtok(NULL, "; ");
			i++;
		}

		exe = atoi(aux[0]);

    		if(exe == 0)
			strcpy(resp, hello);
    

		if(exe == 1)
			reajusta_salario(aux[1], aux[2], aux[3], resp);

    		if(exe == 2)
			maioridade(aux[1], aux[2], aux[3], resp);

    
    		if(exe == 3)
			media_aprovado(aux[1], aux[2], aux[3], resp);
	
		if(exe == 4)
			peso_ideal(aux[1], aux[2], resp);

       
		if(exe == 5)
			categoria_nadador(aux[1], resp);

	
		if(exe == 6)
			salario_liquido(aux[1], aux[2], aux[3], aux[4], resp);

	
		if(exe == 7)
			aposentadoria(aux[1], aux[2], resp);

	
		if(exe == 8)
			credito(aux[1], resp);
	  
		send(client_fd, resp, strlen(resp), 0);
		
		close(client_fd);
		printf("[DISCONNECTED] Connection closed\n");

	}

	close(server_fd);

	return 0;
}

void reajusta_salario (char *nome, char *cargo, char *salario, char *resp)
{
	float sal;
	char rSal[20];
	
	sal = atof(salario);//converte string para float
	
	if(strcmp(cargo, "operador") == 0)
		sal = sal + (sal*0.20);
	
	if(strcmp(cargo, "programador") == 0)
		sal = sal + (sal*0.18);
	
	//printf("%f\n", sal);
	
	sprintf(rSal, "%.2f", sal);//tingransforma o tipo float em str
	
	//printf("%s\n", rSal);
	
	sprintf(resp, "Nome: %s; Salario reajustado: %s", nome, rSal);//concatena a frase
}

void maioridade (char *nome, char *sexo, char *idade, char *resp)
{
	int ida;
	
	ida = atoi(idade);
	
	if(strcmp(sexo, "M") == 0 && ida >= 18)
	{
		sprintf(resp, "Nome: %s; Já é maior de idade!", nome);//concatena a frase
	} else {
		if(strcmp(sexo, "F") == 0 && ida >= 21)
			sprintf(resp, "Nome: %s; Já é maior de idade!", nome);//concatena a frase
		else
			sprintf(resp, "Nome: %s; NÃO é maior de idade!", nome);//concatena a frase
	}
}

void media_aprovado (char *nota1, char *nota2, char *nota3, char *resp)
{
	float n1 = atof(nota1);
	float n2 = atof(nota2);
	float n3 = atof(nota3);
	
	if((n1 + n2)/2 >= 7.0)
	{
		sprintf(resp, "Media (n1 e n2): %.2f; Aprovado", (n1 + n2)/2);
	} else {
		if((n1 + n2 + n3)/3 >= 5.0)
		{
			sprintf(resp, "Media (n1, n2, n3): %.2f; Aprovado", (n1 + n2 + n3)/3);
		} else {
			sprintf(resp, "Media: %.2f; Reprovado!", (n1 + n2 + n3)/3);
		}
	}
}

void peso_ideal (char *altura, char *sexo, char *resp)
{
	float a1 = atof(altura);
	
	if(strcmp(sexo, "M") == 0)
		sprintf(resp, "Peso ideal: %.2f;", (72.7*a1)-58.0);
	if(strcmp(sexo, "F") == 0)
		sprintf(resp, "Peso ideal: %.2f;", (62.1*a1)-44.7);
}

void categoria_nadador (char *idade, char *resp)
{
	int ida = atoi(idade);
	
	if(ida >= 5 && ida <= 7)
		sprintf(resp, "Categoria: infantil A");
	if(ida >= 8 && ida <= 10)
		sprintf(resp, "Categoria: infatil B");
	if(ida >= 11 && ida <= 13)
		sprintf(resp, "Categoria: juvenil a");
	if(ida >= 14 && ida <= 17)
		sprintf(resp, "Categoria: juvenil B");
	if(ida >= 18)
		sprintf(resp, "Categoria: adulto");
}

void salario_liquido(char *nome, char *nivel, char *salario_bruto, char *numero, char *resp)
{
	int n = atoi(numero);
	float sal_b = atof(salario_bruto);
	
	if(strcmp(nivel, "A") == 0)
	{
		if(n > 0)
			sal_b = sal_b - (sal_b*0.08);
		else
			sal_b = sal_b - (sal_b*0.03);
	}
	
	if(strcmp(nivel, "B") == 0)
	{
		if(n > 0)
			sal_b = sal_b - (sal_b*0.10);
		else
			sal_b = sal_b - (sal_b*0.05);
	}
	
	if(strcmp(nivel, "C") == 0)
	{
		if(n > 0)
			sal_b = sal_b - (sal_b*0.15);
		else
			sal_b = sal_b - (sal_b*0.08);
	}
	
	if(strcmp(nivel, "D") == 0)
	{
		if(n > 0)
			sal_b = sal_b - (sal_b*0.10);
		else
			sal_b = sal_b - (sal_b*0.17);
	}
	
	sprintf(resp, "Nome: %s; Salario liquido: %.2f;", nome, sal_b);
}

void aposentadoria (char *idade, char *tempo_serv, char *resp)
{
	int i = atoi(idade);
	int t = atoi(tempo_serv);	
	
	if(i >= 65)
	{
		sprintf(resp, "Parabéns! O senhor tá velho!");
	} else {
		if(t >= 30)
		{
			sprintf(resp, "Parabéns! Você ja trabalhou muito!");
		} else {
			if (i >= 60 && t >= 25)
				sprintf(resp, "Parabéns! Você ja trabalhou muito e está velho!");
			else
				sprintf(resp, "Você não pode se aposentar ainda!");
		}
	}
}

void credito (char *saldo_medio, char *resp)
{
	float s = atof(saldo_medio);
	
	if(s <= 200)
		sprintf(resp, "Nenhum crédito!");
	
	if(s > 200 && s < 400)
		sprintf(resp, "Voce recebera 20 por cento, => %.2f", s*0.2);
	
	if(s > 400 && s < 600)
		sprintf(resp, "Voce recebera 30 por cento, => %.2f", s*0.3);
	
	if(s >= 600)
		sprintf(resp, "Voce recebera 40 por cento, => %.2f", s*0.4);
}
