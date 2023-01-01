// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080
   
int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    char mensagem[300], numero_quest[10];
    int exe = 0;
    
    //Realiza as verificações do Socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    
    
    //Escolhe o exercicio
    printf("Selecione um exercício:\n");
    scanf("%d%*c", &exe);
    
    if(exe == 0)
    {
    	send(sock, hello, strlen(hello), 0);//envia a mensagen para o servidor
    	printf("Mensagem enviada para o servidor\n");
    }	
    
    if(exe == 1)
    	printf("%d- Digite o nome, o cargo e o salario: (separados e finalizado por ponto e virgula)\n", exe);   
    
    if(exe == 2)
    	printf("%d- Digite o nome, o sexo e a idade: (separados e finalizado por ponto e virgula)\n", exe);
    
    if(exe == 3)
    	printf("%d- Digite as 3 notas, n1, n2, n3: (separados e finalizado por ponto e virgula)\n", exe);
    
    if(exe == 4)
    	printf("%d- Digite altura e sexo: (separados e finalizado por ponto e virgula)\n", exe);

    
    if(exe == 5)
    	printf("%d- Digite a idade:\n", exe);
      
    if(exe == 6)
    	printf("%d- Digite nome, nivel, salario bruto e numero de dependentes: (separados e finalizado por ponto e virgula)\n", exe);
    	
    if(exe == 7)
    	printf("%d- Didite a idade e o tempo de serviço: (separados e finalizado por ponto e virgula)\n", exe);
    	
    if(exe == 8)
    	printf("%d- Didite seu saldo médio:\n", exe);
    
    if(exe > 0 && exe < 10)
    {
	fgets(mensagem, 300, stdin);//Escreve a mensagem completa
	mensagem[strlen(mensagem)-1] = '\0';//finaliza com \0	
	sprintf(numero_quest, "%d; ", exe);//indica o numero da questão na mensagem
	strcat(numero_quest, mensagem); //concatena a mensagem com o numero da questão

	send(sock, numero_quest, strlen(numero_quest), 0);//envia a mensagen para o servidor
	printf("Mensagem enviada para o servidor\n");
    }
    
    valread = read(sock, buffer, 1024);//le a mensagem do servidor
    printf("Resultado=> %s\n", buffer);
    	
    return 0;
}
