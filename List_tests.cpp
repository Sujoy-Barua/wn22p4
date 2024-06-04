// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"

using namespace std;

// Add your test cases here

TEST(test_list_default_ctor_clear) {
    // Add test code here
    List<int> my_list;
    ASSERT_TRUE(my_list.empty());
    ASSERT_TRUE(my_list.size() == 0);

    for (int i = 0; i < 5; i++) {
        my_list.push_back(i);
    }

    ASSERT_FALSE(my_list.empty());

    List<int> my_list_2(my_list);
    ASSERT_EQUAL(my_list.front(), my_list_2.front());
    ASSERT_EQUAL(my_list.back(), my_list_2.back());

    List<int>::Iterator iter1 = my_list.begin();
    List<int>::Iterator iter2 = my_list_2.begin();

    while (iter1 != my_list.end()) {
        ASSERT_EQUAL(*iter1, *iter2);
        ++iter1;
        ++iter2;
    }

    ASSERT_EQUAL(iter1, my_list.end());
    ASSERT_EQUAL(iter2, my_list_2.end());

    my_list.clear();
    ASSERT_TRUE(my_list.empty());
    ASSERT_TRUE(my_list.size() == 0);

    my_list.push_back(10);
    ASSERT_FALSE(my_list.empty());
    my_list.clear();
    ASSERT_TRUE(my_list.empty());
    ASSERT_TRUE(my_list.size() == 0);
    
    my_list.push_back(100);
    List<int> my_list_3(my_list);
    ASSERT_EQUAL(my_list.front(), my_list_3.front());
    ASSERT_EQUAL(my_list.back(), my_list_3.back());
    ASSERT_EQUAL(*my_list.begin(), *my_list_3.begin());
    ASSERT_EQUAL(++my_list.begin(), my_list_3.end());
}

TEST(test_list_pushNpop_backNfront) {
    List<int> my_list;
    ASSERT_TRUE(my_list.empty());
    ASSERT_TRUE(my_list.size() == 0);

    my_list.push_front(10);
    ASSERT_EQUAL(my_list.front(), 10);
    ASSERT_EQUAL(my_list.back(), 10);
    ASSERT_TRUE(my_list.size() == 1);

    my_list.push_back(14);
    my_list.push_back(5);
    my_list.push_back(15);
    ASSERT_EQUAL(my_list.front(), 10);
    ASSERT_EQUAL(my_list.back(), 15);
    ASSERT_EQUAL(my_list.size(), 4);

    my_list.pop_back();
    ASSERT_EQUAL(my_list.front(), 10);
    ASSERT_EQUAL(my_list.back(), 5);
    ASSERT_EQUAL(my_list.size(), 3);

    my_list.push_back(20);
    my_list.pop_front();
    ASSERT_EQUAL(my_list.front(), 14);
    ASSERT_EQUAL(my_list.back(), 20);

    my_list.push_front(30);
    ASSERT_EQUAL(my_list.front(), 30);
    ASSERT_EQUAL(my_list.back(), 20);

    my_list.pop_back();
    ASSERT_EQUAL(my_list.front(), 30);
    ASSERT_EQUAL(my_list.back(), 5);

    my_list.pop_back();
    ASSERT_EQUAL(my_list.size(), 2);
    my_list.pop_back();
    ASSERT_EQUAL(my_list.size(), 1);
    my_list.pop_back();
    ASSERT_EQUAL(my_list.size(), 0);
    my_list.push_front(100);
    my_list.pop_front();
    ASSERT_TRUE(my_list.empty());

    my_list.push_front(30);
    my_list.front() = 10;
    my_list.back() = 10;
    ASSERT_EQUAL(my_list.front(), 10);
    ASSERT_EQUAL(my_list.back(), 10);

    my_list.pop_front();
    my_list.push_back(50);
    my_list.push_back(20);
    my_list.push_back(30);
    my_list.front() = 10;
    my_list.back() = 100;
    ASSERT_EQUAL(my_list.front(), 10);
    ASSERT_EQUAL(my_list.back(), 100);
    // 10 20 100
    my_list.push_back(30);
    // 10 20 100 30
    ASSERT_EQUAL(my_list.front(), 10);
    ASSERT_EQUAL(my_list.back(), 30);
    my_list.pop_back();
    ASSERT_EQUAL(my_list.front(), 10);
    ASSERT_EQUAL(my_list.back(), 100);
    my_list.pop_back();
    ASSERT_EQUAL(my_list.front(), 10);
    ASSERT_EQUAL(my_list.back(), 20);
    my_list.pop_back();
    ASSERT_EQUAL(my_list.front(), 10);
    ASSERT_EQUAL(my_list.back(), 10);
    my_list.pop_back();

    my_list.push_back(10);
    my_list.push_back(20);
    my_list.push_back(100);
    my_list.push_back(30);
    // 10 20 100 30
    ASSERT_EQUAL(my_list.front(), 10);
    ASSERT_EQUAL(my_list.back(), 30);
    my_list.pop_front();
    ASSERT_EQUAL(my_list.front(), 20);
    ASSERT_EQUAL(my_list.back(), 30);
    my_list.pop_front();
    ASSERT_EQUAL(my_list.front(), 100);
    ASSERT_EQUAL(my_list.back(), 30);
    my_list.pop_front();
    ASSERT_EQUAL(my_list.front(), 30);
    ASSERT_EQUAL(my_list.back(), 30);
    my_list.pop_front();

    my_list.push_back(10);
    ASSERT_EQUAL(my_list.front(), 10);
    ASSERT_EQUAL(my_list.back(), 10);
    
}

TEST(test_list_insert_erase) {
    List<int> my_list;
    List<int>::Iterator iter = my_list.begin();
    my_list.insert(iter, 42);
    ASSERT_EQUAL(my_list.front(), 42);
    ASSERT_EQUAL(my_list.back(), 42);
    ASSERT_EQUAL(my_list.back(), my_list.front());
    iter = my_list.begin();
    ASSERT_EQUAL(*iter, 42);
    my_list.insert(iter, 30);
    ASSERT_EQUAL(my_list.front(), 30);
    ASSERT_EQUAL(my_list.back(), 42);

    List<int>::Iterator iter2 = my_list.end();
    const List<int>::Iterator iter3 = iter2;
    ASSERT_TRUE(iter2 == iter3);
    ASSERT_FALSE(iter2 != iter3);

    iter = my_list.begin();
    ++iter;
    ASSERT_EQUAL(*iter, 42);
    ASSERT_EQUAL(my_list.size(), 2);
    --iter;
    ASSERT_EQUAL(*iter, 30);
    ASSERT_FALSE(iter3 == iter);
    ASSERT_TRUE(iter3 != iter);
    ASSERT_EQUAL(my_list.size(), 2);

    my_list.erase(++iter);
    ASSERT_TRUE(my_list.size() == 1);
    ASSERT_EQUAL(my_list.front(), 30);

    iter = my_list.begin();
    my_list.erase(iter);
    ASSERT_TRUE(my_list.size() == 0);
}

TEST(test_list_assignment) {
    List<int> my_list;
    for (int i = 0; i < 5; i++) {
        my_list.push_back(i);
    }

    List<int> my_list_cpy;

    my_list_cpy = my_list;

    List<int>::Iterator iter1 = my_list.begin();
    List<int>::Iterator iter2 = my_list_cpy.begin();

    while (iter1 != my_list.end()) {
        ASSERT_EQUAL(*iter1, *iter2);
        ++iter1;
        ++iter2;
    }

    my_list.clear();
    ASSERT_TRUE(my_list.size() == 0);
}

TEST(test_all) {
    List<int> my_list;

    int size = 0;
    ASSERT_TRUE(my_list.empty());
    ASSERT_TRUE(my_list.size() == size);

    my_list.push_front(42);
    my_list.push_back(42);

    ASSERT_EQUAL(my_list.front(), 42);
    ASSERT_EQUAL(*my_list.begin(), 42);
    ASSERT_EQUAL(my_list.back(), 42);

    my_list.front() = 73;
    my_list.back() = 73;

    ASSERT_EQUAL(my_list.front(), 73);
    ASSERT_EQUAL(*my_list.begin(), 73);
    ASSERT_EQUAL(my_list.back(), 73);

    List<int> list2;
    list2 = my_list;

    ASSERT_EQUAL(list2.front(), 73);
    ASSERT_EQUAL(*list2.begin(), 73);
    ASSERT_EQUAL(list2.back(), 73);

    List<int>::Iterator iter = list2.begin();
    list2.insert(iter, 42);
    ASSERT_EQUAL(list2.front(), 42);
    ASSERT_EQUAL(list2.back(), 73);
    iter = list2.begin();
    list2.erase(iter);
    ASSERT_EQUAL(list2.front(), 73);
    ASSERT_EQUAL(list2.back(), 73);
    iter = list2.begin();

    List<int>::Iterator iter2 = list2.end();
    const List<int>::Iterator iter3 = iter2;

    ASSERT_FALSE(iter == iter2);
    ASSERT_FALSE(iter2 == iter);
    ASSERT_TRUE(iter != iter2);
    ASSERT_TRUE(iter2 != iter);
    ASSERT_TRUE(iter3 == list2.end());
    ASSERT_TRUE(list2.end() == iter3);
    list2.push_front(42);
    list2.push_back(42);
    iter = list2.begin();
    ASSERT_TRUE(iter != iter2);
    ASSERT_FALSE(iter3 != list2.end());
    ASSERT_FALSE(list2.end() != iter3);
    ++iter;
    ASSERT_EQUAL(*iter, 73);

    List<int>::Iterator iter_cpy(iter);
    ASSERT_EQUAL(*iter_cpy, 73);
    List<int>::Iterator iter_cpy2 = iter;
    ASSERT_EQUAL(*iter_cpy2, 73);

    ASSERT_EQUAL(++--iter, iter);
    ASSERT_EQUAL(*--++list2.begin(), 42);

    list2.insert(list2.begin(), 3);
    ASSERT_EQUAL(*list2.begin(), 3);
    ASSERT_EQUAL(list2.front(), 3);

    List<int> list3;
    list3.push_back(3);
    ASSERT_EQUAL(*list3.begin(), 3);

    List<int> list4;
    list4.push_front(4);
    ASSERT_EQUAL(*list4.begin(), 4);

    List<int> list5;
    list5.push_front(10);
    List<int>::Iterator iter5 = list5.begin();
    list5.erase(iter5);
    ASSERT_EQUAL(list5.size(), 0);

    List<int> list6;
    list6.push_back(5);
    list6.push_back(10);
    list6.push_back(15);
    list6.push_back(20);
    List<int>::Iterator iter6 = list6.begin();
    list6.erase(++++iter6);
    ASSERT_EQUAL(list6.size(), 3);
    iter6 = list6.begin();
    ASSERT_EQUAL(*iter6, 5);
    ASSERT_EQUAL(*++iter6, 10);
    ASSERT_EQUAL(*++iter6, 20);

    List<int> list7;
    list7.push_back(5);
    list7.push_back(10);
    list7.push_back(15);
    list7.push_back(20);
    List<int>::Iterator iter7 = list7.begin();
    list7.insert(++++iter7, 69);
    ASSERT_EQUAL(list7.size(), 5);
    iter7 = list7.begin();
    ASSERT_EQUAL(*iter7, 5);
    ASSERT_EQUAL(*++iter7, 10);
    ASSERT_EQUAL(*++iter7, 69);
    ASSERT_EQUAL(*++iter7, 15);
    ASSERT_EQUAL(*++iter7, 20);

    iter7 = list7.begin();
    list7.insert(++++++++iter7, 69);
    ASSERT_EQUAL(list7.size(), 6);
    iter7 = list7.begin();
    ASSERT_EQUAL(*iter7, 5);
    ASSERT_EQUAL(*++iter7, 10);
    ASSERT_EQUAL(*++iter7, 69);
    ASSERT_EQUAL(*++iter7, 15);
    ASSERT_EQUAL(*++iter7, 69);
    ASSERT_EQUAL(*++iter7, 20);

    iter7 = list7.end();
    list7.insert(iter7, 69);
    iter7 = list7.begin();
    ASSERT_EQUAL(*iter7, 5);
    ASSERT_EQUAL(*++iter7, 10);
    ASSERT_EQUAL(*++iter7, 69);
    ASSERT_EQUAL(*++iter7, 15);
    ASSERT_EQUAL(*++iter7, 69);
    ASSERT_EQUAL(*++iter7, 20);
    ASSERT_EQUAL(*++iter7, 69);

    List<int> list8;
    List<int>::Iterator iter8 = list8.end();
    list8.insert(iter8, 10);
    iter8 = list8.begin();
    ASSERT_EQUAL(*iter8, 10);
    
}

TEST_MAIN()
