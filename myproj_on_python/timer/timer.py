import sqlite3
import subprocess
import sys
import threading
import time
from datetime import datetime


class Timer:
    autonotify = False
    autonotify_thread = None
    stop_flag = threading.Event()

    def __init__(self):
        self.active = True

    @staticmethod
    def log(e):
        with open("logs.txt", "a") as f:
            f.write(f"\ntime: {datetime.now()}\nlog: {e}\n")

    @staticmethod
    def stderr(e):
        with open("stderr.txt", "a") as f:
            f.write(f"\ntime: {datetime.now()}\nerror: {e}\n")

    @staticmethod
    def info():
        print(
            """
    Hi, this is a timer from genz
        After calling the binary, specify the time for which you need to set the timer
        Use the --autonotify flag to turn on/off hourly notification sending
        """
        )

    @staticmethod
    def hourly_print():
        while not Timer.stop_flag.is_set():
            now = datetime.now()
            if now.minute == 0 and now.second == 0:
                subprocess.Popen(["notify-send", "work bro work..."])
                time.sleep(1)
            time.sleep(0.9)

    def start_autonotify(self):
        if Timer.autonotify and Timer.autonotify_thread is None:
            Timer.stop_flag.clear()
            Timer.autonotify_thread = threading.Thread(
                target=Timer.hourly_print, daemon=True
            )
            Timer.autonotify_thread.start()
            self.log("auto-notify is on")

    def stop_autonotify(self):
        if not Timer.autonotify and Timer.autonotify_thread is not None:
            Timer.stop_flag.set()
            Timer.autonotify_thread.join(timeout=2)
            Timer.autonotify_thread = None
            self.log("auto-notify is off")

    def process(self):
        while self.active:
            current_time = datetime.now().time().replace(microsecond=0)

            with sqlite3.connect("timer.db") as conn:
                cur = conn.cursor()
                cur.execute("SELECT * FROM timer")
                db = cur.fetchall()

                for arg in db:
                    time_str = arg[0]
                    try:
                        target_time = datetime.strptime(time_str, "%H:%M:%S").time()

                        if current_time == target_time:
                            subprocess.Popen(["notify-send", "there is an alarm"])
                            cur.execute("DELETE FROM timer WHERE time = ?", (time_str,))
                            conn.commit()
                            self.log(f"{time_str} completed and was terminated automatically.")
                            break
                    except Exception as e:
                        self.stderr(f"error of processing this time {time_str}: {e}")

            if Timer.autonotify:
                self.start_autonotify()
            else:
                self.stop_autonotify()

            time.sleep(0.9)


def init_db():
    subprocess.Popen(["notify-send", "timer was started..."])
    conn = sqlite3.connect("timer.db")
    cur = conn.cursor()
    cur.execute("CREATE TABLE IF NOT EXISTS timer (time TEXT)")
    conn.commit()
    conn.close()


def main(user_input):
    if user_input == "--help":
        Timer.info()
        return

    timer = Timer()

    if user_input and user_input != "--autonotify":
        with sqlite3.connect("timer.db") as conn:
            cur = conn.cursor()
            cur.execute("INSERT INTO timer (time) VALUES (?)", (user_input,))
            conn.commit()
            cur.execute("SELECT * FROM timer")
            db = cur.fetchall()
            timer.log(f"added time: {user_input}. Все таймеры: {db}")
            return
    elif user_input == "--autonotify":
        Timer.autonotify = not Timer.autonotify
        status = "is on" if Timer.autonotify else "is off"
        timer.log(f"auto-notify {status}")
        return

    timer.process()


if __name__ == "__main__":
    init_db()
    try:
        main(sys.argv[1] if len(sys.argv) > 1 else "")
    except KeyboardInterrupt:
        Timer.stderr("timer was stoped")
    except Exception as e:
        Timer.stderr(f"error: {e}")

