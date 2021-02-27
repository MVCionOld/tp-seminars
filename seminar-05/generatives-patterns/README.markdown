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
Рассмотрим пример процесса порождения военных персонажей стратегической игры. Будем создавать
военные персонажи для некой армии без учета особенностей воюющих сторон.

```cpp
class Infantryman {
  public:
    void Attack() { std::cout << "Infantryman attack" << std::endl; }
    ...
};
class Archer {
  public:
    void Attack() { std::cout << "Archer attack" << std::endl; }
    ...
};
class Horseman {
  public:
    void Attack() { std::cout << "Horseman attack" << std::endl; }
    ...
};

int main() {
    std::vector<Infantryman*> pInfantries = { ... };
    std::vector<Archer*>      pArchers    = { ... };
    std::vector<Horseman*>    pHorsemen   = { ... };
    
    for (auto pInfantry: pInfantries) pInfantry->Attack();
    for (auto pArcher:   pArchers)    pArcher->Attack();
    for (auto pHorseman: pHorsemen)   pHorseman->Attack();
}
```

Заметим, что каждый из видов воинов умеет атаковать (и, возможно еще что-то). Давайте обозначим
общее для каждого вида воина в отдельном абстрактном классе ```Warrior```.  

```c++
class Warrior {
  public:
    virtual void Attack() = 0;
};

class Infantryman: public Warrior {
  public:
    void Attack() override { std::cout << "Infantryman attack" << std::endl; }
    ...
};
class Archer: public Warrior {
  public:
    void Attack() override { std::cout << "Archer attack" << std::endl; }
    ...
};
class Horseman: public Warrior {
  public:
    void Attack() override { std::cout << "Horseman attack" << std::endl; }
    ...
};

int main() {
    std::vector<Warrior*> pWarriors = { ... };
    
    for (auto pWarrior: pWarriors) pWarrior->Attack();
}
```

Добавление абстрактного вносить лишь косметические улучшения, однако мы пока не решили проблему
гибкого создания объектов в случае расширения новыми видами воинов.
</p>
</details>  

* Решение - ???
* Результат - 
<details><summary>Решение</summary>
<p>
</p>
</details>

# Абстрактная фабрика (Abstract factory)
* Имя - Abstract factory
* Задача -
* Решение - ???
* Результат -
<details><summary>Решение</summary>
<p>
</p>
</details>

# Строитель (Builder)
* Имя - Builder
* Задача -
* Решение - ???
* Результат -
<details><summary>Решение</summary>
<p>
</p>
</details>