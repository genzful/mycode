class htmlform:
    HTML = """
    <!DOCTYPE html>
    <html>
    <head>
        <title>Данные клиента</title>
        <style>
            body { font-family: Arial, sans-serif; margin: 40px; }
            .section { margin-bottom: 30px; padding: 20px; border: 1px solid #ddd; border-radius: 5px; }
            .section h2 { color: #333; border-bottom: 1px solid #eee; padding-bottom: 10px; }
            pre { background: #f5f5f5; padding: 15px; border-radius: 5px; overflow-x: auto; }
            .key { color: #d14; font-weight: bold; }
            .value { color: #333; }
        </style>
    </head>
    <body>
        <h1>Данные полученные от клиента</h1>
        
        <div class="section">
            <h2>Основная информация</h2>
            <p><span class="key">Время запроса:</span> <span class="value">{{ timestamp }}</span></p>
            <p><span class="key">URL:</span> <span class="value">{{ request_data.url }}</span></p>
            <p><span class="key">Метод:</span> <span class="value">{{ request_data.method }}</span></p>
            <p><span class="key">Порт:</span> <span class="value">{{ request_data.environ.SERVER_PORT }}</span></p>
        </div>

        <div class="section">
            <h2>Информация о клиенте</h2>
            <p><span class="key">IP-адрес:</span> <span class="value">{{ request_data.remote_addr }}</span></p>
            <p><span class="key">Хост:</span> <span class="value">{{ request_data.host }}</span></p>
            <p><span class="key">User Agent:</span> <span class="value">{{ request_data.user_agent }}</span></p>
            <p><span class="key">Real IP (X-Forwarded-For):</span> <span class="value">{{ real_ip }}</span></p>
        </div>

        <div class="section">
            <h2>Заголовки HTTP</h2>
            <pre>{{ headers_json }}</pre>
        </div>

        <div class="section">
            <h2>Параметры URL (Query String)</h2>
            {% if request_data.args %}
            <pre>{{ args_json }}</pre>
            {% else %}
            <p>Нет параметров</p>
            {% endif %}
        </div>

        <div class="section">
            <h2>Cookies</h2>
            {% if request_data.cookies %}
            <pre>{{ cookies_json }}</pre>
            {% else %}
            <p>Нет cookies</p>
            {% endif %}
        </div>

        <div class="section">
            <h2>Данные формы (Form Data)</h2>
            {% if form_data %}
            <pre>{{ form_json }}</pre>
            {% else %}
            <p>Нет данных формы</p>
            {% endif %}
        </div>

        <div class="section">
            <h2>JSON данные</h2>
            {% if json_data %}
            <pre>{{ json_data }}</pre>
            {% else %}
            <p>Нет JSON данных</p>
            {% endif %}
        </div>

        <div class="section">
            <h2>Файлы</h2>
            {% if files %}
            <pre>{{ files_json }}</pre>
            {% else %}
            <p>Нет файлов</p>
            {% endif %}
        </div>

        <div class="section">
            <h2>WSGI окружение</h2>
            <details>
                <summary>Показать/скрыть полное окружение ({{ environ_keys|length }} переменных)</summary>
                <pre>{{ environ_json }}</pre>
            </details>
        </div>

        <div class="section">
            <h2>Тестирование отправки данных</h2>
            <form method="post" enctype="multipart/form-data">
                <div>
                    <label>Текстовое поле:</label>
                    <input type="text" name="test_field" placeholder="Введите текст">
                </div>
                <div>
                    <label>Файл:</label>
                    <input type="file" name="test_file">
                </div>
                <div>
                    <button type="submit">Отправить данные</button>
                </div>
            </form>
        </div>
    </body>
    </html>
    """