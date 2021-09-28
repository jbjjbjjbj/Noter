;; This is not meant do be, please do not use define-syntax too much.
;; Just leaving this here to remember how it works.
(define-syntax lambda-curry
  (syntax-rules ()
    [(_ (x) b1 b2 ...)
     (lambda (x) b1 b2 ...)]
    [(_ (x r ...) b1 b2 ...)
     (lambda (x)
       (lambda-curry (r ...) b1 b2 ...)
       )]
    ))

(define-syntax call-curry
  (syntax-rules ()
    [(_ f x)
     (f x)]
    [(_ f x r ...)
     (call-curry (f x) r ...)]
    ))

;;# Exercise 2.21
;;? Create a differentiation function
;;? For the delta use a very small number ;-)
(define (diff f)
  (lambda (x)
    (let [(delta 0.00001)]
      (/ (- (f (+ delta x)) (f x)) delta))
    ))

;; Lets get a text function
(define (f x) (* x x))
(define (fd x) (* 2 x))

;;? Create compare-2-function which takes two functions and and array of numbers
(define (compare-2-funcs f1 f2 numbers)
  (map (lambda (num)
	 (- (f2 num) (f1 num)))
       numbers))

;; Yeah not tail recursive, but its fine
(define (linspace start stop step)
  (if (> start stop)
      '()
      (cons start (linspace (+ start step) stop step))
      ))

(define (accumulate f nul)
  (letrec [(self (lambda (lst)
		   (if (null? lst)
		       nul
		       (f (car lst) (self (cdr lst)))
		       ))
		 )] self))

(define sum (accumulate + 0))

;;# Exercise 2.11
;;? Create a generator function for (cmp x y) which takes a lt (less than) function.
;;? (cmp x y) returns -1 if x < y, 0 when x = y and 1 when x > y.
(define (make-cmp lt)
  (lambda (x y)
    (cond [(lt x y) -1]
	  [(lt y x) 1]
	  [else 0])
    ))

(define (from-cmp cmp)
  (let* ([lt (lambda (x y) (= -1 (cmp x y)))]
	 [gt (lambda (x y) (= 1 (cmp x y)))]
	 [eq (lambda (x y) (= 0 (cmp x y)))]
	 ) (values lt gt eq)))

;;# Exercise 2.2
(define (replication-to list len)
  (letrec ([recur (lambda (part len res)
		    (cond [(zero? len) res]
			  [(null? part) (recur list len res)]
			  [else (recur (cdr part) (1- len) (cons (car part) res))]
			  ))]
	   ) (reverse (recur list len '()))))

;;# Exercise 2.16
(define (for-all-1 lst p)
  ((accumulate (lambda (x y) (and y (p x))) #t) lst))

(define (there-exists lst p)
  ((accumulate (lambda (x y) (or y (p x))) #f) lst))

;; Wow im a bit stupid, but this is much easier with a filter function
;; The above one's too
;; I dont want to implement it right now
(define (there-exists-1 lst p)
  (car ((accumulate (lambda (x state) (let ([good (p x)])
					(cons (cond [(not (cdr state)) good]
						    [good #f]
						    [else #t])
					      (or good (cdr state))
					      ))) (cons #f #f)) lst)))

