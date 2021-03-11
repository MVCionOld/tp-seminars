### Зачем нужны структурные паттерны?

---

# Адаптер (Adapter)

* Имя - Adapter
* Задача - совместить классы/объекты/сервисы c несовместимым интерфейсом

<details><summary>Пример</summary>
<p>

В Россию поставляют Tesla Cybertruck из США. Необходимо локализовать ПО под нужны наших потребителей.
Для всего пользовательского интерфейса производители позаботились об адаптации, кроме датчиков температуры,
они показывают в градусах Кельвина, вместо градусов Цельсия.

```c++
class TeslaFahrenheitSensor {
  public:
    float GetTemp() const;
    ...
};
```

Реализацию класса ```TeslaFahrenheitSensor``` менять нельзя, да и сама реализация нам неизвестна.  
Известно, что ПО отвечающее за UI использует класс сенсора в качестве шаблонного параметра.

```c++
template<class Sensor>
void SendTempToUi(Sensor sensor) {
    UiSingleton.GetInstance().UpdateTempUi(sensor.GetTemp());
}
```

Реализацию функции ```SendTempToUi``` тоже менять нельзя.

```c++
void InitUpdateUi() {
    ...
    EventloopBuilder loopBuilder(...);
    ...
    TeslaFahrenheitSensor sensor;
    loop.BuildTempUiUpdater([&]() {
        SendTempToUi(sensor);
    });
    ...
    Eventloop loop(loopBuilder.build());
    loop.start();
}
```

А вот функцию ```InitUpdateUi``` можно.  
  
**Что будем делать?**  
  
**> Надо адаптировать код ```TeslaFahrenheitSensor```**

```c++
class TeslaCelsiusSensorAdapter {    
  public:
    Adapter(TeslaFahrenheitSensor tfSensor_) 
      : tfSensor(std::make_shared(tfSensor_)) {}
    float GetTemp() const {
        return (ftSensor.GetTemp() - 32.0) * 5.0 / 9.0;
    }
  private:
    std::shared_ptr<TeslaFahrenheitSensor> tfSensor; 
};
```

```c++
void InitUpdateUi() {
    ...
    EventloopBuilder loopBuilder(...);
    ...
    TeslaFahrenheitSensor sensor;
    TeslaCelsiusSensorAdapter sensorAdapter(sensor);  // <-
    loop.BuildTempUiUpdater([&]() {
        SendTempToUi(sensorAdapter);                  // <-
    });
    ...
    Eventloop loop(loopBuilder.build());
    loop.start();
}
```

</p>
</details>

* Решение - ???
* Результат - Адаптер позволяет создать объект-прокладку, который будет превращать вызовы приложения в формат, 
  понятный стороннему классу.

<details><summary>Решение</summary>
<p>

Сделаем класс, который будет _адаптировать_ запросы клиента к формату, совместимому с исходным классом. 
Класс-адаптер можно реализовать на основании композиции или наследования.

</p>
</details>

---

# Фасад (Facade)

* Имя - Facade
* Задача - вы реализовали или ваш код использует сложную и тяжеловесную библиотеку/фреймворк с уймой классов, дающих
  гибкую настройку и гибкий функционал. Поэтому самостоятельно создавать объекты, следить за правильным порядком зависимостей
  и т.д.. Бизнес-логика ваших классов тесно переплетается с деталями реализации сторонних классов. 
  Такой код довольно сложно понимать и поддерживать.

<details><summary>Пример</summary>
<p>

Когда вы звоните в магазин и делаете заказ по телефону, сотрудник службы поддержки является вашим фасадом ко всем службам и отделам магазина. 
Он предоставляет вам упрощённый интерфейс к системе создания заказа, платёжной системе, упаковки, отделу доставки и тд.

</p>
</details>  

* Решение - ???
* Результат - Фасад предоставляет урезанный интерфейс, не имеющий 100% функциональности, которой можно достичь, 
  используя сложную подсистему напрямую. Но он предоставляет именно те фичи, которые нужны клиенту, и скрывает все остальные.

<details><summary>Решение</summary>
<p>

![Facade](facade.gif)

</p>
</details>

---

### Сравните Адаптер и Фасад