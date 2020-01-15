//
// Created by Aliaksandr Sharstniou.
//
#include <iostream>

template <class K, class V>
struct OpenHashDictionary
{
public:
    OpenHashDictionary(int capacity = 10)
        : _capacity(capacity)
    {
        assert(capacity > 0);
        _buckets = new Item*[capacity];
        for (int i = 0; i < _capacity; i++) { _buckets[i] = nullptr; }
    };

    ~OpenHashDictionary()
    {
        for (int i = 0; i < _capacity; i++) { _Clear(_buckets[i]); }
        delete[] _buckets;
    };

    void Insert(const K& key, V&& value)
    {
        int index = _Hash(key);
        if (_buckets[index] != nullptr)
        {
            Item* existingItem = _FindItemByKey(index, key);
            if (existingItem != nullptr)
            {
                existingItem->value = value;
                return;
            }
        }

        auto* newItem = new Item();
        newItem->key = key;
        newItem->value = value;
        if (_buckets[index] != nullptr) { newItem->next = _buckets[index]; }
        _buckets[index] = newItem;
    };

    bool Find(const K& key, V& value)
    {
        bool found = false;
        int index = _Hash(key);
        if (_buckets[index] != nullptr)
        {
            Item* item = _FindItemByKey(index, key);
            if (item != nullptr)
            {
                value = item->value;
                found = true;
            }
        }

        return found;
    };

    bool Remove(const K& key)
    {
        bool removed = false;
        int index = _Hash(key);
        if (_buckets[index] != nullptr)
        {
            bool found = false;
            Item* prevItem = nullptr;
            Item* item = _buckets[index];
            while (item != nullptr)
            {
                if (item->key == key)
                {
                    found = true;
                    break;
                }
                prevItem = item;
                item = item->next;
            }

            if (found)
            {
                if (prevItem == nullptr) { _buckets[index] = item->next; }
                else { prevItem->next = item->next; }
                delete item;
            }
        }

        return removed;
    };

    void Print() const
    {
        for (int i = 0; i < _capacity; ++i)
        {
            if (_buckets[i] != nullptr)
            {
                Item* item = _buckets[i];
                while (item != nullptr)
                {
                    std::cout << item->key << ": " << item->value << "\n";
                    item = item->next;
                }
            }
        }
    };

private:
    struct Item
    {
        K key;
        V value;
        Item* next;
    };

    void _Clear(Item* head)
    {
        Item* item = head;
        while (item != nullptr)
        {
            Item* itemToDelete = item;
            item = item->next;
            delete itemToDelete;
        }
    };

    Item* _FindItemByKey(int index, const K& key)
    {
        Item* result = nullptr;
        Item* item = _buckets[index];
        while (item != nullptr)
        {
            if (item->key == key)
            {
                result = item;
                break;
            }
            item = item->next;
        }

        return result;
    };

    int _Hash(const K& key)
    {
        int s = 0;
        for (int i = 0; i < key.size(); ++i) { s += static_cast<int>(key[i]); }
        return s % _capacity;
    };

    int _capacity;
    Item** _buckets;
};

int main()
{
    std::cout << "Lab 02\n\n";

    OpenHashDictionary<std::string, std::string> d;
    d.Insert(std::string("Test_100"), std::string("100"));
    d.Insert(std::string("Test_101"), std::string("101"));
    d.Insert(std::string("Test_102"), std::string("102"));
    d.Insert(std::string("Test_110"), std::string("110"));
    d.Insert(std::string("Test_111"), std::string("111"));
    d.Insert(std::string("Test_120"), std::string("120"));

    std::cout << "Dictionary values: \n";
    d.Print();
    std::cout << "\n";

    d.Remove(std::string("Test_101"));
    std::cout << "Dictionary values after remove 'Test_101': \n";
    d.Print();
    std::cout << "\n";

    std::string exist("Test_110");
    std::string missing("Missing");
    std::string value;
    if (d.Find(exist, value)) { std::cout << "Dictionary found value '" << value << "' for key '" << exist << "'\n"; }
    if (!d.Find(missing, value)) { std::cout << "Dictionary not found any value for key '" << missing << "'\n"; }

    return 0;
}