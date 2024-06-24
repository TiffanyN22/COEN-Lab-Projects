insert(X, empty, node(empty, X, empty)).
insert(X, node(L, X, R), node(L, X, R)).
insert(X, node(L, Y, R), node(LN, Y, R)) :-
	X < Y, insert(X, L, LN).
insert(X, node(L, Y, R), node(L, Y, RN)) :-
	X > Y, insert(X, R, RN).

exists(X, node(_, X, _)).
exists(X, node(L, Y, _)) :-
	X < Y, exists(X, L).
exists(X, node(_, Y, R)) :-
	X > Y, exists(X, R).
