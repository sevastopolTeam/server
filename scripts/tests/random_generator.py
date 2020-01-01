import random
import string

def random_string(length):
   letters = string.ascii_lowercase
   return ''.join(random.choice(letters) for i in range(length))

def random_email():
    return random_string(10) + "@example.com"

def random_phone():
    result = "+7"
    for i in range(10):
        result += str(random.randint(0, 9))

    return result

def random_user():
    password = random_string(8)
    return {
        "Email": random_email(),
        "Name": random_string(10),
        "Phone": random_phone(),
        "Password": password,
        "RepeatPassword": password
    }