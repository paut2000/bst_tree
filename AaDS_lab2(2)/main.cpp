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
            cout << "�������������� �������� ������������----------------------------------------------------------------" << endl;
            cout << "0.  ������� ������� �� �����" << endl;
            cout << "1.  ���������� ������������� ����� ���������� ���������" << endl;
            cout << "2.  �������������� ��������� (�� ���������, � ������ ���������; ��������� ����� ���������� 31 � 32)" << endl;
            cout << "�������� ��������-----------------------------------------------------------------------------------" << endl;
            cout << "3.  �������� ����" << endl;
            cout << "4.  ���������� ����� � ������" << endl;
            cout << "5.  ��������� �� �������" << endl;
            cout << "6.  �������� ������� �� �����" << endl;
            cout << "7.  ��������" << endl;
            cout << "8.  �������" << endl;
            cout << "9.  ������ ������ � ������� ������ NLR" << endl;
            cout << "10. ������� �� ��������: ������ ���������� ����� ����" << endl;
            cout << "������ ��������-------------------------------------------------------------------------------------" << endl;
            cout << "11. ������� �������� ������ foreach (range based for)" << endl;
            cout << "12. ������� ���������, ����������� �� begin" << endl;
            cout << "13. ���������������� 1-�� �������� ++" << endl;
            cout << "14. ���������������� 2-�� �������� ++" << endl;
            cout << "15. ���������������� 1-�� �������� --" << endl;
            cout << "16. ���������������� 2-�� �������� --" << endl;
            cout << "17. ������������ 1-�� �������� *" << endl;
            cout << "18. ������������ 2-�� �������� *" << endl;
            cout << "19. �������� 1-�� � 2-�� ��������� � ������� ==" << endl;
            cout << "20. �������� 1-�� � 2-�� ��������� � ������� !=" << endl;
            cout << "�������� ��������-----------------------------------------------------------------------------------" << endl;
            cout << "21. ������� ��� �������� ������ � �������������� ��������� ���������" << endl;
            cout << "22. ������� ���������, ����������� �� rbegin" << endl;
            cout << "23. ���������������� 1-�� �������� ++" << endl;
            cout << "24. ���������������� 2-�� �������� ++" << endl;
            cout << "25. ���������������� 1-�� �������� --" << endl;
            cout << "26. ���������������� 2-�� �������� --" << endl;
            cout << "27. ������������ 1-�� �������� *" << endl;
            cout << "28. ������������ 2-�� �������� *" << endl;
            cout << "29. �������� 1-�� � 2-�� ��������� � ������� ==" << endl;
            cout << "30. �������� 1-�� � 2-�� ��������� � ������� !=" << endl;
            cout << "�������������� ���������� ������:-------------------------------------------------------------------" << endl;
            cout << "31. ��������� ���������� ���������� c ���������� �������������� add(�������� rand(), ���� rand())" << endl;
            cout << "32. ��������� ����������� ������������������� for(i = 0; i < n; i++) add(�������� rand(), ���� i)" << endl;

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
                            if (tree.remove(key)) //���� ����� ����� ���� ����
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
                cout << "������ ������: " << tree.size() << endl;
                cout << "������������� ������: " << 1.39 * (log((double)tree.size()) / log(2.0)) << endl;
                cout << "����������������� ������ �������: " << labor_add / (quantity / 2) << endl;
                cout << "����������������� ������ ��������: " << labor_remove / (quantity / 2) << endl;
                cout << "����������������� ������ ������: " << labor_at / (quantity / 2) << endl;
                break;
            }
            case 3: {
                cout << "������� ����: ";
                K key;
                cin >> key;
                cout << "������� ��������: ";
                T value;
                cin >> value;
                tree.add(key, value);
                keys.push_back(key);
                break;
            }
            case 4: cout << tree.size() << endl; break;
            case 5: cout << tree.empty() << endl; break;
            case 6: {
                cout << "������� ����: ";
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
                cout << "������� ����: ";
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
                cout << "������� ����: ";
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
                cout << "������� ���������� ����� ���������: ";
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
                cout << "������� ���������� ����� ���������: ";
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
            default: "�������� ����� �������"; break;
            }
        }
        catch (exception ex) {
            cout << ex.what() << endl;
        }
        system("pause");
    }

    return 0;
}
