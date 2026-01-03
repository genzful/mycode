import json
from datetime import datetime

from flask import Flask, render_template_string, request

from form import htmlform

app = Flask(__name__)

HTML_TEMPLATE = htmlform.HTML


def logs(whichtype, message, ip):
    log = f"""
type: {whichtype},
message: {message},
when: {datetime.now()},
who: {ip}
"""

    with open("app.log", "a", encoding="utf-8") as f:
        f.write(log)


@app.route("/", methods=["GET", "POST"])
def show_client_data():
    # Собираем все данные
    request_data = request

    # Получаем реальный IP за прокси
    real_ip = request.environ.get("HTTP_X_FORWARDED_FOR", request.remote_addr)
    logs("info", "Клиент зашел на сервер...", real_ip)

    # Подготавливаем данные для отображения
    headers_dict = dict(request.headers)

    # Данные формы
    form_data = {}
    if request.form:
        form_data = dict(request.form)

    # JSON данные
    json_data = None
    if request.is_json:
        try:
            json_data = request.get_json()
        except:
            json_data = {"error": "Невалидный JSON"}

    # Информация о файлах
    files_info = {}
    if request.files:
        for filename, file in request.files.items():
            files_info[filename] = {
                "filename": file.filename,
                "content_type": file.content_type,
                "content_length": len(file.read()) if file else 0,
            }
            file.seek(0)  # Возвращаем указатель файла

    # Ограниченное WSGI окружение (исключаем бинарные данные и длинные строки)
    safe_environ = {}
    for key, value in request.environ.items():
        try:
            # Пробуем преобразовать в строку, исключаем бинарные данные
            str_value = str(value)
            if len(str_value) < 1000:  # Ограничиваем длинные значения
                safe_environ[key] = str_value
            else:
                safe_environ[key] = f"<Длинное значение: {len(str_value)} символов>"
        except:
            safe_environ[key] = "<Невозможно отобразить>"

    return render_template_string(
        HTML_TEMPLATE,
        timestamp=datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
        request_data=request_data,
        real_ip=real_ip,
        headers_json=json.dumps(headers_dict, indent=2, ensure_ascii=False),
        args_json=json.dumps(dict(request.args), indent=2, ensure_ascii=False),
        cookies_json=json.dumps(dict(request.cookies), indent=2, ensure_ascii=False),
        form_json=json.dumps(form_data, indent=2, ensure_ascii=False),
        json_data=(
            json.dumps(json_data, indent=2, ensure_ascii=False) if json_data else None
        ),
        form_data=form_data,
        files=request.files,
        files_json=(
            json.dumps(files_info, indent=2, ensure_ascii=False) if files_info else None
        ),
        json_data_raw=json_data,
        environ_json=json.dumps(safe_environ, indent=2, ensure_ascii=False),
        environ_keys=list(safe_environ.keys()),
    )


@app.route("/json", methods=["POST"])
def receive_json():
    """Отдельный endpoint для тестирования JSON"""
    return {
        "status": "received",
        "data": request.get_json() if request.is_json else None,
        "headers": dict(request.headers),
    }


if __name__ == "__main__":
    app.run(debug=True, host="0.0.0.0", port=5000)
