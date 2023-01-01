import zmq

context = zmq.Context()
p = "tcp://" + "192.168.40.50" + ":" + "5555" # how and where to communicate

n = context.socket(zmq.SUB) # create a subscriber socket
n.connect(p) # connect to the server
n.setsockopt_string(zmq.SUBSCRIBE, "DADOS") # subscribe to TIME messages

#c = context.socket(zmq.SUB) # create a subscriber socket
#c.connect(p) # connect to the server
#c.setsockopt_string(zmq.SUBSCRIBE, "CARGO") # subscribe to TIME messages

#s = context.socket(zmq.SUB) # create a subscriber socket
#s.connect(p) # connect to the server
#s.setsockopt_string(zmq.SUBSCRIBE, "SALARIO") # subscribe to TIME messages

for i in range(5): # Five iterations
    nome = n.recv() # receive a message
    nome = str(nome)
    aux = []
    aux = nome.split(",")
    print(aux[1])
    
    #cargo = c.recv()
    #print(cargo)

    #sal = s.recv()
    #print(sal)
