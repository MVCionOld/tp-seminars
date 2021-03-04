### Что мы помним про Singleton и Prototype?

# Фабричный метод (Factory method)
* Имя - Factory method
* Задача - наша система должна оставаться расширяемой путем добавления объектов новых типов. 
  Непосредственное использование выражения ```new``` является нежелательным, так как в этом случае 
  код создания объектов с указанием конкретных типов может получиться разбросанным по всему 
  приложению. Тогда такие операции как добавление в систему объектов новых типов или замена 
  объектов одного типа на другой будут затруднительными, код будет **хрупкий**!
<details><summary>Пример</summary>
<p>
Рассмотрим пример процесса порождения сущностей техники в бух.учете IT-гиганта, такого, например, как Apple. 
В их продукцию входят как стационарные решения, так и носимые девайсы.

```cpp
class IWatch {
  public:
    std::string GetVersion() { ... }
    std::string GetSerialId() { ... }
    ...
};
class IPad {
  public:
    std::string GetVersion() { ... }
    std::string GetSerialId() { ... }
    ...
};
class IPod {
  public:
    std::string GetVersion() { ... }
    std::string GetSerialId() { ... }
    ...
};
class IPhone {
  public:
    std::string GetVersion() { ... }
    std::string GetSerialId() { ... }
    ...
};
class Macbook {
  public:
    std::string GetVersion() { ... }
    std::string GetSerialId() { ... }
    ...
};
class IMac {
  public:
    std::string GetVersion() { ... }
    std::string GetSerialId() { ... }
    ...
};
class Mac {
  public:
    std::string GetVersion() { ... }
    std::string GetSerialId() { ... }
    ...
};
class MacMini {
  public:
    std::string GetVersion() { ... }
    std::string GetSerialId() { ... }
    ...
};

/**
 * Отправляет на завод по производству стационарной продукции
 * запрос на производство следующие устройства в следующем количестве.
 * Дополнительно читает/пишет в несколько база данных и т.д.
 */
void ProduceDesktopDevices(
  std::vector<IMac*> &pIMacs,
  std::vector<Mac*> &pMacs,
  std::vector<MacMini*> &pMacMinis,
  size_t nIMacs, size_t nMacs, size_t nMacMinis) {
    ...
}

/**
 * Отправляет на завод по производству портативной продукции
 * запрос на производство следующие устройства в следующем количестве.
 * Дополнительно читает/пишет в несколько база данных и т.д.
 */
void ProducePortableDevices(
  std::vector<IWatch*> &pIWatches,
  std::vector<IPod*> &pIPods,
  std::vector<IPad*> &pIPads,
  std::vector<IPhone*> &pIPhones,
  std::vector<Macbook*> &pMacbooks,
  size_t nIWatches, size_t nIPods, size_t nIPads,
  size_t nIPhones, size_t nMacbooks) {
    ...
}

...
```

Какой же ужастный код!  
Во-первых, внутри и вне функций куча инициализаций, хочется этого избежать.  
Во-вторых, что произойдет, если добавятся новые товары: Apple AR Glasses, Apple ,... - код надо будет править во всех таких функциях? 
Это влечет к пастообразным партянкам из костылей, велосипедов и багов.  
Последнее, но не маловажное - функции дублируют друг друга (<b>DRY</b>).

Заметим, что каждый из классов всех видов техники имеет (и, возможно еще что-то) методы для 
получение своей версии и серийного номера. Давайте обозначим
общее для каждого вида в отдельном абстрактном классе ```AppleProduct```.  

```c++
class AppleProduct {
  public:
    virtual std::string GetVersion() = 0;
    virtual std::string GetSerialId() = 0;
    ...
};
class IWatch: public AppleProduct {
  public:
    std::string GetVersion() override { ... }
    std::string GetSerialId() override { ... }
    ...
};
class IPad: public AppleProduct { ... };
class IPod: public AppleProduct { ... };
class IPhone: public AppleProduct { ... };
class Macbook: public AppleProduct { ... };
class IMac: public AppleProduct { ... };
class Mac: public AppleProduct { ... };
class MacMini: public AppleProduct { ... };

/**
 * Отправляет на завод по производству стационарной продукции
 * запрос на производство следующие устройства в следующем количестве.
 * Дополнительно читает/пишет в несколько база данных и т.д.
 */
void ProduceDesktopDevices(
  std::vector<AppleProduct*> &newProducts, 
  size_t nIMacs, size_t nMacs, size_t nMacMinis) {
    ...
}

/**
 * Отправляет на завод по производству портативной продукции
 * запрос на производство следующие устройства в следующем количестве.
 * Дополнительно читает/пишет в несколько база данных и т.д.
 */
void ProducePortableDevices(
  std::vector<AppleProduct*> &newProducts,
  size_t nIWatches, size_t nIPods, size_t nIPads, 
  size_t nIPhones, size_t nMacbooks) {
    ...
}

...
```

Добавление абстрактного вносить лишь косметические улучшения, однако мы пока не решили проблему
гибкого создания объектов в случае расширения новыми видами техники.  

Возможно, кто-то предложит просто сделать использовать шаблоны, <b>НО</b>, как правило, запрос на
порождение новых объектов (кол-во каждого определенного типа) происходит динамически и вызывать 
конкретную реализацию в зависимости от динамических показателей не в каждом ЯПе возможно. Более того,
не все ЯПы имеют эти шаблоны. И самое главное: а должны ли мы перекомпилировать всю систему ради 
добавления одной новой сущности?

<b>Как такое решать?</b>

</p>
</details>  

* Решение - ???
* Результат - расширяемая система для добавления объектов новых типов.
<details><summary>Решение</summary>
<p>
Фабричный метод использует механизм полиморфизма - классы всех конечных типов наследуют от одного абстрактного базового 
класса, предназначенного для полиморфного использования. В этом базовом классе определяется единый интерфейс, через который 
пользователь будет оперировать объектами конечных типов.

Для обеспечения относительно простого добавления в систему новых типов паттерн локализует создание объектов конкретных 
типов в специальном классе-фабрике. Методы этого класса, посредством которых создаются объекты конкретных классов, 
называются фабричными. Существуют две разновидности паттерна:

<ul>
<li>
<b>Обобщенный конструктор</b>: когда в том же самом полиморфном базовом классе, от которого наследуют производные 
классы всех создаваемых в системе типов, определяется статический фабричный метод. 
В качестве параметра в этот метод должен передаваться идентификатор типа создаваемого объекта.
</li>
</ul>

```c++
enum AppleProductID {
    IWatchID
    ,IPadID
    ,IPodID
    ,IPhoneID
    ,MacbookID
    ,IMacID
    ,MacID
    ,MacMiniID
};

class AppleProduct {
  public:
    virtual std::string GetVersion() = 0;
    virtual std::string GetSerialId() = 0;
    ...
    static AppleProduct* CreateAppleProduct(AppleProductID id);
};
class IWatch: public AppleProduct {
  public:
    std::string GetVersion() override { ... }
    std::string GetSerialId() override { ... }
    ...
};
class IPad: public AppleProduct { ... };
class IPod: public AppleProduct { ... };
class IPhone: public AppleProduct { ... };
class Macbook: public AppleProduct { ... };
class IMac: public AppleProduct { ... };
class Mac: public AppleProduct { ... };
class MacMini: public AppleProduct { ... };

AppleProduct* AppleProduct::CreateAppleProduct(AppleProductID id) {
    AppleProduct* product;
    switch (id) {
      case IWatchID:
        product = new IWatch;
        break;
      case IPadID:
        product = new IPad;
        break;
        ...
    }
    return product;
};
```

<ul>
<li>
<b>Классический вариант фабричного метода</b>: когда интерфейс фабричных методов объявляется в независимом классе-фабрике, 
а их реализация определяется конкретными подклассами этого класса.
</li>
</ul>

```c++
class AppleProduct {
  public:
    virtual std::string GetVersion() = 0;
    virtual std::string GetSerialId() = 0;
    ...
    static AppleProduct* CreateAppleProduct(AppleProductID id);
};
class IWatch: public AppleProduct {
  public:
    std::string GetVersion() override { ... }
    std::string GetSerialId() override { ... }
    ...
};
class IPad: public AppleProduct { ... };
class IPod: public AppleProduct { ... };
class IPhone: public AppleProduct { ... };
class Macbook: public AppleProduct { ... };
class IMac: public AppleProduct { ... };
class Mac: public AppleProduct { ... };
class MacMini: public AppleProduct { ... };

class AppleProductFactory {
  public:
    virtual AppleProduct* CreateAppleProduct() = 0;
    virtual ~AppleProductFactory() {}
};

class IWatchFactory: public AppleProductFactory {
  public:
    AppleProduct* CreateAppleProduct() {
        return new IWatch;
    }
};
class IPadFactory: public AppleProductFactory {
  public:
    AppleProduct* CreateAppleProduct() {
        return new IPad;
    }
};
class IPodFactory: public AppleProductFactory { ... };
class IPhoneFactory: public AppleProductFactory { ... };
class MacbookFactory: public AppleProductFactory { ... };
class IMacFactory: public AppleProductFactory { ... };
class MacFactory: public AppleProductFactory { ... };
class MacMiniFactory: public AppleProductFactory { ... };
```

<b>Достоинства</b>:
<ul>
<li>избавляет класс от привязки к конкретным классам продуктов</li>
<li>упрощает добавление новых продуктов (открытость и закрытость)</li>
<li>упрощается поддержка продуктов</li>
</ul>

<b>Недостатки</b>:
<ul>
<li>на один объект создается два класса (продукт - фабрика)</li>
</ul>
</details>

# Абстрактная фабрика (Abstract factory)
* Имя - Abstract factory
* Задача - наша система должна оставаться независимой как от процесса создания новых объектов, так и от типов порождаемых 
  объектов. Непосредственное использование выражения ```new``` в коде приложения нежелательно (аналогично с прошлым примером).
  Также необходимо создавать группы или семейства взаимосвязанных объектов, исключая возможность одновременного использования 
  объектов из разных семейств в одном контексте.

<details><summary>Пример</summary>
<p>

Разрабатываем систему по продаже компьютерной техники самых хайповых IT-гигантов: Apple, Samsung, etc.  
Теперь систему бух.учета должна уметь работать с объектами всех типов по каждому производителю по отдельности.
Например, для переучета имеющейся продукции или в целях работы интернет-магазина (выборка техники по производителю, как в 
Яндекс Маркете).  

Подойдет ли Фабричный Метод для наших целей?

</p>
</details>

* Решение - ???
* Результат - система позволяет создавать семейства объектов, не привязываясь к конкретным классам создаваемых объектов.
<details><summary>Решение</summary>
<p>

![Абстрактная фабрика](images/abstract-factory.png)

<b>Достоинства</b>:
+ гарантирует сочетаемость создаваемых объектов
+ выделение кода производства продуктов в одно место
+ расширяет Factory Method в 2D

<b>Недостатки</b>:
- требует наличие всех типов в разных вариациях
- увеличивает число классов (не недостаток, на самом деле)

</p>
</details>

# Строитель (Builder)
* Имя - Builder
* Задача -
* Решение - ???
* Результат -
<details><summary>Решение</summary>
<p>

Паттерн Строитель определяет алгоритм поэтапного создания продукта в специальном классе ```Director``` (распорядитель), 
а ответственность за координацию процесса сборки отдельных частей продукта возлагает на иерархию классов ```Builder```. 
В этой иерархии базовый класс ```Builder``` объявляет интерфейсы для построения отдельных частей продукта, 
а соответствующие подклассы ```ConcreteBuilder*``` их реализуют подходящим образом, например, создают или получают нужные 
ресурсы, сохраняют промежуточные результаты, контролируют результаты выполнения операций.

![Строитель](images/builder.png)

</p>
</details>