// 弱引用指针在观察者模式中的应用：
#include <iostream> // 包含输入输出流头文件
#include <vector>   // 包含vector容器
#include <memory>   // 包含智能指针
#include <mutex>    // 包含互斥锁

class Resource
{
public:
  Resource() { std::cout << "Resource acquired\n"; }
  ~Resource()
  {
    std::cout << "Resource release\n";
  }
};

void process()
{
  auto res1 = std::make_unique<Resource>();

  auto sharedRes = std::make_shared<Resource>();
  std::vector<std::shared_ptr<Resource>> pool;
  pool.push_back(sharedRes);

  std::weak_ptr<Resource>
      ob = sharedRes;
  if (auto locked = ob.lock())
  {
    std::cout << "Resource still exists\n";
  }
}

// 观察者类
// Observer类继承自std::enable_shared_from_this<Observer>，这样Observer对象在被std::shared_ptr管理时，可以在类的成员函数内部通过shared_from_this()安全地获得指向自身的shared_ptr智能指针。
// 这通常用于需要在对象方法中生成自身的shared_ptr（比如注册到其他地方时），避免因直接用this构造shared_ptr而导致的多重所有权和重复析构问题。
class Observer : public std::enable_shared_from_this<Observer>
{
public:
  void update()
  {
    std::cout << "Observer updated" << std::endl; // 输出提示信息
  }
};

// 被观察者（主题）类
class Subject
{
public:
  // 互斥锁 mutex 的作用是保护 observers 容器的线程安全。
  // 在多线程环境下，可能有多个线程同时调用 addObserver 或 notify 方法，
  // 如果不加锁，可能会导致 observers 容器被同时读写，产生数据竞争和未定义行为。
  // 通过在关键操作前加 std::lock_guard<std::mutex> lock(mutex)，
  // 可以保证同一时刻只有一个线程能修改或遍历 observers，避免并发冲突。
  std::mutex mutex;
  std::vector<std::weak_ptr<Observer>> observers; // 存储观察者的弱引用指针

  // 添加观察者
  void addObserver(const std::shared_ptr<Observer> &observer)
  {
    std::lock_guard<std::mutex> lock(mutex); // 加锁，保证线程安全
    observers.push_back(observer);           // 添加观察者到容器
    // 作用域结束时 lock 被析构，自动释放锁 // 释放锁
  }

  // 通知所有观察者
  void notify()
  {
    std::lock_guard<std::mutex> lock(mutex); // 加锁，保证线程安全
    for (auto it = observers.begin(); it != observers.end();)
    {
      if (it->expired())
      {                           // 如果观察者已失效
        it = observers.erase(it); // 移除失效的观察者
        continue;
      }
      // it->lock() 的作用是尝试将 weak_ptr 升级为 shared_ptr。
      // 如果原对象还存在（即没有被销毁），lock() 返回一个有效的 shared_ptr，可以安全访问对象；
      // 如果原对象已被销毁，lock() 返回空指针（nullptr）。
      // lock是智能指针的成员函数，mutex是互斥锁的成员函数。
      if (auto obs = it->lock())
      {                // 获取有效的 shared_ptr
        obs->update(); // 调用观察者的 update 方法
      }
      ++it;
    }
    // 作用域结束时 lock 被析构，自动释放锁 // 释放锁
  }
};

void test()
{
  Subject subject; // 创建主题对象

  // 创建一个 shared_ptr<Observer>，并注册到主题
  std::shared_ptr<Observer> observer = std::make_shared<Observer>();
  subject.addObserver(observer); // 添加观察者

  subject.notify(); // 通知所有观察者

  observer.reset(); // 手动释放 observer，模拟观察者被销毁

  subject.notify(); // 再次通知，已失效的观察者不会被调用
}

int main()
{
  test();
  process();
  return 0;
}