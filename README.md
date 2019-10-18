Скачать git и установить:
https://git-scm.com/download/win
Открыть консоль git-bash и настроить имя пользователя и почту:
https://git-scm.com/book/ru/v1/%D0%92%D0%B2%D0%B5%D0%B4%D0%B5%D0%BD%D0%B8%D0%B5-%D0%9F%D0%B5%D1%80%D0%B2%D0%BE%D0%BD%D0%B0%D1%87%D0%B0%D0%BB%D1%8C%D0%BD%D0%B0%D1%8F-%D0%BD%D0%B0%D1%81%D1%82%D1%80%D0%BE%D0%B9%D0%BA%D0%B0-Git
Настроить ssh на машинке:
https://help.github.com/en/articles/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent

в консоли git-bash создать рабочую папку

Склонировать проект в рабочую папку:
git clone git@github.com:sevastopolTeam/server.git

скачать и установить cmake:
https://cmake.org/download/

в папке с проектом:
1) cmake .
2) cmake --build .

бинарник будет находиться в Debug/server.exe (windows) ./server (unix)
