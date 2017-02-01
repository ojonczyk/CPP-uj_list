#ifndef _UJ_LIST_H
#define _UJ_LIST_H

#include<iterator>
#include<iostream>
#include<algorithm>
#include<functional>
/** \mainpage Lista jednokierunkowa.
* Autor: Oskar Jonczyk
*/
namespace uj {
	/**	Lista jednokierunkowa.
	  */

	template<typename T>
	class list {

		class Iterator;
		/** Pojedynczy element listy.
		* Zawiera pole data,wsk na nastepny element oraz konstruktor.
		*/
		class Node
		{
			T data;
			Node * next;
			Node() : next(nullptr) { }
			Node(const T & val, Node * next_ = nullptr) : data(val), next(next_) { }
			friend class list;
			friend class iterator;
		};
		///@{
		/** Wsk na pierwszy i ostatni element oraz zmienny przechowywujaca rozmiar listy.
		*/
		Node * head;
		Node * tail;
		unsigned int size_;
		///@}
		
		/** Iterator po const elementach.
		*/
		class ConstIterator {
			/** Wskaznik na bierzacy element.
			*/
			Node * current;
			/** Konstruktor przyjmujacy element od ktorego chcemy zaczac.
			*/
			ConstIterator(Node * pos) : current(pos) {  }

			friend class list;

		public:
			///@{
			/** Typedef dla iterator_traits.
			*/
			typedef std::forward_iterator_tag iterator_category;
			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef const T * const_pointer;
			typedef const T & const_reference;
			///@}
			/** Konstruktor domyslny.
			*/
			ConstIterator() : current(nullptr) {  }
			/** Zwraca wartosc bierzacego elementu.
			*/
			const_reference operator*() {
				return current->next->data;
			}
			/** Zwraca wskaznik na wartosc bierzacego elementu.
			*/
			const_pointer operator->() {
				return &(current->next->data);
			}
			/** Preinkrementacja.
			*/
			ConstIterator & operator++() {
				current = current->next;
				return *this;
			}
			/** Postinkrementacja.
			*/
			ConstIterator operator++(int) {
				Iterator tmp = *this;
				current = current->next;
				return tmp;
			}
			/** Porownuje czy pozycje iteratorow sa rowne.
			*/
			bool operator==(const ConstIterator iter)
			{
				return current == iter.current;
			}
			/** Porownuje czy pozycje iteratorow sa rozne.
			*/
			bool operator!=(const ConstIterator iter)
			{
				return current != iter.current;
			}
		};
		/** Iterator po zwyklych elementach. Dziedziczy po ConstIterator.
		*/
		class Iterator : public ConstIterator {
			/** Konstruktor przyjmujacy startowa pozycje.
			*/
			Iterator(Node * pos) : ConstIterator(pos) {  }
			friend class list;
		public:
			typedef T * pointer;
			typedef T & reference;
			typedef std::forward_iterator_tag iterator_category;
			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			/** Konstruktor domyslny
			*/
			Iterator() : ConstIterator() {  }
			/** Zwraca wartosc bierzacego elementu.
			*/
			reference operator*() {
				return this->current->next->data;
			}
			/** Zwraca wskaznik na wartosc bierzacego elementu.
			*/
			pointer operator->() {
				return &(this->current->next->data);
			}
			Iterator operator++(int) {
				Iterator tmp = *this;
				this->current = this->current->next;
				return tmp;
			}
			Iterator & operator++() {
				this->current = this->current->next;
				return *this;
			}
		};

	public:
		///@{
		/** Dla iterator_traits
		*/
		typedef T value_type;
		typedef T * pointer;
		typedef const T * const_pointer;
		typedef T & reference;
		typedef const T & const_reference;
		typedef Iterator iterator;
		typedef size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef ConstIterator const_iterator;
		///@}
		/** Konstruktor domyslny listy.
		  *	Konstruuje pierwszy element i ustawia wartosci zmiennych.
		  */
		list() {
			head = new Node();
			tail = head;
			size_ = 0;
		}
		list(size_type n, const value_type& val) : list() {
			for (unsigned int i = 0; i < n; ++i) {
				push_back(val);
			}
		}
		/** Operator przypisania.
		*/
		list & operator=(const list & other)  {
			clear();
			for (auto it = other.begin(); it != other.end(); ++it) {
				push_back(*it);
			}
			return *this;
		}
		/** Kontruktor kopiujacy.
		*/
		list(const list & other) : list() {
			list<T> tempList;
			for (auto it = other.begin(); it != other.end(); ++it) {
				push_back(*it);
			}
		}
		template <class InputIterator>
		list(InputIterator first, InputIterator last) : list() {
			for (InputIterator it = first; it != last; ++it) {
				push_back(*it);
			}
		}
		/** Sprawdza czy lista jest pusta.
		*/
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last) {
			clear();
			for (InputIterator it = first; it != last; ++it) {
				push_back(*it);
			}
		}
		void assign(size_type n, const value_type& val) {
			clear();
			for (unsigned int i = 0; i < n; ++i) {
				push_back(val);
			}
		}
		void swap(list& other) {
			Node * tmpTail = other.tail;
			Node * tmpHead = other.head;
			int tmpSize = other.size_;
			other.head = head;
			other.tail = tail;
			other.size_ = size_;
			tail = tmpTail;
			head = tmpHead;
			size_ = tmpSize;
		}
		void resize(size_type n, value_type val = value_type()) {
			if (size_ < n) {
				for (unsigned int i = 0; i < n - size_; ++i) {
					push_back(val);
				}
			}
			if (size_ > n) {
				for (unsigned int i = 0; i < n - size_; ++i) {
					pop_back();
				}
			}
		}
		void remove(const value_type& val) {
			for (auto it = begin(); it != end(); ++it) {
				while (*it == val) erase(it);
			}
		}
		template <class Predicate>
		void remove_if(Predicate pred) {
			auto prev = begin();
			for (auto it = begin(); it != end(); ++it) {
				while (pred(*it)) {
					erase(it);
					it = prev;
				}
			}
		}
		template<typename Predicate>
		void unique(Predicate equal) {
			auto it = begin();

			while (it != end()) {
				auto it2 = it;
				++it2;
				while (it2 != end()) {
					if (equal(*it2, *it)) erase(it2);
					else ++it2;
				}
				it++;
			}
		}

		template <typename Predicate>
		void sort(Predicate comp) {
			auto end = tail;
			while (end != head->next) {
				auto it = head->next;
				while (true) {
					if (comp(it->next->data, it->data)) {
						auto tmp = it->data;
						it->data = it->next->data;
						it->next->data = tmp;
					}
					if (it->next == end) {
						end = it;
						break;
					}
					it = it->next;
				}
			}
		}

		void sort() {
			sort(std::less<T>());
		}

		
		template <typename Predicate>
		void merge(list& x, Predicate comp) {
			if (&x == this) return;
			auto it = begin();
			auto itx = x.begin();
			while (itx.current->next != nullptr) {
				while (it != end() && comp(*it, *itx)) ++it;

				auto tmp = itx.current->next->next;
				itx.current->next->next = it.current->next;
				it.current->next = itx.current->next;
				itx.current->next = tmp;
				if (it.current->next->next == nullptr) tail = it.current->next;
			}
			x.tail = x.head;
			size_ += x.size_;
			x.size_ = 0;
		}
		void merge(list& x) {
			merge(x, std::less<T>());
		}
		void reverse() {
			auto it = head->next;
			auto it_next = it->next;
			while (it_next != nullptr) {
				auto tmp = it_next->next;
				it_next->next = it;
				it = it_next;
				it_next = tmp;
			}
			tail = head->next;
			tail->next = nullptr;
			head->next = it;
		}

		void unique() {
			unique(std::equal_to<T>());
		}
		bool empty() const {
			return head->next == 0;
		}
		/** Zwraca iterator na pierwszym elemencie.
		*/
		iterator begin() {
			return iterator(head);
		}
		/** Zwraca iterator na ostatnim elemencie.
		*/
		iterator end() {
			return iterator(tail);
		}
		/** Zwraca const_iterator na pierwszym elemencie.
		*/
		const_iterator begin() const{
			return const_iterator(head);
		}
		/** Zwraca const_iterator na ostatnim elemencie.
		*/
		const_iterator end() const {
			return const_iterator(tail);
		}
		/** Umieszcza element w liscie na podanej pozycji.
		*/
		iterator insert(Iterator pos, const T & value) {
			if (size_ == 0) {
				head->next = new Node(value, 0);
				 tail = head->next;
				 ++size_;
				 return begin();

			}
			Node * new_ = new Node(value, pos.current->next);
			pos.current->next = new_;
			if (pos.current == tail) {
				tail = new_;
			}
			++size_;
			return pos;

		}
		/** Zwraca rozmiar listy.
		*/
		size_type size() const {
			return size_;
		}
		/** Usuwa pierwszy element listy.
		*/
		void pop_front() {
			if (size_ == 1) {
				delete head->next;
				head->next = 0;
				tail = head;
				--size_;
				return;
			}
			Node * tmp = head->next;
			head->next = head->next->next;
			delete tmp;
			--size_;
		}
		void pop_back() {
			if (size_ == 0) return;
			if (size_ == 1) {
				delete head->next;
				head->next = 0;
				tail = head;
				--size_;
				return;
			}
			Node * current = head;
			while (current->next != tail) current = current->next;
			delete current->next;
			current->next = nullptr;
			tail = current;
			--size_;
		}
		/** Czysci liste do rozmiaru 0.
		*/
		void clear() {
			while (size_ > 0) {
				pop_front();
			}
		}
		/** Destruktor.
		*/
		~list() {
			clear();
			delete head;
		}
		/** Wstawia element na koniec listy.
		*/
		void push_back(const T & val) {
			if (size_ == 0) {
				push_front(val);
				return;
			}
			insert(iterator(tail), val);
		}
		/** Wstawia element na poczatek listy.
		*/
		void push_front(const T & val) {
			Node * new_ = new Node(val, head->next);
			head->next = new_;
			if ( tail == head ){
			  tail = new_;
			}
			++size_;
		}
		void splice(Iterator position, list& x) {
			if (&x == this) return;
			x.tail->next = position.current->next;
			position.current->next = x.head->next;
			if (position.current == tail) tail = x.tail;
			size_ += x.size_;
			x.size_ = 0;
			x.head->next = nullptr;
			x.tail = x.head;
		}
		void splice(Iterator position, list& x, iterator i) {
			if (&x == this) return;
			if (i.current->next == x.tail) x.tail = i.current;

			auto tmp = i.current->next->next;

			i.current->next->next = position.current->next;
			position.current->next = i.current->next;

			i.current->next = tmp;

			if (position.current == tail) tail = position.current->next;

			size_++;
			x.size_--;
		}
		void splice(Iterator position, list& x, iterator first, iterator last) {
			if (&x == this || first == last) return;
			int counter = 0;
			for (auto it = first; it != last; ++it) ++counter;
			if (last.current == x.tail) x.tail = first.current;

			auto tmp = last.current->next;

			last.current->next = position.current->next;
			position.current->next = first.current->next;
			first.current->next = tmp;

			if (position.current == tail) tail = last.current;

			size_ += counter;
			x.size_ -= counter;
		}
		/** Usuwa element na podanej pozycji.
		*/
		iterator erase(Iterator pos) {
			if (pos.current == tail) {
				return 0;
				//throw exception
			}
			Node * tmp = pos.current->next;
			pos.current->next = tmp->next;
			if (tmp->next == nullptr) {
				tail = pos.current;
			}
			delete tmp;
			--size_;
			return pos;
		}
		reference front() {
			return head->next->data;
		}
		reference back() {
			return tail->data;
		}
	};
}

#endif
