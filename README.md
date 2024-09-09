### Set

<details>
  <summary>Общая информация</summary>
<br />

Set (множество) - это ассоциативный контейнер уникальных элементов. Это означает, что в множество нельзя добавить один и тот же элемент дважды. Контейнер множество является ассоциативным, так как внутри он также представлен в виде дерева, как и контейнер map (словарь), и, соответственно, также хранит элементы в отсортированном порядке. Разница между словарем и множеством заключается в том, что уникальным в множестве является, не ключ а само значение, ровно как и поиск значения в дереве проверяется не по ключу, а по самому значению. При добавлении уже существующего элемента в множество возникает соответствующее исключение. 

В стандартной реализации, математические операции над множествами (пересечение, объединение, вычитание и т. д.) не реализуются на уровне класса.

</details>

<details>
  <summary>Спецификация</summary>
<br />

*Set Member type*

В этой таблице перечислены внутриклассовые переопределения типов (типичные для стандартной библиотеки STL), принятые для удобства восприятия кода класса:

| Member type            | Definition                                                                             |
|------------------------|----------------------------------------------------------------------------------------|
| `key_type`               | `Key` the first template parameter (Key)                                                     |
| `value_type`             | `Key` value type (the value itself is a key)                                                    |
| `reference`              | `value_type &` defines the type of the reference to an element                                                             |
| `const_reference`        | `const value_type &` defines the type of the constant reference                                         |
| `iterator`               | internal class `SetIterator<T>` or `BinaryTree::iterator` as the internal iterator of tree subclass; defines the type for iterating through the container                                                 |
| `const_iterator`         | internal class `SetConstIterator<T>` or `BinaryTree::const_iterator` as the internal const iterator of tree subclass; defines the constant type for iterating through the container                                           |
| `size_type`              | `size_t` defines the type of the container size (standard type is size_t) |

*Set Member functions*

В этой таблице перечислены основные публичные методы для взаимодействия с классом:

| Member functions      | Definition                                      |
|----------------|-------------------------------------------------|
| `set()`  | default constructor, creates empty set                                 |
| `set(std::initializer_list<value_type> const &items)`  | initializer list constructor, creates the set initizialized using std::initializer_list<T>    |
| `set(const set &s)`  | copy constructor  |
| `set(set &&s)`  | move constructor  |
| `~set()`  | destructor  |
| `operator=(set &&s)`      | assignment operator overload for moving object                                |


*Set Iterators*

В этой таблице перечислены публичные методы для итерирования по элементам класса (доступ к итераторам):

| Iterators              | Definition                                                                             |
|------------------------|----------------------------------------------------------------------------------------|
| `iterator begin()`            | returns an iterator to the beginning                                                   |
| `iterator end()`                | returns an iterator to the end                                                         |


*Set Capacity*

В этой таблице перечислены публичные методы для доступа к информации о наполнении контейнера:

| Capacity       | Definition                                      |
|----------------|-------------------------------------------------|
| `bool empty()`          | checks whether the container is empty           |
| `size_type size()`           | returns the number of elements                  |
| `size_type max_size()`       | returns the maximum possible number of elements |

*Set Modifiers*

В этой таблице перечислены публичные методы для изменения контейнера:

| Modifiers              | Definition                                                                             |
|------------------------|----------------------------------------------------------------------------------------|
| `void clear()`                  | clears the contents                                                                    |
| `std::pair<iterator, bool> insert(const value_type& value)`                 | inserts node and returns iterator to where the element is in the container and bool denoting whether the insertion took place                                        |
| `void erase(iterator pos)`                  | erases element at pos                                                                        |
| `void swap(set& other)`                   | swaps the contents                                                                     |
| `void merge(set& other);`                  | splices nodes from another container                                                   |

*Set Lookup*

В этой таблице перечислены публичные методы, осуществляющие просмотр контейнера:

| Lookup                 | Definition                                                                             |
|------------------------|----------------------------------------------------------------------------------------|
| `iterator find(const Key& key)`                   | finds element with specific key                                                        |
| `bool contains(const Key& key)`               | checks if the container contains element with specific key                             |

</details>

<details>
  <summary>Для тестирования</summary>
<br />
  Зайти в репозиторий

  Ввести в командную строку ''make''  
  Чтобы посмотреть покрытие через браузер, надо открыть файл set_coverage_report.html после использования ''make''
</details>

<details>
  <summary>Для использования</summary>
<br />
  Достаточно добавить #include "s21_set.h" в заголовок проекта, в котором собираетесь его использовать
</details>
