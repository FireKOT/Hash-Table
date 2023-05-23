# Хеш-таблица

## Введение
 
Данная работа исследует распределение различных хеш-функций и оптимизацию поиска в хеш-таблице с закрытой адресацией.

### Хеш-таблица с закрытой адресацией

**Хеш-таблица** - это структура данных, реализующая ассоциативный массив, сопоставляющий каждому входному ключу целое неотрицательное число - индекс в массиве. Это сопоставление осуществляется при помощи хеширования, и так как хеш-функция может создавать коллизии (сопоставление разным ключам одного значения), то каждым элементом массива будет являтся список, в который будут помещаться ключи с одинаковым хешем. Такая реализация хеш-таблицы называется **хеш-таблицей с закрытой адресацией**.

**Основное свойство хеш-таблицы** - это быстрое добавление, удаление и поиск элементов. Оно достигается при помощи нахождения хеш-функции с равномерным распределением и подбором подходящего размера массива.

## Часть 1. Сравнение хеш-функций

В первой части исследования было произведено сравнение распределения 7 хеш-функций.
Все тесты производились на файле [words.txt](https://github.com/FireKOT/Hash-Table/blob/main/words.txt) с 58110 английскими словами, длина которых не превышает 30 символов, и при размере хеш-таблицы 1013.

#### Формат тестового файла
В первой строке идет число n - количество слов, далее в n строках по одному англискому слову, длина которого не превышает 30 символов.

#### Хеш-функции:
1. **hashZero** - всегда возвращает 0.
2. **hashFirstChar** - возвращает ASCII код первего символа слова (или 0, если такового нет).
3. **hashStrLen** - возвращает количество символов в слове.
4. **hashStrSum** - возвращает сумму ASCII кодов всех символов слова.
5. **hashRotr** - циклический сдвик хеша вправо и xor со значение элемента ключа.
6. **hashRotl** - циклический сдвик хеша влево и xor со значение элемента ключа.
7. **hashCRC32** - алгоритм нахождения контрольной суммы.

### Анализ

Ниже представлены графики распределения семи указанных хеш-функций.

---

### 1. hashZero
![](https://github.com/FireKOT/Hash-Table/blob/main/plots/hashZero.png)
![](https://github.com/FireKOT/Hash-Table/blob/main/plots/hashZeroEnlarged.png)

* Максимальный размер списка: 58110
* Минимальный размер списка: 0
* Среднеквадратичное отклонение размеров списков: 1824.9

---

### 2. hashFirstChar
![](https://github.com/FireKOT/Hash-Table/blob/main/plots/hashFirstChar.png)
![](https://github.com/FireKOT/Hash-Table/blob/main/plots/hashFirstCharEnlarged.png)

* Максимальный размер списка: 6670
* Минимальный размер списка: 0
* Среднеквадратичное отклонение размеров списков: 444.5

---

### 3. hashStrLen
![](https://github.com/FireKOT/Hash-Table/blob/main/plots/hashStrLen.png)
![](https://github.com/FireKOT/Hash-Table/blob/main/plots/hashStrLenEnlarged.png)

* Максимальный размер списка: 9396
* Минимальный размер списка: 0
* Среднеквадратичное отклонение размеров списков: 609.7

---

### 4. hashStrSum
![](https://github.com/FireKOT/Hash-Table/blob/main/plots/hashStrSum.png)

* Максимальный размер списка: 230
* Минимальный размер списка: 0
* Среднеквадратичное отклонение размеров списков: 53.4

---

### 5. hashRotr
![](https://github.com/FireKOT/Hash-Table/blob/main/plots/hashRotr.png)

* Максимальный размер списка: 113
* Минимальный размер списка: 18
* Среднеквадратичное отклонение размеров списков: 19.5

---

#### 6. hashRotl
![](https://github.com/FireKOT/Hash-Table/blob/main/plots/hashRotl.png)

* Максимальный размер списка: 88
* Минимальный размер списка: 24
* Среднеквадратичное отклонение размеров списков: 11.6

---

### 7. hashCRC32
![](https://github.com/FireKOT/Hash-Table/blob/main/plots/hashCRC32.png)

* Максимальный размер списка: 81
* Минимальный размер списка: 34
* Среднеквадратичное отклонение размеров списков: 7.7

---

### Вывод

Из графиков видно, что лучше всего себя показала хеш-функция hashCRC32 и что она наиболее равномерно распределяет входные данные. Среди представленных функций у нее наименьший максимальный размер списка , наибольший минимальный размер списка и наименьшее среднеквадратичное отклонение размеров спискав. 

## Часть 2. Оптимизация поиска по хеш-таблице

Во второй части исследовались возможности оптимизации поиска по хеш-таблице.

#### Конфигурация изначальной хеш-таблицы:

* Хеш-таблица с закрытой адресацией
* В качестве элементов массива использовались двусвязные списки на массивах
* Размер хеш-таблицы: 1013
* Хеш-функция: hashCRC32

#### Методы тестирования:

Тестирование производилось на файле [words.txt](https://github.com/FireKOT/Hash-Table/blob/main/words.txt) с 58110 английскими словами, длина которых не превышает 30 символов.

На каждом этапе оптимизации производилось 20 измерений, в каждом из которых таблица заполнялась всеми словами из файла, после чего в ней 100 раз искалось каждое слово из того же файла.

#### Условия тестирования

* Процессор AMD Ryzen 5 5500U 2.1 ГГц
* Измерения производились с опциями компилятора GCC -O1 и -mavx2

Для нахождения проблеммных мест программы был использован профайлер valgrind. Критерием выбора функции для оптимизации был выбран параметр self - процент времени выполнения программы, потраченный конкретно на эту функцию.

### Изначальная версия

Версия    | Среднее время (мс) | Абсолютный прирост (раз) | Относительный прирост (раз)
:--------:|:------------------:|:------------------------:|:--------------------:
Изначальная   | $$2050 \pm 52$$    | N/A                      | N/A
        
Поскольку в базовой версии программы измерения проходят в условиях, аналагичных условиям измерения графиков, то можно заметить, что в данной версии большое количество коллизий, поэтому первой оптимизацией был увеличен размер таблицы до 11777.

### Первая оптимизация

Версия                    | Среднее время (мс)  | Абсолютный прирост (раз) | Относительный прирост (раз)
:------------------------:|:-------------------:|:------------------------:|:--------------------:
Оптимизированный размер   | $$858 \pm 5.9$$     | $$2.4 \pm 0.7$$          |  $$2.4 \pm 0.7$$ 

По результатам работы профайлера было выяснено, что при текущей оптимизации наиболее затратной функцией является **hashCRC32**. 

![](https://github.com/FireKOT/Hash-Table/blob/main/profiles/FirstOptimization.png "Профилирование первой оптимизации")

Поэтому была написана на ассемблере при помощи ассемблерной вставки функция hashCRC32Fast.

### Вторая оптимизация

Версия                 | Среднее время (мс) | Абсолютный прирост (раз) | Относительный прирост (раз)
:---------------------:|:------------------:|:------------------------:|:--------------------:
Оптимизированный хеш   | $$656 \pm 5.2$$    | $$3.1 \pm 0.1$$          | $$1.31 \pm 0.02$$

По результатам следующего профилирования было выяснено, что после последней оптимизации наиболее затратной функцией стала strcmp.

![](https://github.com/FireKOT/Hash-Table/blob/main/profiles/SecondOptimization.png "Профилирование второй оптимизации")

Поэтому при помощи интринсик команд была написана функция strCmpFast.

### Третья оптимизация

Версия                 | Среднее время (мс)   | Абсолютный прирост (раз) | Относительный прирост (раз)
:---------------------:|:--------------------:|:------------------------:|:--------------------:
Оптимизированное сравнение строк   | $$543 \pm 5.0$$      | $$3.8 \pm 0.13$$         | $$1.21 \pm 0.02$$ 

После очередного профилирования было выявлено, что новой самой затратной функцией стала hashTableFind.

![](https://github.com/FireKOT/Hash-Table/blob/main/profiles/ThirdOptimization.png "Профилирование третьей оптимизации")

Поэтому была написана на ассемблера функция hashTableFindAsm, в которой было оптимизированно обращение к памяти.

### Четвертая оптимизация 

Версия                 | Среднее время (мс)   | Абсолютный прирост (раз) | Относительный прирост (раз)
:---------------------:|:--------------------:|:------------------------:|:--------------------:
Оптимизированный поиск в таблице   | $$496 \pm 3.3$$      | $$4.1 \pm 0.13$$         | $$1.09 \pm 0.02$$ 

Поскольку последняя оптимизация дала относительный прирост менее 10%, то мы посчитали, что дальнейшие оптимизации будут не столь существенны и остановились.

### Сводка оптимизации

Версия    | Среднее время (мс) | Абсолютный прирост (раз) | Относительный прирост (раз)
:--------:|:------------------:|:------------------------:|:--------------------:
Изначальная   | $$2050 \pm 52$$    | N/A                      | N/A
Оптимизированный размер   | $$858 \pm 5.9$$     | $$2.4 \pm 0.7$$          |  $$2.4 \pm 0.7$$
Оптимизированный хеш   | $$656 \pm 5.2$$    | $$3.1 \pm 0.1$$          | $$1.31 \pm 0.02$$
Оптимизированное сравнение строк   | $$543 \pm 5.0$$      | $$3.8 \pm 0.13$$         | $$1.21 \pm 0.02$$ 
Оптимизированный поиск в таблице   | $$496 \pm 3.3$$      | $$4.1 \pm 0.13$$         | $$1.09 \pm 0.02$$ 

## Вывод

На основе произведенного исследований можно заключить, что не всякую функцию можно брать в качестве хеш-функции из-за возможной плохой равномерности, что компилятор GCC с флагами -O1 и -mavx2 компилирует далеко не самую оптимизированную хеш-таблицу, а также, что при реализации хеш-таблицы крайне важно подобрать подходящий размер массива. Правильным выбором размера и ассемблерными оптимизациями можно добиться ускорения в 4.1 раза, только ассемблерными оптимизациями в 1.7 раз.
