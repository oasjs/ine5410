from time import sleep
from random import randint
from threading import Thread, Semaphore


def produtor():
    global buffer
    for i in range(10):
        sleep(randint(0, 2))           # fica um tempo produzindo...
        item = 'item ' + str(i)
        # verifica se há lugar no buffer
        semaphore.release()
        buffer.append(item)
        print('Produzido %s (ha %i itens no buffer)' % (item, len(buffer)))


def consumidor():
    global buffer
    for i in range(10):
        # aguarda que haja um item para consumir
        semaphore.acquire()
        item = buffer.pop(0)
        print('Consumido %s (ha %i itens no buffer)' % (item, len(buffer)))
        sleep(randint(0, 2))         # fica um tempo consumindo...


buffer = []
tam_buffer = 3
# cria semáforos
semaphore = Semaphore(0)
produtor = Thread(target=produtor)
consumidor = Thread(target=consumidor)
produtor.start()
consumidor.start()
produtor.join()
consumidor.join()
