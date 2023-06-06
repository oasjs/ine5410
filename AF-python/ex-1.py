from time import sleep
from random import randint
from threading import Thread, Lock, Condition

def produtor():
    global buffer
    global i
    i = 0
    with lock_produtor:
        while i < 10:
            sleep(randint(0, 2))           # fica um tempo produzindo...
            item = 'item ' + str(i)
            with lock:
                if len(buffer) == tam_buffer:
                    print('>>> Buffer cheio. Produtor ira aguardar.')
                    lugar_no_buffer.wait()    # aguarda que haja lugar no buffer
                buffer.append(item)
                print('Produzido %s (ha %i itens no buffer)' % (item, len(buffer)))
                item_no_buffer.notify()
            i += 1


def consumidor():
    global buffer
    global j
    j = 0
    with lock_consumidor:
        while j < 10:
            with lock:
                if len(buffer) == 0:
                    print('>>> Buffer vazio. Consumidor ira aguardar.')
                    item_no_buffer.wait()   # aguarda que haja um item para consumir
                item = buffer.pop(0)
                print('Consumido %s (ha %i itens no buffer)' % (item, len(buffer)))
                lugar_no_buffer.notify()
            sleep(randint(0, 2))         # fica um tempo consumindo...
            j += 1

buffer = []
tam_buffer = 5
lock = Lock()
lock_produtor = Lock()
lock_consumidor = Lock()
lugar_no_buffer = Condition(lock)
item_no_buffer = Condition(lock)

n_threads = 2
produtores = []
consumidores = []

for a in range(n_threads):
    produtores.append(Thread(target=produtor))
    consumidores.append(Thread(target=consumidor))
    produtores[a].start()
    consumidores[a].start()

for b in range(n_threads):
    produtores[b].join()
    consumidores[b].join()
