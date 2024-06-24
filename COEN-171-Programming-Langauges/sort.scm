; vi:ai:list:sm

(define (quicksort lst)
	(if (null? lst) lst
		(let*
			((x (car lst))
			(xs (cdr lst))
			(above (lambda (y) (>= y x)))
			(below (lambda (y) (< y x))))
		(append (quicksort (filter below xs))
  		(cons x (quicksort (filter above xs)))))))
