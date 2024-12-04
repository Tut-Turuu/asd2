#include <cstring>


namespace my {

    template <typename T>
    class stack {
        int sz;
        int cap;
        T* data;
    public:
        stack(): sz(0), cap(0), data(0) {}

        ~stack() {
            delete[] data;
        }

        void reserve(int new_cap) {
            if (cap > new_cap) return;

            T* new_data = new T[new_cap]; 

            if (data != nullptr) memcpy(new_data, data, sizeof(T)*sz);

            data = new_data;

            cap = new_cap;
        }


        void push_back(const T& el) noexcept {
            if (sz == cap) reserve(cap*2 + 1);
            new(data + sz) T(el);
            ++sz;
        }

        void push_back(T&& el) noexcept {
            if (sz == cap) reserve(cap*2 + 1);
            new(data + sz) T(el);
            ++sz; 
        }

        T pop_back() noexcept {
            
            return data[--sz];
        }

        T& operator[](int ind) const noexcept{
            return data[ind];
        }

        T& last() {
            return data[sz-1];
        }

        int size() {return sz;}
    };
}




bool s_is_valid(std::string& s) {
    my::stack<char> stack;
    for (auto ch : s) {
        if (ch == '{' || ch == '[' || ch == '(') {
            stack.push_back(ch);
        } else if (ch == '}' || ch == ']' || ch == ')') {
            if (stack.size() == 0) {
                return false;
            } else {
                switch (ch) {
                    case '}':
                        if (stack.last() == '{') {
                            stack.pop_back();
                            break;
                        } else {
                            return false;
                        }
                        break;
                    case ']':
                        if (stack.last() == '[') {
                            stack.pop_back();
                            break;
                        } else {
                            return false;
                        }
                        break;
                    case ')':
                        if (stack.last() == '(') {
                            stack.pop_back();
                            break;
                        } else {
                            return false;
                        }
                        break;
                }
            }
        }
    }
    return true;
}