// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080

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

int main(int argc, char const *argv[])
{
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char mensagem_original[300];
	char *hello = "Hello from server";
	char *aux[5];
	int i, exe;
	char resp[300];
       
	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
       
	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}


	//le a mensagem e copia para uma outra variavel
	valread = read(new_socket, buffer, 1024);
	printf("Mensagem recebida!\n");
	strcpy(mensagem_original, buffer);

	int tamanho = strlen(mensagem_original);
	char *token = strtok(mensagem_original, "; ");

	/*for (int i = 0; i < tamanho; i++) 
	{
	printf(token[i] == 0 ? "\\0" : "%c", token[i]);
	}*/

	i = 0;
	//separa a mensagem original em palavras
	while(token != NULL) 
	{
		aux[i] = token;
		//printf("%s\n", aux[i]);
		token = strtok(NULL, "; ");
		i++;
	}

	//printf("%s\n", buffer);

	exe = atoi(aux[0]); //converte a string em int
	//printf("%d\n", exe);

	if(exe == 0)
		strcpy(resp, hello);

	//Reajusta o salario de acordo com o cargo
	if(exe == 1)
	{
		reajusta_salario(aux[1], aux[2], aux[3], resp);
		//printf("%s\n", resp);
	}

	//diz se é de maior; Maioridade masculina é 18 e feminina é 21
	if(exe == 2)
	{
		maioridade(aux[1], aux[2], aux[3], resp);
		//printf("%s\n", resp);
	}

	if(exe == 3)
	{
		media_aprovado(aux[1], aux[2], aux[3], resp);
		//printf("%s\n", resp);
	}

	if(exe == 4)
	{
		peso_ideal(aux[1], aux[2], resp);
		//printf("%s\n", resp);
	}


	if(exe == 5)
	{
		categoria_nadador(aux[1], resp);
		//printf("%s\n", resp);
	}

	if(exe == 6)
	{
		salario_liquido(aux[1], aux[2], aux[3], aux[4], resp);
		//printf("%s\n", resp);
	}

	if(exe == 7)
	{
		aposentadoria(aux[1], aux[2], resp);
		//printf("%s\n", resp);
	}

	if(exe == 8)
	{
		credito(aux[1], resp);
		//printf("%s\n", resp);
	}

	send(new_socket , resp, strlen(resp) , 0); //envia o resultado para o cliente
	printf("Resultado enviado para o cliente\n");

	return 0;
}

