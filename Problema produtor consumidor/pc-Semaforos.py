import threading as tr
import time
import random

lista = []         

MAX_NUM = 10       

sem = tr.Semaphore()  #inicia o semaforo

class Produtor(tr.Thread):
    def run(self):
        nums = range(10) 
        global lista
        
        while True:
            sem.acquire() #pega o semforo depois da operação ser consumida (decrementa o contador interno em 1)
            if (len(lista) == MAX_NUM):
                print ("Lista cheia! Produtor em espera!")
                sem.release() #libera o semaforo (incrementa o contador interno em 1)
                print ("Espaço na fila disponivel, consumidor notificou o produtor.")

            num = random.choice(nums) #Escolhe um numero aleatório de 0 a 4
            lista.append(num) #Coloca o numero aleatório no final da lista
            print ("Produtor =>", num) 
            sem.release() 

            time.sleep(random.random()) 

class Consumidor(tr.Thread):
    def run(self):
        global lista
        
        while True:
            sem.acquire() #pega o semforo depois da operação ser consumida (decrementa o contador interno em 1)
            if not lista:
                print ("A lista está vazia! Consumidor em espera!")
                sem.release() 
                print ("Produtor adicionou algo à fila e notificou o consumidor.")
            else:
                num = lista.pop(0) #remove o primeiro da lista e retorna seu valor
            
                print ("Consumido =>", num)
                sem.release()  #libera o semáforo
                
            time.sleep(random.random())

def main():
    Produtor().start() 
    Consumidor().start()    

if __name__ == '__main__':
    main()
