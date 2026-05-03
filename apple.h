#ifndef APPLE_H
#define APPLE_H

class Apple
{
    private:
        int m_x {};
        int m_y {};
    
    public:
        Apple(int x, int y) 
        : m_x {x}
        , m_y {y}
        {}
        int get_x() { return m_x; }
        int get_y() { return m_y; }
        void set_x(int x) { m_x = x; }
        void set_y(int y) { m_y = y; }
};

#endif