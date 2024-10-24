#include "SetIterator.h"
#include "Set.h"
#include <exception>
using namespace std;


SetIterator::SetIterator(const Set& m) : set(m)
{
	this->currentPosition = 0;
}
// BC = WC = TC: Theta(1)

void SetIterator::first() {
	this->currentPosition = 0;
}
// BC = WC = TC: Theta(1)

void SetIterator::next()
{
	if (this->currentPosition > this->set.maximum - this->set.minimum || this->set.setSize == 0)
	{
		throw exception();
	}	

	this->currentPosition++;
	while ((this->set.elements[this->currentPosition] == 0) && (this->set.minimum + this->currentPosition <= this->set.maximum))
		this->currentPosition++;
}
// BC: Theta(1) in the case where the next element is consecutive to the precedent one
// WC: Theta(capacity) in the case when the element are so far apart that one is at position 0, and the other at 1000000, as initialized.
// TC: O(capacity)

TElem SetIterator::getCurrent()
{
	if (this->currentPosition > this->set.maximum - this->set.minimum || this->set.setSize == 0)
	{
		throw exception();
	}	

	return this->currentPosition + this->set.minimum;
}
// BC = WC = TC: Theta(1), because we know exactly where an element would be found if it is in the set, the complexity does not change,
// computations are done by the next() function.

bool SetIterator::valid() const {
	return ((this->currentPosition < this->set.capacity) && (this->set.elements[this->currentPosition] == 1));
}
// BC = WC = TC: Theta(1)

void SetIterator::jumpBackward(int k) 
{
	if (k <= 0 || this->valid() == false)
	{
		throw exception();
	}

	int k_count = 0;

	while (this->currentPosition >= 0) // to check whether the position is still valid as we go backwards
	{
		this->currentPosition--;

		if (this->set.elements[this->currentPosition] == 1)
			k_count++; // we found an element in the set

		if (k_count == k)
			return; // we found the position, and it is ok, the currentPosition will remain intact
	}

	this->currentPosition = this->set.capacity + 1; // made the currentPosition invalid

}
// BC = Theta(1) if k is invalid or the iterator is invalid, or set to 0, as we cannot go back
// WC = Theta(capacity) if the elements are so far apart that they won't find k elements or it has to traverse a lot
// of elements to find anything (example, if the currentPosition is on the 1000000th element, and we need to go back
// to find the minimum element, at position 0)
// TC = O(capacity)

