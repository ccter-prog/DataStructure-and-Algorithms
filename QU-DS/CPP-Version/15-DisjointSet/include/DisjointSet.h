#pragma once

#include <cstddef>
#include <map>
#include <memory>
#include <new>
#include <optional>
#include <print>
#include <utility>

template <typename T>
class DisjointSet
{
    public:
        // 特殊函数
        DisjointSet(std::size_t capacity = 0);
        DisjointSet(const DisjointSet& obj);
        DisjointSet(DisjointSet&& obj) noexcept;
    public:
        class Iterator
        {
            public:
                friend class DisjointSet;
            public:
                Iterator& operator++();
                T& operator*() const;
                bool operator!=(const Iterator& obj) const;
                bool operator==(const Iterator& obj) const;
            public:
                explicit Iterator(T* data);
            private:
                T* ptr;
        };
    public:
        Iterator begin() const;
        Iterator end() const;
    public:
        DisjointSet& operator=(const DisjointSet& obj);
        DisjointSet& operator=(DisjointSet&& obj) noexcept;
    public:
        bool insert(const T& value);
        void print() const;
        std::optional<std::size_t> find(const T& value);
        bool union_set(const T& value1, const T& value2);
        bool connected(const T& value1, const T& value2);
        bool grow(const std::size_t new_capacity = 0);
        std::size_t get_size() const;
        std::size_t get_capacity() const;
    private:
        std::unique_ptr<T[]> m_data;
        std::unique_ptr<std::size_t[]> m_parent;
        std::map<T, std::size_t> m_map;
        std::unique_ptr<std::size_t[]> m_tree_size;
        std::size_t m_capacity;
        std::size_t m_size;
};

// 构造函数：初始化指定容量的并查集
// 设计思路：预分配内存避免频繁扩容，所有数组大小设为capacity+1(索引0留空)
template <typename T>
inline DisjointSet<T>::DisjointSet(std::size_t capacity)
    : m_data(new (std::nothrow) T[capacity + 1]),
      m_parent(new (std::nothrow) std::size_t[capacity + 1]),
      m_tree_size(new (std::nothrow) std::size_t[capacity + 1]), m_capacity(0), m_size(0)
{
    // 检查内存分配是否成功：三个数组必须同时成功或同时失败
    // 如果任何一个分配失败，保持m_capacity=0表示未初始化状态
    if (m_data && m_parent && m_tree_size)
    {
        m_capacity = capacity;
    }
}

// 深拷贝整个并查集状态
// 完整复制三个数组和map
template <typename T>
inline DisjointSet<T>::DisjointSet(const DisjointSet<T>& obj)
    : m_data(new (std::nothrow) T[obj.m_capacity + 1]),
      m_parent(new (std::nothrow) std::size_t[obj.m_capacity + 1]), m_map(obj.m_map),
      m_tree_size(new (std::nothrow) std::size_t[obj.m_capacity + 1]), m_capacity(obj.m_capacity),
      m_size(obj.m_size)
{
    // 如果内存分配失败，将容量和大小置为0，防止后续访问无效内存
    // 注意：此时m_map已经通过初始化列表完成拷贝，但数组指针可能为空
    if (!m_data || !m_parent || !m_tree_size)
    {
        m_capacity = 0;
        m_size = 0;
        return;
    }
    // 只复制有效数据范围[1, m_size]，不复制未使用的空间
    // 这是因为m_size记录了实际插入的元素数量，后面的空间是预留的但未使用
    for (std::size_t i = 1; i <= m_size; ++i)
    {
        m_data[i] = obj.m_data[i];
        m_parent[i] = obj.m_parent[i];
        m_tree_size[i] = obj.m_tree_size[i];
    }
}

// 移动构造函数：转移资源所有权，避免深拷贝开销
// 设计思路：利用unique_ptr的移动语义，O(1)时间复杂度
template <typename T>
inline DisjointSet<T>::DisjointSet(DisjointSet<T>&& obj) noexcept
    : m_data(std::move(obj.m_data)), m_parent(std::move(obj.m_parent)), m_map(std::move(obj.m_map)),
      m_tree_size(std::move(obj.m_tree_size)), m_capacity(obj.m_capacity), m_size(obj.m_size)
{
    // 清空源对象状态，防止析构时重复释放内存
    // unique_ptr移动后源对象自动变为nullptr，但m_capacity和m_size需要手动清零
    obj.m_capacity = 0;
    obj.m_size = 0;
}

template <typename T>
inline DisjointSet<T>::Iterator::Iterator(T* data) : ptr(data)
{
}

// 前置递增运算符：移动到下一个元素
// 直接指针算术运算，不需要边界检查，因为迭代器的有效性由使用者保证
template <typename T>
inline DisjointSet<T>::Iterator& DisjointSet<T>::Iterator::operator++()
{
    ++ptr;
    return *this;
}

// 解引用运算符：获取当前元素值
// 不进行nullptr检查，因为迭代器在使用前应该已经通过!=end()验证过有效性
template <typename T>
inline T& DisjointSet<T>::Iterator::operator*() const
{
    return *ptr;
}

// 不等比较运算符：用于循环终止判断
template <typename T>
inline bool DisjointSet<T>::Iterator::operator!=(const DisjointSet<T>::Iterator& obj) const
{
    return ptr != obj.ptr;
}

// 相等比较运算符
template <typename T>
inline bool DisjointSet<T>::Iterator::operator==(const DisjointSet<T>::Iterator& obj) const
{
    return ptr == obj.ptr;
}

// begin(): 返回指向第一个元素的迭代器
// 注意：m_data[0]未使用，因此从m_data+1开始
// 不需要检查m_data是否为nullptr，因为begin()通常在确认容器非空后调用
template <typename T>
inline DisjointSet<T>::Iterator DisjointSet<T>::begin() const
{
    return Iterator(m_data.get() + 1);
}

// end(): 返回指向末尾后一位的迭代器
// 设计思路：遵循STL惯例，end()指向最后一个元素的下一位
// 即使容器为空(m_size=0)，end()也会指向m_data+1，与begin()相等
template <typename T>
inline DisjointSet<T>::Iterator DisjointSet<T>::end() const
{
    return Iterator(m_data.get() + m_size + 1);
}

// 先创建临时副本再交换，保证异常安全
// copy-and-swap惯用法，即使分配失败也不会破坏原对象
template <typename T>
inline DisjointSet<T>& DisjointSet<T>::operator=(const DisjointSet<T>& obj)
{
    // 自赋值检查：防止将自己赋值给自己导致数据丢失
    if (this == &obj)
    {
        return *this;
    }
    // 先分配新内存，失败则返回原对象（不修改任何状态）
    // 这种策略保证了强异常安全：要么完全成功，要么完全不改变
    std::unique_ptr<T[]> temp_data(new (std::nothrow) T[obj.m_capacity + 1]);
    std::unique_ptr<std::size_t[]> temp_parent(new (std::nothrow) std::size_t[obj.m_capacity + 1]);
    std::unique_ptr<std::size_t[]> temp_tree_size(new (std::nothrow)
                                                      std::size_t[obj.m_capacity + 1]);
    if (!temp_data || !temp_parent || !temp_tree_size)
    {
        return *this;
    }
    // 复制数据：只复制有效范围[1, obj.m_size]
    for (std::size_t i = 1; i <= obj.m_size; ++i)
    {
        temp_data[i] = obj.m_data[i];
        temp_parent[i] = obj.m_parent[i];
        temp_tree_size[i] = obj.m_tree_size[i];
    }
    // 移动赋值：原子性替换所有成员
    // 此时temp_*持有旧内存，移动后自动释放，不会泄漏
    m_map = obj.m_map;
    m_data = std::move(temp_data);
    m_parent = std::move(temp_parent);
    m_tree_size = std::move(temp_tree_size);
    m_capacity = obj.m_capacity;
    m_size = obj.m_size;
    return *this;
}

// 移动赋值运算符：转移资源，高效
template <typename T>
inline DisjointSet<T>& DisjointSet<T>::operator=(DisjointSet<T>&& obj) noexcept
{
    // 自赋值检查：虽然移动赋值通常不需要，但防御性编程避免意外
    if (this == &obj)
    {
        return *this;
    }
    // 移动所有成员变量：unique_ptr移动后源对象自动变为nullptr
    m_data = std::move(obj.m_data);
    m_parent = std::move(obj.m_parent);
    m_map = std::move(obj.m_map);
    m_tree_size = std::move(obj.m_tree_size);
    m_capacity = obj.m_capacity;
    m_size = obj.m_size;
    // 清空源对象，防止析构时访问已移动的内存
    obj.m_capacity = 0;
    obj.m_size = 0;
    return *this;
}

// insert: 插入新元素，初始时每个元素自成一个集合
// 设计思路：
// 1. 检查容量，不足则自动扩容
// 2. 将新元素添加到数组末尾(m_size+1位置)
// 3. 初始化parent为0(自己是根节点)
// 4. 初始化tree_size为1(单节点树)
// 5. 建立值到索引的映射
template <typename T>
inline bool DisjointSet<T>::insert(const T& value)
{
    // 容量检查：满则扩容
    // 如果grow()失败返回false，insert也返回false，保证不会越界写入
    if (m_size == m_capacity)
    {
        if (!grow())
        {
            return false;
        }
    }
    // 执行到这里说明：要么有足够容量，要么grow()成功扩容
    // 因此可以直接使用m_size+1作为索引，不会越界
    ++m_size;
    m_data[m_size] = value;
    m_parent[m_size] = 0;     // 0表示根节点(无父节点)
    m_tree_size[m_size] = 1;  // 初始树大小为1
    m_map[value] = m_size;    // 建立双向映射
    return true;
}

// print: 调试辅助函数，可视化并查集内部状态
// 输出三行：索引、父节点值、元素值
template <typename T>
inline void DisjointSet<T>::print() const
{
    // 遍历有效范围[1, m_size]打印索引
    for (std::size_t i = 1; i <= m_size; ++i)
    {
        std::print("{}\t", i);
    }
    std::println();
    // 打印对应的父节点值
    for (std::size_t i = 1; i <= m_size; ++i)
    {
        std::print("{}\t", m_parent[i]);
    }
    std::println();
    // 使用迭代器打印元素值，展示三种视图的对应关系
    for (const auto& i : *this)
    {
        std::print("{}\t", i);
    }
    std::println();
}

// find: 查找元素的根节点，带路径压缩(Path Compression)优化
// 算法流程：
// 1. 通过map找到元素索引
// 2. 沿parent指针向上追溯到根节点(parent[i]==0)
// 3. 路径压缩：将查找路径上的所有节点直接连接到根节点
// 实现细节：
// - 第一次while循环：找到根节点
// - 第二次while循环：回溯时将路径上节点直接连到根
template <typename T>
inline std::optional<std::size_t> DisjointSet<T>::find(const T& value)
{
    // 元素不存在于map中，说明从未insert过，返回nullopt
    // 这里必须先检查，因为后续要用m_map[value]获取索引
    if (m_map.find(value) == m_map.end())
    {
        return std::nullopt;
    }

    // 执行到这里说明value一定在map中，可以安全访问m_map[value]
    std::size_t i = m_map[value];

    // 已是根节点，直接返回
    // parent[i]==0表示没有父节点，即自己是根
    if (m_parent[i] == 0)
    {
        return i;
    }

    // 保存起始位置，用于后续路径压缩
    // tmp记录原始节点，之后要从tmp开始向上压缩路径
    std::size_t tmp = i;

    // 第一阶段：向上追溯找到根节点
    // 循环条件m_parent[i]>0：只要还有父节点就继续向上
    // 循环结束时i指向根节点（其parent值为0）
    while (m_parent[i] > 0)
    {
        i = m_parent[i];
    }
    // 此时i指向根节点

    // 第二阶段：路径压缩，将tmp到根路径上的所有节点直接连到根
    // 从原始节点tmp开始，沿着原来的parent链向上遍历
    // 将每个节点的parent直接设置为根节点i
    while (m_parent[tmp] > 0)
    {
        std::size_t tmp2 = tmp;  // 保存当前节点
        tmp = m_parent[tmp];     // 移动到父节点
        m_parent[tmp2] = i;      // 将原节点的parent直接指向根，跳过中间节点
    }
    // 路径压缩完成后，tmp到根之间的所有节点都直接连接到根
    // 下次查找这些节点时只需一步就能到达根

    return i;
}

// 合并策略：
// - 比较两棵树的size，将小树挂到大树下
// - 更新大树的size为两树size之和
template <typename T>
inline bool DisjointSet<T>::union_set(const T& value1, const T& value2)
{
    // 查找两个元素的根节点
    // find()已经处理了元素不存在的情况（返回nullopt）
    std::optional<std::size_t> find_value1(find(value1));
    std::optional<std::size_t> find_value2(find(value2));

    // 任一元素不存在，合并失败
    // has_value()检查确保两个元素都在并查集中
    if (!find_value1.has_value() || !find_value2.has_value())
    {
        return false;
    }

    // 已在同一集合，无需合并
    // 根节点相同说明已经在同一个集合中，直接返回true表示"已成功连接"
    if (*find_value1 == *find_value2)
    {
        return true;
    }

    // 执行到这里说明：两个元素都存在且在不同集合中
    // 可以安全解引用find_value1和find_value2进行合并操作

    // 按树的大小合并：小树挂到大树下
    // 比较两棵树的大小，决定谁作为子树
    if (m_tree_size[*find_value1] < m_tree_size[*find_value2])
    {
        // value1的树更小，将其根节点挂到value2的根节点下
        // 这样做的目的是保持树的平衡，避免大树成为小树的子树导致深度增加
        m_parent[*find_value1] = *find_value2;
        m_tree_size[*find_value2] = m_tree_size[*find_value2] + m_tree_size[*find_value1];
    }
    else
    {
        // value2的树更小或相等，将其根节点挂到value1的根节点下
        // 相等情况任意选择，这里统一让value2成为子树
        m_parent[*find_value2] = *find_value1;
        m_tree_size[*find_value1] = m_tree_size[*find_value1] + m_tree_size[*find_value2];
    }

    return true;
}

// connected: 判断两个元素是否连通(在同一集合中)
// 实现：分别查找根节点，比较是否相同
// 时间复杂度：两次find操作，摊还O(α(n))
template <typename T>
inline bool DisjointSet<T>::connected(const T& value1, const T& value2)
{
    // 分别查找两个元素的根节点
    // find()可能返回nullopt（元素不存在），需要用optional接收
    std::optional<std::size_t> a(find(value1));
    std::optional<std::size_t> b(find(value2));

    // 任一元素不存在，视为不连通
    // 必须在解引用前检查has_value()，否则对nullopt解引用会导致未定义行为
    if (!a.has_value() || !b.has_value())
    {
        return false;
    }

    // 执行到这里说明两个元素都存在
    // 比较它们的根节点是否相同：相同则在同一集合，不同则在不同集合
    return *a == *b;
}

// grow: 动态扩容机制
// 扩容策略：
// 1. 若指定new_capacity且大于当前容量，按指定值扩容
// 2. 若new_capacity小于当前容量，拒绝操作(不支持缩容)
// 3. 若new_capacity等于当前容量或未指定，则翻倍扩容
template <typename T>
inline bool DisjointSet<T>::grow(const std::size_t new_capacity)
{
    std::size_t new_alloc;

    if (new_capacity > m_capacity)
    {
        // 按指定值扩容：用户明确要求更大的容量
        new_alloc = new_capacity;
    }
    else if (new_capacity < m_capacity)
    {
        // 不支持缩容：返回false表示操作被拒绝
        return false;
    }
    else
    {
        // 默认翻倍策略，初始容量为0时设为1*2=2
        // new_capacity==m_capacity时触发自动扩容（通常是insert时发现容量不足）
        new_alloc = m_capacity == 0 ? (m_capacity + 1) * 2 : m_capacity * 2;
    }

    // 分配新内存：使用nothrow版本，失败返回nullptr而非抛出异常
    // 三个数组必须同时成功，任何一个失败都要回滚
    std::unique_ptr<T[]> temp_data(new (std::nothrow) T[new_alloc]);
    std::unique_ptr<std::size_t[]> temp_parent(new (std::nothrow) std::size_t[new_alloc]);
    std::unique_ptr<std::size_t[]> temp_tree_size(new (std::nothrow) std::size_t[new_alloc]);

    if (!temp_data || !temp_parent || !temp_tree_size)
    {
        // 任一分配失败，返回false
        // 此时原对象未被修改，保持原状，保证异常安全
        return false;
    }

    // 复制现有数据(保持索引不变)
    // 只复制[1, m_size]范围内的有效数据，新分配的空间保持未初始化状态
    for (std::size_t i = 1; i <= m_size; ++i)
    {
        temp_data[i] = m_data[i];
        temp_parent[i] = m_parent[i];
        temp_tree_size[i] = m_tree_size[i];
    }
    m_data = std::move(temp_data);
    m_parent = std::move(temp_parent);
    m_tree_size = std::move(temp_tree_size);
    m_capacity = new_alloc;
    return true;
}

// 获取当前元素数量
template <typename T>
inline std::size_t DisjointSet<T>::get_size() const
{
    return m_size;
}

// 获取总容量
template <typename T>
inline std::size_t DisjointSet<T>::get_capacity() const
{
    return m_capacity;
}
