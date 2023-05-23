# Хеш-таблица

## Введение
 
Данная работа исследует распределение различных хеш-функций и оптимизацию поиска в хеш-таблице с закрытой адресацией.

### Хеш-таблица с закрытой адресацией

**Хеш-таблица** - это структура данных, реализующая ассоциативный массив, сопостовляющий каждому входному ключу целое неотрицательное число - индекс в массиве. Это сопоставление осуществляется при помощи хеширования, и так как хеш-функция может создавать коллизии (сопоставление разным ключам одного значения), то каждым элементом массива будет являтся список, в который будут помещаться ключи с одинаковым хешем. Такая реализация хеш-таблицы называется **хеш-таблицей с закрытой адресацией**.

**Основное свойство хеш-таблицы** - это быстрое добавление, удаление и поиск элементов. Оно достигается при помощи нахождения хеш-функции с равномерным распределением и подбором подходящего размера массива.

## Часть 1. Сравнение хеш-функций

В первой части исследования было произведено сравнение распределения 7 хеш-функций.
Все тесты производились на файле [words.txt]() с 58110 английскими словами, длина которых не превышает 30 символов, и при размере хеш-таблицы 1013.

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

Ниже представлены графики распределения 7 указанных хеш-функций.

---

#### 1. hashZero
![](https://github.com/FireKOT/Hash-Table/blob/main/plots/hashZero.png)
![](https://github.com/FireKOT/Hash-Table/blob/main/plots/hashZeroEnlarged.png)

* Максимальный размер списка: 58110
* Минимальный размер списка: 0
* Среднеквадратичное размеров списков: 1825.8

---

#### 2. hashFirstChar
![](https://github.com/FireKOT/Hash-Table/blob/main/plots/hashFirstChar.png)
![](https://github.com/FireKOT/Hash-Table/blob/main/plots/hashFirstCharEnlarged.png)

* Максимальный размер списка: 6670
* Минимальный размер списка: 0
* Среднеквадратичное размеров списков: 448.2

---

#### 3. hashStrLen
![](https://github.com/FireKOT/Hash-Table/blob/main/plots/hashStrLen.png)
![](https://github.com/FireKOT/Hash-Table/blob/main/plots/hashStrLenEnlarged.png)

* Максимальный размер списка: 9396
* Минимальный размер списка: 0
* Среднеквадратичное размеров списков: 612.4

---

#### 4. hashStrSum
![](https://github.com/FireKOT/Hash-Table/blob/main/plots/hashStrSum.png)

* Максимальный размер списка: 230
* Минимальный размер списка: 0
* Среднеквадратичное размеров списков: 78.4

---

#### 5. hashRotr
![](https://github.com/FireKOT/Hash-Table/blob/main/plots/hashRotr.png)

* Максимальный размер списка: 113
* Минимальный размер списка: 18
* Среднеквадратичное размеров списков: 60.6

---

#### 6. hashRotl
![](https://github.com/FireKOT/Hash-Table/blob/main/plots/hashRotl.png)

* Максимальный размер списка: 88
* Минимальный размер списка: 24
* Среднеквадратичное размеров списков: 58.5

---

#### 7. hashCRC32
![](https://github.com/FireKOT/Hash-Table/blob/main/plots/hashCRC32.png)

* Максимальный размер списка: 81
* Минимальный размер списка: 34
* Среднеквадратичное размеров списков: 57.9

---

### Вывод

Из графиков видно, что лучше всего себя показала хеш-функция hashCRC32 и что она наиболее равномерно распределяет входные данные. Среди представленных функций у нее наименьший максимальный размер списка , наибольший минимальный размер списка и наименьшее среднеквадратичное размеров спискав. 

## Часть 2. Оптимизация поиска по хеш-таблице

