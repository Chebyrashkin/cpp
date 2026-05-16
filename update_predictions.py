import os
import json
import requests

# === НАСТРОЙКИ ===
LABEL_STUDIO_URL = "http://172.31.246.82:4041"
API_TOKEN = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ0b2tlbl90eXBlIjoicmVmcmVzaCIsImV4cCI6ODA4NTI0NjE2NCwiaWF0IjoxNzc4MDQ2MTY0LCJqdGkiOiJjN2QzZTMwZGRkMjY0ZTI2YTIwNjRhMTExNGQyMDlmNiIsInVzZXJfaWQiOiIxMjEifQ.syrmxd91HViWzup9kF0F-6WPYypYrr3arHtvBm3lLTU"   # вставьте токен
PROJECT_ID = 1                 # ваш ID проекта

# Папки с данными
TEXT_DIR = "./texts"
PRELABEL_DIR = "./prelabels"

HEADERS = {
    "Authorization": f"Token {API_TOKEN}",
    "Content-Type": "application/json"
}

def get_task_by_text(text):
    """Находит ID задачи, у которой data.text точно совпадает с данным текстом"""
    url = f"{LABEL_STUDIO_URL}/api/tasks?project={PROJECT_ID}"
    resp = requests.get(url, headers=HEADERS)
    resp.raise_for_status()
    tasks = resp.json()
    for task in tasks:
        if task.get("data", {}).get("text") == text:
            return task["id"]
    return None

def update_predictions(task_id, predictions):
    """Заменить predictions для задачи (удалить старые, добавить новые)"""
    # 1. Удалить существующие prediction
    url_preds = f"{LABEL_STUDIO_URL}/api/predictions?task={task_id}"
    resp = requests.get(url_preds, headers=HEADERS)
    if resp.status_code == 200:
        for pred in resp.json():
            del_url = f"{LABEL_STUDIO_URL}/api/predictions/{pred['id']}"
            requests.delete(del_url, headers=HEADERS)
    # 2. Добавить новое prediction
    payload = {
        "task": task_id,
        "model_version": "auto_label_english",
        "result": predictions
    }
    resp = requests.post(f"{LABEL_STUDIO_URL}/api/predictions", headers=HEADERS, json=payload)
    return resp.status_code in (200, 201)

# === ОСНОВНОЙ ЦИКЛ ===
for pre_file in os.listdir(PRELABEL_DIR):
    if not pre_file.endswith(".prelabel.json"):
        continue
    base = pre_file.replace(".prelabel.json", "")
    text_path = os.path.join(TEXT_DIR, base + ".txt")
    if not os.path.exists(text_path):
        print(f"Не найден текст для {pre_file}, пропускаем")
        continue

    # Читаем текст и предразметку
    with open(text_path, "r", encoding="utf-8") as f:
        text = f.read()
    with open(os.path.join(PRELABEL_DIR, pre_file), "r", encoding="utf-8") as f:
        pre_ann = json.load(f)

    # Находим задачу по тексту
    task_id = get_task_by_text(text)
    if task_id is None:
        print(f"Задача с таким текстом не найдена: {base}. Создаём новую? (пропускаем)")
        continue

    print(f"Обновляем задачу {task_id} ({base})...")
    success = update_predictions(task_id, pre_ann)
    if success:
        print(f"  -> Предразметка добавлена для задачи {task_id}")
    else:
        print(f"  -> Ошибка при обновлении задачи {task_id}")