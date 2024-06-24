partition(_, [], [], []).
partition(Pivot, [H|T], Below, [H|Above]) :- Pivot < H, partition(Pivot, T, Below, Above).
partition(Pivot, [H|T], [H|Below], Above) :- Pivot >= H, partition(Pivot, T, Below, Above).

quicksort([], []).
quicksort([H|T], Sorted) :-
	partition(H, T, Below, Above),
	quicksort(Below, BelowSorted),
	quicksort(Above, AboveSorted),
	append(BelowSorted, [H|AboveSorted], Sorted).
