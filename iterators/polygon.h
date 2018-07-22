#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <vector>
#include <iostream>

// test program

template<class T>
class Point;

template<class T>
class Edge;

template<class T>
class EdgeIterator;

template<class T>
class Polygon
{
public:
    typedef typename std::vector< Point<T> >::iterator VertexIterator;
    
    VertexIterator BeginVertex()
    {
        return m_points.begin();
    }

    VertexIterator EndVertex()
    {
        return m_points.end();
    }

    EdgeIterator<T> BeginEdge()
    {
        return EdgeIterator<T>(m_points.begin(), m_points.begin());
    }

    EdgeIterator<T> EndEdge()
    {
        return EdgeIterator<T>(m_points.end(), m_points.begin());
    }

    void AddPoint(
        const Point<T>& point
    )
    {
        m_points.emplace_back(point);
    }
private:
    // assuming the points are added in sequence
    std::vector< Point<T> > m_points;
};

template<class T>
class Point
{
public:
    Point(
        T x,
        T y
    ) : m_x(x),
        m_y(y)
    {};

    Point()
    : Point(0, 0)
    {
        std::cout << "Constructing default point" << std::endl;
    };

    T GetX() const
    {
        return m_x;
    }

    T GetY() const
    {
        return m_y;
    }
    
private:
    T m_x, m_y;
};

template<class T>
class EdgeIterator
{
public:
    EdgeIterator(
        const typename std::vector< Point<T> >::iterator& iter,
        const typename std::vector< Point<T> >::iterator& beginIter
    )
    {
        m_currIter = iter;
        m_beginIter = beginIter;
    }
    // support ++ pre-increment
    // support != operator
    // support * operator
private:
    // define state of the iterator
    typename std::vector< Point<T> >::iterator m_currIter;
    std::vector< Point<T> > m_beginIter;
};

template<class T>
class Edge
{
public:
    Edge(
        const Point<T>& p0,
        const Point<T>& p1
    )
    {
        m_edge = std::make_pair(p0, p1);
    }

    std::pair< Point<T>, Point<T> > GetEdge() const
    {
        return m_edge;
    }

private:
    std::pair< Point<T>, Point<T> > m_edge;
};


#endif  // _POLYGON_H_