import xmlrpc.client

server = xmlrpc.client.ServerProxy("http://localhost:4455")

print (server.now())