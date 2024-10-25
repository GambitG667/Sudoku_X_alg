# Сборка
для сборки проекта необходимо использовать `cmake`
```bash
mkdir build
cd build
cmake ..
make
./sudoku
```
# Описание
Данный проект представляет собой реализацию генератора судоку и решателя основанного на алгоритме X Кнута. Для оптимизации затрат памяти двоичная матрица представлена в виде двумерного связанного списка с, так называемыми, "пляшущими ссылками", что позволяет уменьшить затраты памяти и ускорить удаление и восстановление столбцов и строк.

## Алгоритм X
Алгоритм разработаный Дональдом Кнутом для нахождения точного покрытия множества подмножествами. Подмножества представляются в виде характеристического вектора, что открывает большое число возможностей для применения этого алгоритма во многих областях. В частности для судоку для каждой клетки должно выполнятся четыре условия:
1) в каждой клетке одно число
2) в каждой строке число встречается единожды
3) в каждом столбце число встречается единожды
4) в каждом квадранте число встречается единожды

Перевод этих условий в характеристический вектор длиной 4*n^2 (в случае с обычным судоку 4*9^2) позволяет применить алгоритм X.

### Описание алгоритма:
- Входные данные: множества S и Y; стэк Stack множеств, потенциально входящих в покрытие (может изначально быть пустой или уже иметь какие-то элементы)
1) Если множество S пустое - на стэке лежит искомое покрытие.
2) Если множество Y пустое - покрытие не найдено.
3) Ищем в множестве S элемент s, входящий в минимальное число множеств из Y.
4) Выбираем из Y все строчки X, содержащие s.
5) Для каждого множества X повторяем 6-9.
6) Добавляем X в стэк Stack как потенциальный элемент покрытия.
7) Формируем множества S' и Y': S' - это S, из которого удалены все элементы, содержащиеся в X, Y' - множества из Y, не пересекающиеся с X.
8) Вызываем алгоритм X для S', Y' и Stack.
9) Если на шаге 7 получено, что покрытие невозможно - снимаем с вершины Stackа элемент и переходим к следующему X. Если решение найдено - возвращаем его.
10) Если ни для какого X решения нет - для этих входных данных задача не решается.


## Генерация Судоку
Алгоритм генерации не оригинальный, был позаимствован мною из [статьи на хабре](https://habr.com/ru/articles/192102/). Суть алгоритма заключается в том, что свап столбцов и строк в пределах одного квадранта, а также свап соседних рядов квадрантов не нарушает верность Судоку. Алгоритм состоит в рандомном применении различных свапов.
После генерации уникальной таблицы, рандомно удаляются значения из клеток, с последующей проверкой единственности решения полученной головоломки.

# Использованные материалы
- https://habr.com/ru/articles/462411/
- https://habr.com/ru/articles/194410/
- https://habr.com/ru/articles/192102/
