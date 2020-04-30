import json

class IOHelper:

    @classmethod
    def print_json(self, obj):
        print(json.dumps(obj, ensure_ascii=False))

    @classmethod
    def print_json_to_file(self, obj, filename):
        with open(filename, "w", encoding="utf-8") as file:
            json.dump(obj, file, ensure_ascii=False)
