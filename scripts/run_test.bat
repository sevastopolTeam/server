echo >/dev/null # >nul & GOTO WINDOWS & rem ^
echo 'Processing for Linux'

./server config/priemka.json &
mongo mongodb://localhost:1235/priemka scripts/mongo_add_admin.js
sleep 3
pytest scripts/tests/test_english.py
kill %1

exit 0

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

:WINDOWS
echo "Processing for Windows"

start /B Debug\server.exe config\priemka.json
mongo mongodb://localhost:1235/priemka scripts/mongo_add_admin.js
sleep 5
pytest scripts\tests\test_english.py
taskkill /PID server.exe /f
