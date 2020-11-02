import logging

import threading
import time
import queue

logging.basicConfig(level=logging.DEBUG, format='%(threadName)s: %(message)s')

# memo:　開始時間を同期する。

def worker1(barrier):
    barrier.wait()
    while True:
        logging.debug('start')
        time.sleep(3)
        logging.debug('end')


def worker2(barrier):
    barrier.wait()
    while True:
        logging.debug('start')
        time.sleep(3)
        logging.debug('end')


if __name__ == '__main__':
    barrier = threading.Barrier(2)
    t1 = threading.Thread(target=worker1, args=(barrier, ))
    t2 = threading.Thread(target=worker2, args=(barrier,))

    t1.start()
    t2.start()




