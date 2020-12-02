/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 17:10:37 by rofernan          #+#    #+#             */
/*   Updated: 2020/11/27 17:10:40 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <limits>
# include <memory>
# include "../Iterator/RandomAccessIterator.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T>>
	class vector
	{
		public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
		typedef RandomAccessIterator<T> iterator;
		typedef RandomAccessIterator<const T> const_iterator;
		typedef ReverseRandomAccess<T> reverse_iterator;
		typedef ReverseRandomAccess<const T> const_reverse_iterator;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;

		/* Member functions */
		vector() {
			_vec = nullptr;
			_size = 0;
			_cap = 0;
		};
		vector(size_type n, const value_type &val = value_type()) {
			_vec = nullptr;
			_vec = _alloc.allocate(n);
			_size = 0;
			_cap = n;
			assign(n, val);
		};
		vector(iterator first, iterator last) {
			difference_type n = last - first;
			_vec = nullptr;
			_vec = _alloc.allocate(n);
			_size = 0;
			_cap = n;
			assign(first, last);
		};
		vector(const vector &x) {
			_vec = nullptr;
			_vec = _alloc.allocate(x._cap);
			_size = 0;
			_cap = x._cap;
			assign(x.begin(), x.end());
		};
		~vector() {
			_alloc.deallocate(_vec, _cap);
		};
		vector	&operator=(const vector &x) {
			if (this != &x)
			{
				_alloc.deallocate(_vec, _cap);
				_vec = _alloc.allocate(x._cap);
				_size = 0;
				_cap = x._cap;
				assign(x.begin(), x.end());
			}
			return (*this);
		};

		/* Iterators */
		iterator				begin() {
			return (iterator(_vec));
		};
		const_iterator			begin() const {
			return (const_iterator(_vec));
		};
		iterator				end() {
			return (iterator(_vec + _size));
		};
		const_iterator			end() const {
			return (const_iterator(_vec + _size));
		};
		reverse_iterator		rbegin() {
			return (reverse_iterator(_vec + _size - 1));
		};
		const_reverse_iterator	rbegin() const {
			return (const_reverse_iterator(_vec + _size - 1));
		};
		reverse_iterator		rend() {
			return (reverse_iterator(_vec - 1));
		};
		const_reverse_iterator	rend() const {
			return (const_reverse_iterator(_vec - 1));
		};

		/* Capacity */
		size_type	size() const {
			return (_size);
		};
		size_type	max_size() const {
			return (std::numeric_limits<size_type>::max() / sizeof(value_type));
		};
		void		resize(size_type n, value_type val = value_type()) {
			if (n < _size)
			{
				value_type *tmp;
				tmp = _alloc.allocate(n);
				for (size_t i = 0; i < n; i++)
					tmp[i] = _vec[i];
				clear();
				_vec = tmp;
				_size = n;
				_cap = n;
			}
			else if (n > _size)
			{
				reserve(n);
				for (size_t i = _size; i < n; i++)
					push_back(val);
			}
		};
		size_type	capacity() const {
			return (_cap);
		};
		bool		empty() const {
			return (_size == 0);
		};
		void		reserve (size_type n) {
			value_type	*tmp;

			if (n > max_size())
				throw (std::length_error("new capacity (which is " + std::to_string(n) \
				+ ") > max_size() (which is " + std::to_string(max_size()) + ")"));
			if (n > _cap)
			{
				tmp = _alloc.allocate(n);
				for (size_t i = 0; i < _size; i++)
					tmp[i] = _vec[i];
				_alloc.deallocate(_vec, _cap);
				_cap = n;
				_vec = tmp;
			}
		};

		/* Element access */
		reference		operator[](size_type n) {
			return (_vec[n]);
		};
		const_reference	operator[](size_type n) const {
			return (_vec[n]);
		};
		reference		at (size_type n) {
			if (n >= _size)
				throw (std::out_of_range("range_check: n (which is " + std::to_string(n) \
				+ ") >= this->size() (which is " + std::to_string(_size) + ")"));
			return (_vec[n]);
		};
		const_reference	at(size_type n) const {
			if (n >= _size)
				throw (std::out_of_range("range_check: n (which is " + std::to_string(n) \
				+ ") >= this->size() (which is " + std::to_string(_size) + ")"));
			return (_vec[n]);
		};
		reference		front() {
			return (_vec[0]);
		};
		const_reference	front() const {
			return (_vec[0]);
		};
		reference		back() {
			return (_vec[_size - 1]);
		};
		const_reference	back() const {
			return (_vec[_size - 1]);
		};

		/* Modifiers */
		void		assign(iterator first, iterator last) {
			if (!empty())
				clear();
			while (first != last)
			{
				push_back(*first);
				first++;
			}
		};
		void		assign(const_iterator first, const_iterator last) {
			if (!empty())
				clear();
			while (first != last)
			{
				push_back(*first);
				first++;
			}
		};
		void		assign(size_type n, const value_type &val) {
			if (!empty())
				clear();
			for (size_type i = 0; i < n; i++)
				push_back(val);
		};
		void		push_back(const value_type &val) {
			if (_vec == nullptr || _cap <= _size + 1)
				reserve(_size + 1);
			_vec[_size] = val;
			_size++;
		};
		void		pop_back() {
			erase(end() - 1);
		};
		iterator	insert(iterator position, const value_type &val) {
			difference_type pos = position - begin();

			if (_cap <= _size + 1)
				reserve(_size + 1);
			_size++;
			for (size_t i = _size - 1; i > (size_t)pos; i--)
				_vec[i] = _vec[i - 1];
			_vec[pos] = val;
			return (begin() + pos);
		};
		void		insert(iterator position, size_type n, const value_type &val) {
			difference_type pos = position - begin();

			if (_cap <= _size + n)
				reserve(_size + n);
			_size = _size + n;
			for (size_t i = _size - 1; i > pos + n - 1; i--)
				_vec[i] = _vec[i - n];
			for (size_t i = pos; i < pos + n; i++)
				_vec[i] = val;
		};
		void		insert(iterator position, iterator first, iterator last) {
			difference_type range = last - first;
			difference_type pos = position - begin();
			
			if (_cap <= _size + range)
				reserve(_size + range);
			_size = _size + range;
			for (size_t i = _size - 1; i > (size_t)pos + (size_t)range - 1; i--)
				_vec[i] = _vec[i - range];
			iterator it = begin();
			while (first != last)
			{
				*(it + pos) = *first;
				first++;
				it++;
			}
		};
		iterator	erase(iterator position) {
			for (iterator it = position; it != end() - 1; it++)
				*it = *(it + 1);
			_size--;
			return (position);
		};
		iterator	erase(iterator first, iterator last) {
			difference_type range = last - first;

			for (difference_type i = first - begin(); i < end() - first; i++)
				_vec[i] = _vec[i + range];
			_size -= range;
			return (first);
		};
		void		swap(vector &x) {
			value_type	*tmp;
			size_type	tmpsize = _size;
			size_type	tmpcap = _cap;

			tmp = x._vec;
			x._vec = _vec;
			_vec = tmp;
			tmpsize = x._size;
			x._size = _size;
			_size = tmpsize;
			tmpcap = x._cap;
			x._cap = _cap;
			_cap = tmpcap;
		};
		void		clear() {
			_alloc.deallocate(_vec, _cap);
			_size = 0;
			_cap = 0;
		};

		private:
		value_type		*_vec;
		size_type		_size;
		size_type		_cap;
		allocator_type	_alloc;
	};

	/* Non-member function overloads */
	template <class T, class Alloc>
	bool	operator==(const vector<T> &lhs, const vector<T> &rhs) {
		if (lhs.size() != rhs.size())
			return (false);
		for (size_t i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return (false);
		return (true);
	};
	template <class T, class Alloc>
	bool	operator!=(const vector<T> &lhs, const vector<T> &rhs) {
		return (!(lhs == rhs));
	};
	template <class T, class Alloc>
	bool	operator<(const vector<T> &lhs, const vector<T> &rhs) {
		if (lhs.size()  == rhs.size() || lhs.size() > rhs.size())
			return (false);
		for (size_t i = 0; i < lhs.size(); i++)
			if (lhs[i] > rhs[i])
				return (false);
		return (true);
	};
	template <class T, class Alloc>
	bool	operator<=(const vector<T> &lhs, const vector<T> &rhs) {
		return (!(rhs < lhs));
	};
	template <class T, class Alloc>
	bool	operator>(const vector<T> &lhs, const vector<T> &rhs) {
		return (rhs < lhs);
	};
	template <class T, class Alloc>
	bool	operator>=(const vector<T> &lhs, const vector<T> &rhs) {
		return (!(lhs < rhs));
	};
	template <class T>
	void	swap (vector<T> &x, vector<T> &y) {
		x.swap(y);
	};
};

#endif
