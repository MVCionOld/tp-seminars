# Кросскомпиляция

Процесс сборки программ, предназначенных для другой процессорной архитектуры или операционной системы называется 
__кросс-компиляцией__.

Для этого необходимо специальная версия компилятора ```gcc```, предназначенного для другой платформы. Во многих 
дистрибутивах существуют отдельные пакеты компилятора для других платформ, включая ARM.  

__Toolchain__ - набор утилит, которая умеет компилировать устройство под другие платформы.  

Выполнение программ, предназначенных для других архитектур, возможно только интерпретацией инородного набора команд. 
Для этого предназначены специальные программы - __эмуляторы__.



# Кросскомпиляция под ARM

### Установка toolchain

Полные названия команд ```gcc``` имеют вид _триплетов_:
```bash
ARCH-OS[-VENDOR]-gcc
ARCH-OS[-VENDOR]-g++
ARCH-OS[-VENDOR]-gdb
...
```
где:
 * ```ARCH``` - это имя архитектуры: ```i686```, ```x86_64```, ```arm```, ```ppc``` и т.д.;  
 * ```OS``` - целевая операционная система, например, ```linux```, ```win32``` или ```darwin```;  
 * необязательный фрагмент триплета ```VENDOR``` - соглашения по бинарному интерфейсу, если их для платформы существует несколько, например, для ```ARM``` это может быть ```gnueabi``` (стандартное соглашение ```Linux```) или ```none-eabi``` (без операционной системы, просто голое железо).

Для архитектуры ```ARM``` можно скачать готовую поставку "все-в-одном" из проекта Linaro: http://releases.linaro.org/components/toolchain/binaries/7.5-2019.12/arm-linux-gnueabi/

Для загрузки и установки понадобится:

```shell
# узнаем архитектуру своего компьютеру, потребуется для выбора нужной версии linaro
uname -m  # в моем случае это x86_64
# cкачать набор компиляторов и динамических библиотек из проекта linaro, [ARCH] из пункта выше
wget http://releases.linaro.org/components/toolchain/binaries/7.5-2019.12/arm-linux-gnueabi/gcc-linaro-7.5.0-2019.12-[ARCH]_arm-linux-gnueabi.tar.xz
# распаковать
tar xvf gcc-linaro-7.5.0-2019.12-[ARCH]_arm-linux-gnueabi.tar.xz
# установить qemu-arm
sudo apt-get install qemu-user-static qemu-system-arm qemu-user
```

В случае ошибки:
```shell
bash: <...>/bin/arm-linux-gnueabi-gcc: No such file or directory
```

Выполните:
```shell
sudo apt-get upgrade 
sudo apt-get install libc6:x86_64 libncurses5:x86_64 libstdc++6:x86_64
sudo dpkg --add-architecture x86_64
```

Стоит добавить путь до скачанных компиляторов в PATH, чтобы их можно было запускать по имени программы, а не по пути до нее.
```shell
export PATH=$PATH:<...>/gcc-linaro-7.5.0-2019.12-[ARCH]_arm-linux-gnueabi/bin
```

Стоит записать путь до динамических библиотек ARM в QEMU_LD_PREFIX, чтобы не писать -L опцию.
```shell
export QEMU_LD_PREFIX=<...>/gcc-linaro-7.5.0-2019.12-[ARCH]_arm-linux-gnueabi/arm-linux-gnueabi/libc
```
Или запускать как:
```shell
qemu-arm -L <...>/gcc-linaro-7.5.0-2019.12-[ARCH]_arm-linux-gnueabi/arm-linux-gnueabi/libc ./a.out
```

Если вам не хватает просто ```qemu-arm```, то читайте этот пункт до конца.

Идеальный вариант для тестирования и отладки - это использовать настоящее железо, например Raspberry Pi. Если под рукой
нет компьютера с ARM-процессором, то можно выполнять эмуляцию ПК через QEMU с установленной системой Raspbian. Скачать 
образ можно отсюда: https://www.raspberrypi.org/software/

Установка QEMU: https://www.qemu.org/download/  
Документация по QEMU: https://qemu-project.gitlab.io/qemu/  