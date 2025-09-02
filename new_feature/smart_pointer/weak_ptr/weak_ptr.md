# weak_ptr 实现示例

回到[主文档 weak_ptr](../../../README.md#313-weak_ptr)

```cpp
// 控制块结构（简化版）
template <typename T>
struct ControlBlock {
    int strong_count;  // 强引用计数
    int weak_count;    // 弱引用计数
    T* object;         // 指向实际对象
    // ... 其他成员（删除器等）
};

// weak_ptr 简化实现
template <typename T>
class weak_ptr {
private:
    ControlBlock<T>* cb;  // 指向控制块

public:
    // 从 shared_ptr 构造
    weak_ptr(const shared_ptr<T>& sp) : cb(sp.cb) {
        if (cb) cb->weak_count++;  // 弱引用计数+1
    }

    // 转换为 shared_ptr（lock() 方法）
    shared_ptr<T> lock() const {
        if (cb && cb->strong_count > 0) {
            // 对象存活，返回 shared_ptr 并增加强引用计数
            return shared_ptr<T>(cb);
        }
        return shared_ptr<T>();  // 对象已销毁，返回空
    }

    // 析构函数
    ~weak_ptr() {
        if (cb) {
            cb->weak_count--;
            if (cb->weak_count == 0 && cb->strong_count == 0) {
                delete cb;  // 弱引用计数为0且对象已销毁，释放控制块
            }
        }
    }
};
```
回到[主文档 weak_ptr](../../../README.md#313-weak_ptr)