(define (to-string thing)
  (let ([format-pair-tail
	 (lambda (tail)
	   (apply string-append (cond [(null? tail) (list "")]
				      [(pair? tail) (list " " (to-string tail))]
				      [else (list " . " (to-string tail))])))
	 ])
    (cond [(number? thing) (number->string thing)]
	  [(symbol? thing) (symbol->string thing)]
	  [(null? thing) "()"]
	  [(procedure? thing) "#function#"]
	  [(pair? thing) (string-append
			  (to-string (car thing))
			  (format-pair-tail (cdr thing)))]
	  [(string? thing) thing]
	  [else "?"]
	  )))

(define (create-dispatch methods super-func)
  (lambda (msg)
    (let ([method (assoc msg methods)])
      (if method (cdr method) ((super-func) msg))
      )))

(define (send obj msg . para)
  (let ((method (obj msg)))
    (apply method para)))

(define (new-instance class . para)
  (apply class (cons '() para)))

;; TODO implement str 
(define (object self-into)
  (letrec ([whoami 'object]
	   [dispatch (create-dispatch (list
				       [cons 'pretty-str (lambda ()
							   (to-string (send (self) 'pretty)))]
				       [cons 'pretty (lambda () (list whoami))]
				       [cons 'type-of (lambda () whoami)]
				       [cons 'class-of (lambda () object)]
				       ) '())]
	   [self (lambda () (if (null? self-into) dispatch self-into))]
	   ) dispatch))

(define (point self-into x y)
  (letrec ([whoami 'point]
	   [super (lambda () (object (self)))]
	   [self (lambda () (if (null? self-into) (dispatch) self-into))]
	   [pretty (lambda () (list whoami x y))]
	   [move (lambda (dx dy)
		   (send (self) 'add (new-instance point dx dy)))]
	   [add (lambda (other)
		  (new-instance (send (self) 'class-of) (+ x (send other 'getx))
		    (+ y (send other 'gety))
		    ))]
	   [with-color (lambda (color) (new-instance color-point
						(send (self) 'getx)
						(send (self) 'gety)
						color))]
	   [dispatch (lambda () (create-dispatch (list
						  [cons 'getx (lambda () x)]
						  [cons 'gety (lambda () y)]
						  [cons 'add add]
						  [cons 'pretty pretty]
						  [cons 'move move]
						  [cons 'type-of (lambda () whoami)]
						  [cons 'class-of (lambda () point)]
						  [cons 'with-color with-color]
						  ) super))]
	   ) (dispatch)))

(define p1 (new-instance point 10 20))
(define p2 (new-instance point 1 1))

(define (color-point self-into x y . color)
  (let ((color (if (null? color) 'green (car color))))
    (letrec ([whoami 'color-point]
	     [super (lambda () (point (self) x y))]
	     [self (lambda () (if (null? self-into) (dispatch) self-into))]
	     [pretty (lambda () (list whoami
				      (send (self) 'getx)
				      (send (self) 'gety)
				      color))]
	     [dispatch (lambda () (create-dispatch (list
						    [cons 'get-color (lambda () color)]
						    [cons 'type-of (lambda () whoami)]
						    [cons 'pretty pretty]
						    [cons 'class-of (lambda () color-point)]
						    ) super))]
	     ) (dispatch))))

;;# Exercise 3.7
;;? What is the value of the expression
(let ((x 1)
      (y 2)
      (z 3)
      (v 5))
  (cons x 
	(call/cc (lambda (e) 
		   (cons y  
			 (cons z 
			       (if (even? v) v (e (+ v 1)))))))))
;; Okay lets start by looking at it:
;; Okay, we define x y z and v
;; Then we create a cons with x and the continuations, so the result must be
;; something like (1 . ???)
;; If v is even, it will do some cons stuff with the other guys, but it's not.
;; Therefore the result of (call/cc ...) is (e (+ v 1)) which is 6.
;; Therefore the result must be (1 . 6)

;; Okay when running it is (1 . 6).

;;# Exercise 3.4
;;? Program (lambda (a b c) (- (* b b) (* 4 a c))) in CPS
(define (sub a b k)
  (k (- a b)))
(define (mult a b k)
  (k (* a b)))
(define (dist a b c k)
  (mult a c (lambda (v)
	      (mult 4 v (lambda (v1)
			  (mult b b (lambda (v2)
				      (sub v2 v1 k))))))))

(define dist-old (lambda (a b c) (- (* b b) (* 4 a c))))
