import socket
import msvcrt

sock = socket.socket() #создаем сокет
sock.bind(("", 9076)) # Порт на котором будем принимать сообщения
sock.listen(5) #максимальновозможное кол-во подключений
conn, addr = sock.accept() # ждем подлкючение нам вернется котреж с сокетом и ip клиента

print("New connection from ", addr)
value_ob=conn.recv(1024) # max кол-во байт для чтения 1024
switch = {
    'w': 'forward',
    's': 'back',
    'd': 'right',
    'a': 'left',
    'q': 'tankLeft',
    'e': 'tankRight'
}

while True:
    print(value_ob)
    key = msvcrt.getwche().lower()
    #if switch.has_key(key):
    if key in switch:
        conn.sendto(switch[key].encode(), addr)
        print(switch[key])
        continue
    else:
        conn.sendto("zero".encode(), addr)
    print("Key Error")