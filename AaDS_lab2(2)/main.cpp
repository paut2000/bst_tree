#include <iostream>
#include <vector>
#include "Tree.h"

using namespace std;

template <typename T, typename K>
int Menu();

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(NULL));
    Menu<int, int>();
}

template <typename T, typename K>
int Menu() {

    Tree <T, K> tree;
    vector <K> keys;
    typename Tree<T, K>::iterator it1 = tree.begin(), it2 = tree.begin();
    typename Tree<T, K>::reverse_iterator rit1 = tree.rbegin(), rit2 = tree.rbegin();

    for (;;) {
        try {
            cout << "Дополнительные операции тестирования----------------------------------------------------------------" << endl;
            cout << "0.  Вывести деревео на экран" << endl;
            cout << "1.  Количество просмотренных узлов предыдущей операцией" << endl;
            cout << "2.  Протестировать коллекцию (не заполняет, а только тестирует; заполнить можно операциями 31 и 32)" << endl;
            cout << "Основные операции-----------------------------------------------------------------------------------" << endl;
            cout << "3.  Добавить узел" << endl;
            cout << "4.  Количество узлов в дереве" << endl;
            cout << "5.  Проверить на пустоту" << endl;
            cout << "6.  Получить элемент по ключу" << endl;
            cout << "7.  Очистить" << endl;
            cout << "8.  Удалить" << endl;
            cout << "9.  Список ключей в порядке обхода NLR" << endl;
            cout << "10. Функция по варианту: узнать порядковый номер узла" << endl;
            cout << "Прямой итератор-------------------------------------------------------------------------------------" << endl;
            cout << "11. Вывести элементы циклом foreach (range based for)" << endl;
            cout << "12. Создать итераторы, указывающие на begin" << endl;
            cout << "13. Инкрементировать 1-ый итератор ++" << endl;
            cout << "14. Инкрементировать 2-ой итератор ++" << endl;
            cout << "15. Декрементировать 1-ый итератор --" << endl;
            cout << "16. Декрементировать 2-ой итератор --" << endl;
            cout << "17. Разыменовать 1-ый итератор *" << endl;
            cout << "18. Разыменовать 2-ой итератор *" << endl;
            cout << "19. Сравнить 1-ый и 2-ой итераторы с помощью ==" << endl;
            cout << "20. Сравнить 1-ый и 2-ой итераторы с помощью !=" << endl;
            cout << "Обратный итератор-----------------------------------------------------------------------------------" << endl;
            cout << "21. Вывести все элементы циклом с использованием обратного итератора" << endl;
            cout << "22. Создать итераторы, указывающие на rbegin" << endl;
            cout << "23. Инкрементировать 1-ый итератор ++" << endl;
            cout << "24. Инкрементировать 2-ой итератор ++" << endl;
            cout << "25. Декрементировать 1-ый итератор --" << endl;
            cout << "26. Декрементировать 2-ой итератор --" << endl;
            cout << "27. Разыменовать 1-ый итератор *" << endl;
            cout << "28. Разыменовать 2-ой итератор *" << endl;
            cout << "29. Сравнить 1-ый и 2-ой итераторы с помощью ==" << endl;
            cout << "30. Сравнить 1-ый и 2-ой итераторы с помощью !=" << endl;
            cout << "Автоматическое заполнение дерева:-------------------------------------------------------------------" << endl;
            cout << "31. Заполнить случайными значениями c нормальным распределением add(значение rand(), ключ rand())" << endl;
            cout << "32. Заполнить вырожденной последовательностью for(i = 0; i < n; i++) add(значение rand(), ключ i)" << endl;

            int n;
            cin >> n;
            switch (n) {
            case 0: tree.out(); break;
            case 1:
                cout << tree.get_visited_node_quantity() << endl;
                break;
            case 2: {
                double labor_at = 0;
                double labor_add = 0;
                double labor_remove = 0;
                int quantity = tree.size();
                for (int i = 0; i < quantity / 2; i++) {
                    if (i % 10 == 0) {
                        try {
                            int key = rand();
                            if (tree.remove(key)) //если вдруг такой ключ есть
                                for (int i = 0; i < keys.size(); i++)
                                    if (key == keys[i]) 
                                        keys.erase(keys.begin() + i);
                            labor_remove += tree.get_visited_node_quantity();
                        }
                        catch (exception ex) {}
                        try {
                            tree.add(keys[rand() % keys.size()], 1);
                            labor_add += tree.get_visited_node_quantity();
                        }
                        catch (exception ex) {}
                        try {
                            tree.at(rand());
                            labor_at += tree.get_visited_node_quantity();
                        } catch(exception ex) {
                            labor_at += tree.get_visited_node_quantity();
                        }
                    }
                    else {
                        try {
                            int key = keys[rand() % keys.size()];
                            tree.remove(key);
                            labor_remove += tree.get_visited_node_quantity();
                            for (int i = 0; i < keys.size(); i++)
                                if (key == keys[i])
                                    keys.erase(keys.begin() + i);
                        }
                        catch (exception ex) {}
                        try {
                            int key = rand();
                            tree.add(key, 1);
                            labor_add += tree.get_visited_node_quantity();
                            keys.push_back(key);
                        }
                        catch (exception ex) {}
                        try {
                            tree.at(keys[rand() % keys.size()]);
                            labor_at += tree.get_visited_node_quantity();
                        }
                        catch (exception ex) {
                            labor_at += tree.get_visited_node_quantity();
                        }
                    }
                }
                cout << "Размер дерева: " << tree.size() << endl;
                cout << "Теоретическая оценка: " << 1.39 * (log((double)tree.size()) / log(2.0)) << endl;
                cout << "Экспериментальная оценка вставки: " << labor_add / (quantity / 2) << endl;
                cout << "Экспериментальная оценка удаления: " << labor_remove / (quantity / 2) << endl;
                cout << "Экспериментальная оценка поиска: " << labor_at / (quantity / 2) << endl;
                break;
            }
            case 3: {
                cout << "Введите ключ: ";
                K key;
                cin >> key;
                cout << "Введите значение: ";
                T value;
                cin >> value;
                tree.add(key, value);
                keys.push_back(key);
                break;
            }
            case 4: cout << tree.size() << endl; break;
            case 5: cout << tree.empty() << endl; break;
            case 6: {
                cout << "Введите ключ: ";
                K key;
                cin >> key;
                cout << tree.at(key) << endl;
                break;
            }
            case 7: 
                tree.clean();
                keys.clear();
                break;
            case 8: {
                cout << "Введите ключ: ";
                K key;
                cin >> key;
                bool b = tree.remove(key);
                cout << b << endl;
                if (b) 
                    for (int i = 0; i < keys.size(); i++) {
                        if (key == keys[i]) keys.erase(keys.begin() + i);
                    }
                break;
            }
            case 9: {
                for (K key : tree.list_of_keys())
                    cout << key << ' ';
                cout << endl;
                break;
            }
            case 10: {
                cout << "Введите ключ: ";
                K key;
                cin >> key;
                cout << tree.serial_number(key) << endl;
                break;
            }
            case 11:
                for (T value : tree)
                    cout << value << ' ';
                cout << endl;
                break;
            case 12:
                it1 = tree.begin();
                it2 = tree.begin();
                break;
            case 13:
                it1++;
                break;
            case 14:
                it2++;
                break;
            case 15:
                it1--;
                break;
            case 16:
                it2--;
                break;
            case 17:
                cout << *it1 << ' ' << it1.getKey() << endl;
                break;
            case 18:
                cout << *it2 << ' ' << it2.getKey() << endl;
                break;
            case 19:
                cout << (it1 == it2) << endl;
                break;
            case 20:
                cout << (it1 != it2) << endl;
                break;
            case 21:
                for (typename Tree<T, K>::reverse_iterator r_it = tree.rbegin(); r_it != tree.rend(); r_it++)
                    cout << *r_it << ' ';
                cout << endl;
                break;
            case 22:
                rit1 = tree.rbegin();
                rit2 = tree.rbegin();
                break;
            case 23:
                rit1++;
                break;
            case 24:
                rit2++;
                break;
            case 25:
                rit1--;
                break;
            case 26:
                rit2--;
                break;
            case 27:
                cout << *rit1 << ' ' << rit1.getKey() << endl;
                break;
            case 28:
                cout << *rit2 << ' ' << rit2.getKey() << endl;
                break;
            case 29:
                cout << (rit1 == rit2) << endl;
                break;
            case 30:
                cout << (rit1 != rit2) << endl;
                break;
            case 31: {
                cout << "Введите количество новых элементов: ";
                int n;
                cin >> n;
                for (int i = 0; i < n; i++)
                    try {
                    K key = rand();
                    T value = rand();
                    tree.add(key, value);
                    keys.push_back(key);
                }
                catch (exception ex) {
                    cout << ex.what() << endl;
                }
                break;
            }
            case 32: {
                cout << "Введите количество новых элементов: ";
                int n;
                cin >> n;
                for (int i = 0; i < n; i++)
                    try {
                    T value = rand();
                    tree.add(i, value);
                    keys.push_back(i);
                }
                catch (exception ex) {
                    cout << ex.what() << endl;
                }
                break;
            }
            default: "Неверный номер команды"; break;
            }
        }
        catch (exception ex) {
            cout << ex.what() << endl;
        }
        system("pause");
    }

    return 0;
}
