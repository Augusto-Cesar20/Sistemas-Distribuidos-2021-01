import zmq, time

context = zmq.Context()
s = context.socket(zmq.PUB) # create a publisher socket
p = "tcp://" + "192.168.40.50" + ":" + "5555" # how and where to communicate
s.bind(p) # bind socket to the address

while True:
    time.sleep(5) # wait every 5 seconds
    s.send("TIME " + time.asctime()) # publish the current time