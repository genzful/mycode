import sqlite3
import sys


def main(name):
    conn = sqlite3.connect(name)
    cur = conn.cursor()
    cur.execute(f"SELECT * FROM {name[:-3]}")
    db = cur.fetchall()
    print(db)


if __name__ == "__main__":
    main(sys.argv[1])
