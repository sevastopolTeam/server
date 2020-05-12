import random
import string

from faker import Faker

faker = Faker("ru_RU")

class Fake:

    @classmethod
    def string(self, length):
       letters = string.ascii_lowercase
       return ''.join(random.choice(letters) for i in range(length))

    @classmethod
    def email(self):
        return faker.email()

    @classmethod
    def name(self):
        return faker.name()

    @classmethod
    def password(self):
        return faker.password()

    @classmethod
    def phone(self):
        result = "+7"
        for i in range(10):
            result += str(random.randint(0, 9))

        return result

    @classmethod
    def user(self):
        password = self.string(8)
        return {
            "Email": self.email(),
            "Name": faker.name(),
            "Phone": self.phone(),
            "Password": password,
            "RepeatPassword": password
        }

    @classmethod
    def translation(self):
        return {
            "ValueFrom": Fake.string(5),
            "ValueTo": Fake.string(5),
            "LanguageFrom": "russian",
            "LanguageTo": "english",
            "PartOfSpeech": Fake.string(5),
            "OriginUrl": "origin_url",
            "DownloadUrl": "download_url",
            "Frequency": random.randint(0, 1000000),
            "IsChecked": False
        }

    @classmethod
    def word_category(self):
        return {
            "Name": Fake.string(5)
        }
