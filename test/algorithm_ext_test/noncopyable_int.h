#include <boost/noncopyable.hpp>
#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )
namespace {
    // test type which is not copyable by moveable.
    class noncopyable_int : boost::noncopyable {
      private:
        int i;
      public:
        noncopyable_int(int x) : i(x) {}
        noncopyable_int(const noncopyable_int&) = delete;
        noncopyable_int& operator=(const noncopyable_int&) = delete;
        noncopyable_int(noncopyable_int&& o) : i(o.i) {}
        noncopyable_int& operator=(noncopyable_int&& o) { return o; }
        bool operator!=(const noncopyable_int &rhs) { return i != rhs.i; }
        friend std::ostream &operator<<(std::ostream &os, const noncopyable_int& x);
    };

    std::ostream & operator<<(std::ostream &os, const noncopyable_int& x)
    {
       return os << x.i;
    }
}

#endif
