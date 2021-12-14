/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 23:08:20 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/12/14 23:08:58 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{
	template < class T1, class T2 > struct pair {
		public:
			T1 first;	
			T2 second;
			pair() : first(), second() {}
			pair ( const pair<T1, T2>& pai ) : first(pai.first), second(pai.second) {}

			pair ( const T1 &a, const T2 &b ) : first(a), second(b) {}

			pair& operator= ( const pair& pai )
			{
				if (this != &pai)
				{
					this->first = pai.first;
					this->second = pai.second;
				}
				return *this;
			}
			~pair() {}

			template <class T1, class T2>
			bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{ return lhs.first==rhs.first && lhs.second==rhs.second; }

			template <class T1, class T2>
			bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{ return !(lhs==rhs); }

			template <class T1, class T2>
			bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

			template <class T1, class T2>
			bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{ return !(rhs<lhs); }

			template <class T1, class T2>
			bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{ return rhs<lhs; }

			template <class T1, class T2>
			bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{ return !(lhs<rhs); }
	};

	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return ( pair<T1,T2>(x,y) );
	}

}