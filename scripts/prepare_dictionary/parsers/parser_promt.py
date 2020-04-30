import numpy
import time
import json
import sys
import os
import requests

import argparse

import sys
sys.stdout.encoding

sys.path.append(os.path.join(sys.path[0], '../../helpers'))

from html_helper import HtmlHelper
from io_helper import IOHelper

DICTIONARY_PAGE = "https://www.translate.ru/dictionary/en-ru/"
SAMPLES_PAGE = "https://www.translate.ru/samples/en-ru/"
GRAMMAR_PAGE = "https://www.translate.ru/grammar/en-ru/"

headers = {
    'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10.9; rv:45.0) Gecko/20100101 Firefox/45.0'
}

class ParserPromt:

    def __init__(self, path_to_files):
        self.path_to_files = path_to_files
        self.not_found_words = []
        self.main_words = []
        self.extra_words = []
        self.main_to_extra = {}
        self.word_frequency = {}

    def get_tree(self, url):
        return HtmlHelper.get_tree(self.path_to_files + "cache/", url, headers)

    def get_samples(self, word):
        url = SAMPLES_PAGE + word
        tree = self.get_tree(url)
        links = tree.xpath('//div[contains(@id, "vc_fltrSampTranslation")]//a[contains(@class, "search-translation-box")]')

        max_count = 0
        for link in links[1:6]:
            frequency =  int(link.xpath('span/text()')[0]) if len(link.xpath('span/text()')) > 0 else 0
            if frequency > max_count // 10 and (max_count == 0 or frequency > 10):
                max_count = max(max_count, frequency)
                self.word_frequency[(word, link.text)] = frequency

    def get_grammar(self, word):
        url = GRAMMAR_PAGE + word
        tree = self.get_tree(url)
        return tree

    def get_dictionary(self, word):
        tree = self.get_tree(DICTIONARY_PAGE + word)

        fromTxt = tree.xpath('//div[@class="fromTxt"]/text()')
        if len(fromTxt) > 0:
            sourceTxt = tree.xpath('//div[@class="sourceTxt"]/text()')
            main_word = tree.xpath('//div[@class="cforms_result"]//span[@class="source_only"]/text()')[0]
            if main_word not in self.main_to_extra:
                self.main_to_extra[main_word] = []
            
            self.main_to_extra[main_word].append([ word, sourceTxt[0] ])
            self.extra_words.append([word, sourceTxt[0]])
        else:
            forms = tree.xpath('//div[@class="cforms_result"]')
            current = { "eng": word, "parts": [] }
            for form in forms:
                current_word = form.xpath('div//span[@class="source_only"]/text()')[0]
                if current_word.lower() != word:
                    continue

                part = form.xpath('div/span[@class="ref_psp"]/text()')
                translates = form.xpath('div//span[@class="ref_result"]/text()')
                current["parts"].append({"part": part, "translates": translates})

            if len(current["parts"]) == 0:
                self.not_found_words.append(word)
            else:
                self.main_words.append(current)

    def get_info(self, word):
        # if (word != "night"):
        #     return
        grammar = self.get_grammar(word)
        self.get_samples(word)
        self.get_dictionary(word)

        # dictionary["frequency"] = self.get_samples(word)

        # if len(dictionary["parts"]) == 0:
        #     print(word + " isn't found")
        #     return None

        # return dictionary

    def parse(self, words):
        results = []
        word_num = 0
        for word in words:
            try:
                word_num += 1
                if word_num % 100 == 0:
                    print(str(word_num) + " records completed")

                # word_info = 
                self.get_info(word)
                # if word_info != None:
                #     results.append(word_info)
            except Exception as e:
                print(e)
                continue

        # for k in self.main_to_extra:
        #     print('----------')
        #     print(k)
        #     for i in self.main_to_extra[k]:
        #         print(i)

        # print("Not Found")
        # for nf in self.not_found_words:
        #     print(nf)

        # self.tmp = sorted(self.tmp)
        # for t in self.tmp:
        #     if t[1] in self.main_to_extra:
        #         print(t[1] + " -> " + t[2] + " -> " + str(t[0]))

        # print("-----------")
        # print("Extra")
        # for ex in self.extra_words:
        #     print(ex[0] + " -> " + ex[1])


        # IOHelper.print_json_to_file(self.main_words, "tmp.json")

        # print(json.dumps(self.main_words))
        # with open('tmp.txt', "w", encoding="utf-8") as file:
        #     json.dump(self.main_words, file, ensure_ascii=False)



        # print("MAIN WORDS")
        # IOHelper.print_json(self.main_words)
        # print("_______________")
        # print("\n\n\n")


        # IOHelper.print_json(self.main_words)
        for mn in self.main_words:
            for part in mn["parts"]:
                if len(part["part"]) == 0:
                    part["part"].append("")
                for tr in part["translates"]:
                    if (mn["eng"], tr) in self.word_frequency:
                        print(mn["eng"] + " -> " + tr + " -> " + part["part"][0] + " -> " + str(self.word_frequency[(mn["eng"], tr)]))
                    # else:
                    #     print(mn["eng"] + " -> " + tr + " -> NOT")

        # print("WORDS FREQUENCY")
        # IOHelper.print_json(self.word_frequency)
        # print("_______________")
        # print("\n\n\n")
        # return self.main_words


        up = []        
        for mn in self.main_words:
            for part in mn["parts"]:
                if len(part["part"]) == 0:
                    part["part"].append("")
                for tr in part["translates"]:
                    if (mn["eng"], tr) in self.word_frequency:
                        # print(mn["eng"] + " -> " + tr + " -> " + part["part"][0] + " -> " + str(self.word_frequency[(mn["eng"], tr)]))
                        up.append({
                            "ValueFrom": tr,
                            "ValueTo": mn["eng"],
                            "LanguageFrom": "russian",
                            "LanguageTo": "english",
                            "PartOfSpeech": part["part"][0],
                            "Frequency": str(self.word_frequency[(mn["eng"], tr)])
                        })

        return up

def main():
    parser = argparse.ArgumentParser(description="Configures")
    parser.add_argument('--path_to_files', dest="path_to_files", required=True)
    args = parser.parse_args()
    if args.path_to_files[-1] != '/':
        args.path_to_files += '/'

    parser = ParserPromt(args.path_to_files)

    words = open(args.path_to_files + "all_words.txt", "r").read().strip().split('\n')
    translations = parser.parse(words)

    token = "12215108c4c63c392826561db6abbe301587856945"
    for translation in translations:
        r = requests.post("http://localhost:1234/api/english/admin/translations", data=json.dumps(translation), headers={"Authorization": token})
        print(r.json())

main()