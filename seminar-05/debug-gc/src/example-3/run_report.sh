# собираем как обычно и запускаем с perf record и потом смотрим результаты
gcc main.cpp -o main.exe
sudo -S perf record ./main.exe 2>&1 > perf.log
sudo -S chmod 0666 perf.data
perf report | cat