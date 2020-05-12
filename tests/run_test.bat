echo >/dev/null # >nul & GOTO WINDOWS & rem ^
echo 'Processing for Linux'

mkdir logs
./server config/priemka.json &
mongo mongodb://localhost:1235/priemka tests/prepare_db_to_tests.js
sleep 3
python -m pytest -s tests/
kill %1

exit 0

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

:WINDOWS
echo "Processing for Windows"

mkdir logs
start /B Debug\server.exe config\priemka.json
mongo mongodb://localhost:1235/priemka tests/prepare_db_to_tests.js
sleep 5
python -m pytest -s tests\
taskkill /PID server.exe /f
