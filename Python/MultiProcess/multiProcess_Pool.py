import logging
import multiprocessing
import time

logging.basicConfig(
    level=logging.DEBUG, format="%(processName)s: %(message)s")

# プロセス間は共有メモリが無い


def worker1(i):
    logging.debug('start')
    time.sleep(5)
    logging.debug('end')
    return i


if __name__ == "__main__":
    with multiprocessing.Pool(5) as p:
        p1 = p.apply_async(worker1, (100, ))
        p2 = p.apply_async(worker1, (100,))
        logging.debug('executed')
        logging.debug(p1.get())
        logging.debug(p2.get())

