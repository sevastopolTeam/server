import json

class IOHelper:  
    
    @classmethod
    def print_json(self, obj):
        print(json.dumps(obj, ensure_ascii=False))
