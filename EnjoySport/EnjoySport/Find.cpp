#include "Find.h"

Find& Find::operator=(const Find& rhs)
{
	++*rhs.use;
	decr_use();
	q = rhs.q;
	use = rhs.use;
	return *this;
}
