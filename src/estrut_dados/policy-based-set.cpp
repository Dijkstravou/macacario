#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

// Antes era pb_ds;
using namespace __gnu_pbds;

typedef tree<
	int,  //  Key type
	null_type,  // Mapped type.
	// null_mapped_type for older versions
	less<int>,  // Key comp function
	rb_tree_tag,  
	tree_order_statistics_node_update
> ordered_set;

// iterator find_by_order(int pos)
// iterator order_of_key(Key key)
