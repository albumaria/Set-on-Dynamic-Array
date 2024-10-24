#include "Set.h"
#include "SetITerator.h"
#include <iostream>
using namespace std;

Set::Set() {
	this->capacity = 10000;
	this->setSize = 0;
	this->minimum = NULL_TELEM;
	this->maximum = NULL_TELEM;

	this->elements = new TElem[this->capacity];

	for (int i = 0; i < this->capacity; i++)
		this->elements[i] = 0;
}
// BC = WC = TC: Theta(n), where n is the capacity of the set = 10000000

bool Set::add(TElem elem) {
	if (this->minimum == NULL_TELEM) { //if we found the first minimum(first element added)
		this->minimum = elem;
		this->maximum = elem;
		this->elements[0] = 1;
		this->setSize++;
		return true;
	}
	
	else if (elem < this->minimum) 
	{ //if we found a new minimum
		int nr_shifts = this->minimum - elem;

		for (int i = this->capacity - 1; i >= this->capacity - nr_shifts; i--) {
			if (this->elements[i] == 1) 
			{
				//resize
				int new_capacity = this->capacity * 10;
				TElem* resizer = new TElem[new_capacity]();
				for (int j = 0; j <= this->maximum - this->minimum; j++)
					resizer[j] = this->elements[j];

				delete[] this->elements;
				this->elements = resizer;
				i = -1;
			}
				
		}
		//if it passed the test, then we can do the shifting, and add the element:

		for (int i = this->maximum - this->minimum + nr_shifts; i - nr_shifts >= 0; i--) 
			this->elements[i] = this->elements[i - nr_shifts];

		for (int i = 1; i < nr_shifts; i++)
			this->elements[i] = 0;

		this->elements[0] = 1;
		this->minimum = elem;
		this->setSize++;

		return true;
	}

	else if (this->capacity - 1 + minimum < elem) //if the element cannot be represented in the current set, as it is too big
	{
		//resize
		int new_capacity = this->capacity * 10;
		TElem* resizer = new TElem[new_capacity]();

		for (int i = 0; i <= this->maximum - this->minimum; i++)
			resizer[i] = this->elements[i];

		delete[] this->elements;
		this->elements = resizer;

	}

	else if (this->elements[elem - this->minimum] == 1) //cannot add element to set twice
		return false;

	else if (this->maximum < elem)
		this->maximum = elem;

	this->elements[elem - this->minimum] = 1;
	this->setSize++;
	return true;
	
}
// BC: Theta(1), in case that the added element is the first of the set, or when trying to add an element twice, or when the element cannot be
// represented in the current set capacity, or when minimum < element < maximum
// WC: Theta(nr_shifts + nr_shifts + nr_shifts) = Theta(nr_shifts), in the case when we want to add a new minimum and we need to shift elements
// TC: O(nr_shifts)


bool Set::remove(TElem elem) {
	if (this->setSize == 0)
		return false;

	else if (this->minimum == elem) {
		if (this->setSize == 1) {
			this->elements[0] = 0;
			this->minimum = NULL_TELEM;
			this->maximum = NULL_TELEM;
			this->setSize = 0;
			return true;
		}
		int i;

		for (i = 1; i < this->maximum - this->minimum; i++) //find the next position where there's a 1
			if (this->elements[i] == 1)
				break;

		int nr_shifts = i; //the spaces until the next 1
		int new_minimum = this->minimum + i; //saving the minimum

		for (i = 0; i + nr_shifts <= this->maximum - this->minimum; i++)
			this->elements[i] = this->elements[i + nr_shifts];

		// i = this->maximum - this->minimum - nr_shifts

		for (int j = i; j <= this->maximum - this->minimum; j++)
			this->elements[j] = 0;

		this->minimum = new_minimum;
		this->setSize--;

		return true;
	}

	else if (elem - this->minimum > this->capacity - 1 || elem < this->minimum)
		return false; // outside of representation size

	else if (this->maximum == elem) {
		for (int i = this->maximum - this->minimum - 1; i >= 0; i--)
			if (this->elements[i] == 1) {
				this->maximum = i + this->minimum;
				this->elements[elem - this->minimum] = 0;
				this->setSize--;
				return true;
			}
	}

	else if (this->elements[elem - this->minimum] == 1) {
		this->elements[elem - this->minimum] = 0;
		this->setSize--;
		return true;	
	}	
	return false;
}
// BC: Theta(1), in the case when the set is empty, or when the element is outside of the representation range, or when minimum < element < maximum, 
// or when the element == minimum and the set has only one element
// WC: Theta(nr_shifts), when the element to remove is equal to the minimum and the setSize > 1, 
// because of the shifting. Here, the nr_shifts cannot be calculated and instead, has to be found as the next element in the set. 
// This can be quite lengthy in cases where the minimum and the maximum are very far away from each other. 
// This complexity also applies when the element == maximum, because we need to find the next most maximal element.
// This means that in reality, nr_shifts represent almost the same thing, the nr. of positions from the minimum to the next bigger smallest element,
// respectively from the maximum to the next smaller biggest element.
// TC: O(nr_shifts), as explained above

bool Set::search(TElem elem) const {
	if (elem < this->minimum || elem > ((capacity - 1) + minimum)) { //out of bounds
		return false;
	}

	return this->elements[elem - this->minimum]; // check later for discrepancy
}
// BC: Theta(1) if the element is out of bounds
// WC: Theta(1), we know exactly where the element would be, because of the way the set is implemented
// TC: Theta(1)


int Set::size() const {
	return this->setSize;
}
// BC = WC = TC: Theta(1)


bool Set::isEmpty() const {
	return this->setSize == 0;
}
// BC = WC = TC: Theta(1)

Set::~Set() {
	delete[] elements;
}
// BC = WC = TC: Theta(n), where n is the capacity.

SetIterator Set::iterator() const {
	return SetIterator(*this);
}



