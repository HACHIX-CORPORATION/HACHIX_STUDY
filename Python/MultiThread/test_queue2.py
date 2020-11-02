import logging

import threading
import time
import queue

logging.basicConfig(level=logging.DEBUG, format='%(threadName)s: %(message)s')

# 処理の実行順番を保ちたい場合に、実施する。


def worker1(queue):
    logging.debug('start')
    while True:
        item = queue.get()
        if item is None:
            break
        logging.debug(item)
        queue.task_done()
    logging.debug('longgggggggggggg')
    logging.debug('end')


if __name__ == '__main__':
    queue = queue.Queue()
    for i in range(10):
        queue.put(i)
    t1 = threading.Thread(target=worker1, args=(queue, ))

    t1.start()
    logging.debug('tasks are not done')

    # queue で10回 task_doneしないと、終了できないようにする。
    queue.join()
    logging.debug('tasks are one')
    queue.put(None)

    t1.join()




