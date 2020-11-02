import logging

import threading
import time

logging.basicConfig(level=logging.DEBUG, format='%(threadName)s: %(message)s')

# 2つ以上のロックを実現したい時に利用する


def worker1(d, semaphore):
    with semaphore:
        logging.debug('start')
        time.sleep(5)
        logging.debug('end')


def worker2(d, semaphore):
    with semaphore:
        logging.debug('start')
        time.sleep(5)
        logging.debug('end')


def worker3(d, semaphore):
    with semaphore:
        logging.debug('start')
        time.sleep(5)
        logging.debug('end')


if __name__ == '__main__':
    d = {'x': 0}
    semaphore = threading.Semaphore(2)
    t1 = threading.Thread(target=worker1, args=(d, semaphore))
    t2 = threading.Thread(target=worker2, args=(d, semaphore))
    t3 = threading.Thread(target=worker3, args=(d, semaphore))

    t1.start()
    t2.start()
    t3.start()

    logging.debug('started')


