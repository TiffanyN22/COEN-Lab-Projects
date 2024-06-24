; vi::ai::lisp::sm

(define (left-child t) (cadr t))
(define (right-child t) (caddr t))
(define (data t) (car t))
(define (make-leaf v) (list v '() '()))

(define (insert lst x)
	(cond
		((null? lst) (make-leaf x))
		((< x (data lst)) (list (data lst) (insert (left-child lst) x)(right-child lst)))
		(else (list (data lst) (left-child lst) (insert (right-child lst) x)))))

(define (member? lst x)
	(cond
		((null? lst) #f)
		((< x (data lst)) (member? (left-child lst) x))
		((> x (data lst)) (member? (right-child lst) x))
		(else #t)))

(define (inorderTraversal lst)
	(if (null? lst) lst 
	(append(inorderTraversal (left-child lst)) (cons (data lst) (inorderTraversal (right-child lst))))))
