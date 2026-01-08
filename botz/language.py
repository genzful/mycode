import telebot; # tg api
import requests; # for yandex api
import random as rand; # for random alhorytm
import sqlite3; # for sqlite db
import re # for format of string

bot = telebot.TeleBot("your token"); # your token of bot from fatherbot
state = 0; # state of chat
test_word = "";

# init func for db sqlite
def init():
    conn = sqlite3.connect('users.db');
    cur = conn.cursor();
    cur.execute('CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, username TEXT)');
    conn.commit();
    conn.close();

# parsing of text
def clean_text(text):
    if text is None:
        return "";
    cleaned = re.sub(r'[^\w\s@\.\-_]', '', text, flags=re.UNICODE);
    return cleaned.strip();

# handler of /start
@bot.message_handler(commands=['start'])
def start(message):
    global word;
    conn = sqlite3.connect('users.db');
    cur = conn.cursor();
    bot.send_message(message.chat.id, f"Hi {message.from_user.first_name}! This bot can translate your words into different languages using Yandex API requests.\nType '{test_word}' to verify that you're not a bot)");
    name = clean_text(str(message.from_user.first_name));
    username = clean_text(str(message.from_user.username));
    cur.execute("INSERT INTO users (name, username) VALUES (?, ?)", (name, username));
    conn.commit();
    conn.close();

# handler of /getdb ( shhhh) )
@bot.message_handler(commands=['getdb'])
def callback(message):
    conn = sqlite3.connect('users.db');
    cur = conn.cursor();
    cur.execute('SELECT * FROM users');
    db = cur.fetchall();
    users = str(db);
    bot.send_message(message.chat.id, users);
    conn.close();

# handler of any text
@bot.message_handler(content_types=['text'])
def handle_message(message):
    # func for free api to yandex
    API_KEY = "";
    def get_langs():
        global API_KEY;
        BASE_URL = 'https://dictionary.yandex.net/api/v1/dicservice.json';
        bot.send_message(message.chat.id, 'loading...');
        response = requests.get(f'{BASE_URL}/getLangs', params={
            'key': API_KEY
        })
        return response;

    # func for get the responce of api
    def lookup(lang, text, ui='ru'):
        global API_KEY;
        BASE_URL = 'https://dictionary.yandex.net/api/v1/dicservice.json';
        response = requests.get(f'{BASE_URL}/lookup', params={
            'key': API_KEY,
            'lang': lang,
            'text': text,
            'ui': ui
        })
        return response;

    global state;
    global test_word;
    # test for a bot
    if message.text.lower() == test_word:
        bot.send_message(message.chat.id, 'super!');
        state += 1;
        langs_response = get_langs();
        bot.send_message(message.chat.id, f'choose the path of translation and after write a word ->\n{langs_response.json()}');
    elif state != 0 and message.text.lower()[2] == '-' or message.text.lower()[3] == '-':
        langs_response = get_langs();
        if langs_response.ok:
            word = message.text.lower().split();
            answer = lookup(word[0], word[1]);
            if len(word) == 3:
                del word[2];
            bot.send_message(message.chat.id, answer.text);
        else:
            bot.send_message(message.chat.id, 'error 4xx');
            exit(1);
    else:
        if state != 0:
            pass;
        else:
            bot.send_message(message.chat.id, 'are you a robot?');


# handler for video
@bot.message_handler(content_types=['video'])
def video(message):
    bot.reply_to(message, 'good video (for what?)');

# handler for any photo
@bot.message_handler(content_types=['photo'])
def photo(message):
    bot.reply_to(message, 'cool photo bro!');

if __name__ == '__main__':
    init(); print("users.db was created || already created");
    test_word = input("what the word u want to use to check for a bot?\n~~~~~~~~> ");
    print("\n\tbot was activated!!!");
    bot.infinity_polling();
import telebot; # tg api
import requests; # for yandex api
import random as rand; # for random alhorytm
import sqlite3; # for sqlite db
import re # for format of string

bot = telebot.TeleBot("your token"); # your token of bot from fatherbot
state = 0; # state of chat
test_word = "";

# init func for db sqlite
def init():
    conn = sqlite3.connect('users.db');
    cur = conn.cursor();
    cur.execute('CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, username TEXT)');
    conn.commit();
    conn.close();

# parsing of text
def clean_text(text):
    if text is None:
        return "";
    cleaned = re.sub(r'[^\w\s@\.\-_]', '', text, flags=re.UNICODE);
    return cleaned.strip();

# handler of /start
@bot.message_handler(commands=['start'])
def start(message):
    global word;
    conn = sqlite3.connect('users.db');
    cur = conn.cursor();
    bot.send_message(message.chat.id, f"Hi {message.from_user.first_name}! This bot can translate your words into different languages using Yandex API requests.\nType '{test_word}' to verify that you're not a bot)");
    name = clean_text(str(message.from_user.first_name));
    username = clean_text(str(message.from_user.username));
    cur.execute("INSERT INTO users (name, username) VALUES (?, ?)", (name, username));
    conn.commit();
    conn.close();

# handler of /getdb ( shhhh) )
@bot.message_handler(commands=['getdb'])
def callback(message):
    conn = sqlite3.connect('users.db');
    cur = conn.cursor();
    cur.execute('SELECT * FROM users');
    db = cur.fetchall();
    users = str(db);
    bot.send_message(message.chat.id, users);
    conn.close();

# handler of any text
@bot.message_handler(content_types=['text'])
def handle_message(message):
    # func for free api to yandex
    API_KEY = "";
    def get_langs():
        global API_KEY;
        BASE_URL = 'https://dictionary.yandex.net/api/v1/dicservice.json';
        bot.send_message(message.chat.id, 'loading...');
        response = requests.get(f'{BASE_URL}/getLangs', params={
            'key': API_KEY
        })
        return response;

    # func for get the responce of api
    def lookup(lang, text, ui='ru'):
        global API_KEY;
        BASE_URL = 'https://dictionary.yandex.net/api/v1/dicservice.json';
        response = requests.get(f'{BASE_URL}/lookup', params={
            'key': API_KEY,
            'lang': lang,
            'text': text,
            'ui': ui
        })
        return response;

    global state;
    global test_word;
    # test for a bot
    if message.text.lower() == test_word:
        bot.send_message(message.chat.id, 'super!');
        state += 1;
        langs_response = get_langs();
        bot.send_message(message.chat.id, f'choose the path of translation and after write a word ->\n{langs_response.json()}');
    elif state != 0 and message.text.lower()[2] == '-' or message.text.lower()[3] == '-':
        langs_response = get_langs();
        if langs_response.ok:
            word = message.text.lower().split();
            answer = lookup(word[0], word[1]);
            if len(word) == 3:
                del word[2];
            bot.send_message(message.chat.id, answer.text);
        else:
            bot.send_message(message.chat.id, 'error 4xx');
            exit(1);
    else:
        if state != 0:
            pass;
        else:
            bot.send_message(message.chat.id, 'are you a robot?');


# handler for video
@bot.message_handler(content_types=['video'])
def video(message):
    bot.reply_to(message, 'good video (for what?)');

# handler for any photo
@bot.message_handler(content_types=['photo'])
def photo(message):
    bot.reply_to(message, 'cool photo bro!');

if __name__ == '__main__':
    init(); print("users.db was created || already created");
    test_word = input("what the word u want to use to check for a bot?\n~~~~~~~~> ");
    print("\n\tbot was activated!!!");
    bot.infinity_polling();
