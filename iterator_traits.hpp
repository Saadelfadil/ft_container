#pragma once
#include <iostream>
#include <string>

#include <vector>
template <class Iter>
class iterator_traits
{
    private:
        typedef typename Iter::iterator_category iterator_category;
        typedef typename Iter::value_type value_type;
        typedef typename Iter::difference_type difference_type;
        typedef          difference_type Iter::distance_type;
        typedef typename Iter::pointer pointer;
        typedef typename Iter::reference reference;

};

