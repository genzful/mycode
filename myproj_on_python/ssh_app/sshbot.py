import os
import random as rand
import re
import sqlite3
import subprocess
import threading
import time
import webbrowser
import requests
import telebot
from telebot import types

bot = telebot.TeleBot("8348562388:AAG6Fpp7AKpZO4bPRtvUikbkatF962KXTNk")
state = 0
passwd = "genzfAnder725"
API = "692689c2793ce2e0a52d1bf56a90e4c8"


def init_db():
    conn = sqlite3.connect("users.db")
    cur = conn.cursor()
    cur.execute(
        "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, username TEXT, userid TEXT UNIQUE)"
    )
    conn.commit()
    conn.close()


def clean_text(text):
    if text is None:
        return ""
    cleaned = re.sub(r"[^\w\s@\.\-_]", "", text, flags=re.UNICODE)
    return cleaned.strip()


def kill_apps_async():
    """Функция для завершения приложений в фоне"""
    try:
        subprocess.run(["pkill", "-f", "Telegram"], check=False)
        subprocess.run(["pkill", "-f", "zen-browser"], check=False)
        subprocess.run(["pkill", "-f", "discord"], check=False)
    except Exception as e:
        print(f"Ошибка при завершении приложений: {e}")


@bot.message_handler(commands=["start"])
def start(message):
    user_id = str(message.from_user.id)

    main_markup = types.ReplyKeyboardMarkup(resize_keyboard=True)

    if user_id == "5042882483":
        admin_markup = types.ReplyKeyboardMarkup(resize_keyboard=True)
        btn = types.KeyboardButton(passwd)
        admin_markup.row(btn)

        bot.send_message(
            message.chat.id,
            f"🔐 Пароль от рута (нажми кнопку):",
            reply_markup=admin_markup,
        )
    else:
        bot.send_message(message.chat.id, "пароль от рута 🤗", reply_markup=main_markup)

    bot.register_next_step_handler(message, checkpass)

    try:
        conn = sqlite3.connect("users.db")
        cur = conn.cursor()
        name = clean_text(str(message.from_user.first_name))
        username = clean_text(str(message.from_user.username))
        userid = clean_text(str(message.from_user.id))

        cur.execute("SELECT * FROM users WHERE userid = ?", (userid,))
        db = cur.fetchall()

        if not db:
            cur.execute(
                "INSERT INTO users (name, username, userid) VALUES (?, ?, ?)",
                (name, username, userid),
            )
            conn.commit()
            print(f"✅ Добавлен пользователь: {userid}")
            bot.send_message(5042882483, "Добавился новый человек!!!")
            bot.send_message(
                5042882483,
                f"<code>name = {name}\nusername = {username}</code>",
                parse_mode="HTML",
            )
        else:
            if userid != 5042882483:
                bot.send_message(
                    5042882483, f"✅ Пользователь уже существует: {userid}"
                )

    except Exception as e:
        print(f"❌ Ошибка базы данных: {e}")
    finally:
        conn.close()


@bot.message_handler(commands=["getdb"])
def callback(message):
    try:
        conn = sqlite3.connect("users.db")
        cur = conn.cursor()
        cur.execute("SELECT * FROM users")
        db = cur.fetchall()
        users = "\n".join(
            [
                f"ID: {row[0]}, Name: {row[1]}, Username: {row[2]}, UserID: {row[3]}"
                for row in db
            ]
        )
        bot.send_message(5042882483, f"Пользователи в базе:\n{users}")
    except Exception as e:
        bot.send_message(5042882483, f"❌ Ошибка при получении данных: {e}")
    finally:
        conn.close()


def checkpass(message):
    global passwd
    markup = types.ReplyKeyboardMarkup(resize_keyboard=True)
    btn1 = types.KeyboardButton("Достать файл")
    btn2 = types.KeyboardButton("Консоль")
    btn3 = types.KeyboardButton("Погода")
    btn4 = types.KeyboardButton("Переводчик")
    markup.row(btn1, btn2)
    markup.row(btn3, btn4)

    if message.text == passwd:
        bot.send_message(message.chat.id, "all is good)", reply_markup=markup)
        bot.register_next_step_handler(message, on_click)
    else:
        bot.send_message(message.chat.id, "wrong\ntype /start again...")


def on_click(message):
    global state
    if message.text == "Консоль":
        state = 1
        bot.send_message(message.chat.id, "arch@arch ~>  ")
        bot.register_next_step_handler(message, console)
    elif message.text == "Достать файл":
        state = 2
        bot.send_message(message.chat.id, "Название файла")
        bot.register_next_step_handler(message, filefrompc)
    elif message.text == "Погода":
        state = 3
        bot.send_message(message.chat.id, "Город:")
        bot.register_next_step_handler(message, getweather)
    elif message.text == "Переводчик":
        bot.register_next_step_handler()
    else:
        bot.send_message(message.chat.id, "error!\ntype /start")


def filefrompc(message):
    global state
    if state == 2:
        found = False
        for root, dirs, files in os.walk("/home/arch"):
            if message.text in files:
                path = os.path.join(root, message.text)
                found = True

                if message.text.endswith((".txt", ".py", ".cpp", ".md")):
                    try:
                        with open(path, "r", encoding="utf-8") as f:
                            content = f.read()
                        if len(content) > 4000:
                            content = content[:4000] + "\n... (файл обрезан)"
                        bot.send_message(
                            message.chat.id,
                            f"```\n{content}\n```",
                            parse_mode="Markdown",
                        )
                    except Exception as e:
                        bot.send_message(message.chat.id, f"❌ Ошибка чтения: {e}")

                elif message.text.lower().endswith(
                    (".png", ".jpg", ".jpeg", "JPEG", "JPG", "PNG")
                ):
                    try:
                        with open(path, "rb") as photo:
                            bot.send_photo(message.chat.id, photo)
                    except Exception as e:
                        bot.send_message(
                            message.chat.id, f"❌ Ошибка отправки фото: {e}"
                        )
                break

        if not found:
            bot.send_message(message.chat.id, "❌ Файл не найден")


@bot.message_handler(func=lambda message: True)
def console(message):
    global state
    if state == 1:
        command = message.text.split()
        if not command:
            return

        if command[0] == "комп" or command[0] == "пк":
            threading.Thread(target=kill_apps_async).start()
            bot.send_message(message.chat.id, "Приложения завершаются...")
            subprocess.run(["poweroff"])

        elif command[0] == "дс":
            try:
                subprocess.Popen(["discord"])
                bot.send_message(message.chat.id, "Discord запускается...")
            except Exception as e:
                bot.send_message(message.chat.id, f"❌ Ошибка: {e}")

        elif command[0] == "тг":
            try:
                subprocess.Popen(["Telegram"])
                bot.send_message(message.chat.id, "Telegram запускается...")
            except Exception as e:
                bot.send_message(message.chat.id, f"❌ Ошибка: {e}")

        elif command[0] == "музыка" or command[0] == "музло":
            bot.send_message(message.chat.id, "Музло включено!")
            webbrowser.open("https://music.youtube.com/watch?v=2mXNRsyTitA&list=LM")

        elif command[0] == "cd":
            try:
                if len(command) > 1:
                    os.chdir(command[1])
                    bot.send_message(message.chat.id, f"Перешел в: {os.getcwd()}")
                else:
                    bot.send_message(message.chat.id, "❌ Укажите путь: cd /path")
            except Exception as e:
                bot.send_message(message.chat.id, f"❌ Ошибка: {e}")

        else:
            try:
                result = subprocess.run(
                    message.text, capture_output=True, text=True, shell=True, timeout=30
                )

                if result.returncode == 0:
                    output = result.stdout
                    if len(output) > 4000:
                        output = output[:4000] + "\n... (output truncated)"
                    bot.send_message(
                        message.chat.id,
                        f"```Output: arch@arch {os.getcwd()} >\n{output}```",
                        parse_mode="Markdown",
                    )
                else:
                    bot.send_message(message.chat.id, f"❌ Ошибка: {result.stderr}")

            except subprocess.TimeoutExpired:
                bot.send_message(message.chat.id, "❌ Таймаут выполнения команды")
            except Exception as e:
                bot.send_message(message.chat.id, f"❌ Ошибка")
    else:
        bot.send_message(message.chat.id, "пока нет доступа.")


def kel_to_cel(temp):
    return round(temp - 273)


@bot.message_handler(commands=["start"])
def func(message):
    bot.send_message(message.chat.id, "Город:")
    bot.register_next_step_handler(message, getweather)


def getweather(message):
    global API
    city = message.text

    def getans():
        global API
        response = requests.get(
            f"https://api.openweathermap.org/data/2.5/weather?q={city}&appid={API}"
        )
        return response

    resp = getans()
    if resp.ok:
        weather_translation = {
            "Clear": "Ясно",
            "Clouds": "Облачно",
            "Rain": "Дождь",
            "Drizzle": "Морось",
            "Thunderstorm": "Гроза",
            "Snow": "Снег",
            "Mist": "Дымка",
            "Smoke": "Дым",
            "Haze": "Мгла",
            "Dust": "Пыль",
            "Fog": "Туман",
            "Sand": "Песок",
            "Ash": "Пепел",
            "Squall": "Шквал",
            "Tornado": "Торнадо",
        }
        coord = [resp.json()["coord"]["lon"], resp.json()["coord"]["lat"]]
        temp = resp.json()["main"]["temp"]
        stateofweather = weather_translation[resp.json()["weather"][0]["main"]]
        speed = round(resp.json()["wind"]["speed"], 2)
        bot.send_message(
            message.chat.id,
            f"```Информация:\nКоординаты:\n\tДолгота: {coord[0]}\n\tШирота: {coord[1]}\nТемпература:\n\t{kel_to_cel(temp)}Градусов цельсия\nВетер:\n\t{speed}метров в секунду```",
            parse_mode="MarkdownV2",
        )


if __name__ == "__main__":
    print("Бот запущен")
    bot.infinity_polling()
    init_db()