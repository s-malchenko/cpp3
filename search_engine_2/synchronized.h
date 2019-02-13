#include <mutex>
using namespace std;

template <typename T>
class Synchronized
{
public:
    explicit Synchronized(T initial = T())
    {
        value = initial;
    }

    struct Access
    {
    public:
        Access(mutex &m, T &value) : guard(lock_guard<mutex>(m)), ref_to_value(value)
        {
        }

        T &ref_to_value;
    private:
        lock_guard<mutex> guard;
    };

    Access GetAccess()
    {
        return Access(m, value);
    }

private:
    T value;
    mutex m;
};