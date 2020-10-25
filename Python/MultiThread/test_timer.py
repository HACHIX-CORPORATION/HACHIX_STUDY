import logging

import threading
import time

logging.basicConfig(level=logging.DEBUG, format='%(threadName)s: %(message)s')


def worker1():
    logging.debug('start')
    time.sleep(5)
    logging.debug('end')


if __name__ == '__main__':
    t1 = threading.Timer(3, worker1)

    t1.start()

    logging.debug('started')
