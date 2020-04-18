import requests
import hashlib
from lxml import html
from lxml import etree

class HtmlHelper:  
    
    @classmethod
    def get_tree(self, path_to_cache, url, headers = {}):
        hash = hashlib.md5(url.encode('utf-8')).hexdigest()
        try:
            if path_to_cache[-1] != '/':
                path_to_cache += '/'
            text = open(path_to_cache + hash).read()
        except Exception as e:
            text = requests.get(url, headers = headers).text
            with open("cache/" + hash, 'w') as outfile:
                outfile.write(text)
        return html.fromstring(text)

    @classmethod
    def get_tree_no_cache(self, url, headers = {}):
        text = requests.get(url, headers = headers).text
        return html.fromstring(text)
