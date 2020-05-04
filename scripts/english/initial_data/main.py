import requests
import json
import random
import sys
import os

sys.path.append(os.path.join(sys.path[0], '../'))

from data_generator import Fake
from client import Client

def main():
    print("Task is started")
    client = Client("http://localhost:1234/api/")

    users = []
    for i in range(50):
        users.append(Fake.user())

    for user in users:
        Client.register_user(user)

    for user in users:
        for i in range(random.randint(0, 2)):
            Client.login_user(user)

    translations = json.load(open("translations_for_uploading.json"))
    print(json.dumps(translations, ensure_ascii=False))

    print("Task is finished")

main()
