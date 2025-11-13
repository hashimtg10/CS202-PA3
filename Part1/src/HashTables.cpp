#include "HashTables.h"

// =======================
// Constructor
// =======================
template <typename T>
HashTable<T>::HashTable(CollisionHandle strategy)
{
    collision_strategy = strategy;
    this->table_size = 20;
    this->num_elements = 0;
    this->loadFactor = 0.0;
    this->loadFactorThreshold = 0.85;
    if (strategy == LINEAR_PROBING || strategy == QUADRATIC_PROBING)
    {
        this->probing_table = new KeyValuePair[this->table_size];
    }
    else
    {
        this->chaining_table.resize(this->table_size);
    }
}

// =======================
// Destructor
// =======================
template <typename T>
HashTable<T>::~HashTable()
{
    if (this->collision_strategy == LINEAR_PROBING || this->collision_strategy == QUADRATIC_PROBING)
    {
        if (this->table_size > 0)
        {
            delete[] this->probing_table;
        }
    }
}

// =======================
// Load Factor Calculation
// =======================
template <typename T>
void HashTable<T>::calculateLoadFactor()
{
    this->loadFactor = this->num_elements / this->table_size;
}

// =======================
// Linear Probing Methods
// =======================
template <typename T>
void HashTable<T>::insertLinearProbing(int key, T value)
{
    int idx = this->hashFunction1(key);
    while (!this->probing_table[idx].isEmpty)
    {
        idx++;
        idx %= this->table_size;
    }
    this->probing_table[idx] = KeyValuePair(key, value, false);
    this->num_elements++;
    this->calculateLoadFactor();
    if (this->loadFactor > this->loadFactorThreshold)
    {
        this->resizeAndRehash();
    }
}
template <typename T>
T HashTable<T>::searchLinearProbing(int key)
{
    int idx = this->hashFunction1(key);
    while (!this->probing_table[idx].isEmpty)
    {
        if (this->probing_table[idx].key == key)
        {
            return this->probing_table[idx].value;
        }
        idx++;
    }
    return this->probing_table[idx].value;
}

template <typename T>
void HashTable<T>::removeLinearProbing(int key)
{   
    int idx = this->hashFunction1(key);
    for(int i = 0; i < this->table_size; i++)
    {
        if (this->probing_table[idx].key == key)
        {
            KeyValuePair temp;
            this->probing_table[idx]  = temp;
            this->num_elements--;
            this->calculateLoadFactor();
            return;
        }
        idx++;
        idx = idx%this->table_size;
    }
}

// =======================
// Quadratic Probing Methods
// =======================
template <typename T>
void HashTable<T>::insertQuadraticProbing(int key, T value)
{
}

template <typename T>
T HashTable<T>::searchQuadraticProbing(int key)
{
    return T();
}

template <typename T>
void HashTable<T>::removeQuadraticProbing(int key)
{
}

// =======================
// Separate Chaining Methods
// =======================
template <typename T>
void HashTable<T>::insertSeparateChaining(int key, T value)
{
}

template <typename T>
T HashTable<T>::searchSeparateChaining(int key)
{
    return T();
}

template <typename T>
void HashTable<T>::removeSeparateChaining(int key)
{
}

template <typename T>
void HashTable<T>::resizeAndRehash()
{  
    if (this->collision_strategy == LINEAR_PROBING)
    {
        KeyValuePair* old_table = this->probing_table;
        int old_size = this->table_size;
        this->probing_table = new KeyValuePair[this->table_size * 2];
        this->num_elements = 0;
        this->table_size *= 2;
        for (int i = 0; i < old_size; i++)
        {
            if (!old_table[i].isEmpty)
            {
                this->insert(old_table[i].key, old_table[i].value);
            }
        }
        delete[] old_table;

        this->calculateLoadFactor();
    }
    else if(this->collision_strategy == QUADRATIC_PROBING)
    {

    }
    else if(this->collision_strategy == SEPARATE_CHAINING)
    {

    }
}

// =======================
// Insert
// =======================
template <typename T>
void HashTable<T>::insert(int key, T value)
{
    switch (collision_strategy)
    {
    case LINEAR_PROBING:
        insertLinearProbing(key, value);
        break;
    case QUADRATIC_PROBING:
        insertQuadraticProbing(key, value);
        break;
    case SEPARATE_CHAINING:
        insertSeparateChaining(key, value);
        break;
    }
    calculateLoadFactor();
}

// =======================
// Search
// =======================
template <typename T>
T HashTable<T>::search(int key)
{
    switch (collision_strategy)
    {
    case LINEAR_PROBING:
        return searchLinearProbing(key);
    case QUADRATIC_PROBING:
        return searchQuadraticProbing(key);
    case SEPARATE_CHAINING:
        return searchSeparateChaining(key);
    }
    return T(); // Default return
}

// =======================
// Remove
// =======================
template <typename T>
void HashTable<T>::remove(int key)
{
    switch (collision_strategy)
    {
    case LINEAR_PROBING:
        removeLinearProbing(key);
        break;
    case QUADRATIC_PROBING:
        removeQuadraticProbing(key);
        break;
    case SEPARATE_CHAINING:
        removeSeparateChaining(key);
        break;
    }
    calculateLoadFactor();
}

// Please use this for debugging help
template <typename T>
void HashTable<T>::displayProbingTable()
{
    cout << "Current Table (size: " << table_size << "):\n";
    for (int i = 0; i < table_size; i++)
    {
        if (!probing_table[i].isEmpty)
            cout << "[" << i << "] -> Key: " << probing_table[i].key << ", Value: " << probing_table[i].value << endl;
        else
            cout << "[" << i << "] -> EMPTY\n";
    }
}

template class HashTable<int>;
template class HashTable<string>;