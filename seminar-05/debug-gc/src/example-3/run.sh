# собираем как обычно и запускаем с perf stat
gcc main.cpp -o main.exe
sudo -S perf stat ./main.exe