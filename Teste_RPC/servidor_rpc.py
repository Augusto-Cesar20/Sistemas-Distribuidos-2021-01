from xmlrpc.server import SimpleXMLRPCServer
from datetime import datetime

server = SimpleXMLRPCServer(("localhost", 4455))

server.register_instance(datetime)

server.serve_forever()