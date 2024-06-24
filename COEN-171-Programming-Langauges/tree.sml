(* define tree datatype*)
datatype tree = Empty | Node of tree * int * tree;

(* insert = fn: tree --> int --> tree
Returns a binary search tree with x inserted at the correct position *)
fun insert Empty x = Node(Empty, x, Empty)
    | insert (Node(l, d, r)) x =
        if x < d then Node(insert l x, d, r)
        else Node(l, d, insert r x);

(* bulid = fn: int list -> tree
 Return a tree that is result of inserting all integers in the given list *)
val build = foldl(fn(v,t) => insert t v) Empty;

(* inorder = fn : tree -> int list
  Returns a list that contains all integers in the tree in order *)
fun inorder Empty = []
    |inorder (Node(l,d,r)) = inorder l @ d :: inorder r;

(* member = fn: tree -> int --> bool
 Returns true if the integer x is in the tree and false if not  *)
fun member Empty x = false
    | member (Node(l, d, r)) x =
	if x < d then member l x
	else if x > d then member r x
	else true;
