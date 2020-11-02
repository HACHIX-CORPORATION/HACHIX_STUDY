import logging
import multiprocessing
import time

logging.basicConfig(
    level=logging.DEBUG, format="%(processName)s: %(message)s")

# プロセス間は共有メモリが無い
# join: プロセス、スレッドの終了待ち


def f(conn):
    conn.send(['test'])
    conn.close()


if __name__ == "__main__":
    parent_conn, child_conn = multiprocessing.Pipe()
    p = multiprocessing.Process(target=f, args=(parent_conn, ))
    p.start()
    logging.debug(child_conn.recv())


