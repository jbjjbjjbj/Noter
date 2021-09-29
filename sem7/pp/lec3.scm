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

(define (send obj msg . para)
  (let ((method (obj obj msg)))
    (apply method para)))

(define (new-instance class . para)
  (apply class para))

;; TODO implement str 
(define (object)
  (let ([whoami 'object])
    (lambda (self msg)
      (cond [(eq? msg 'pretty-str) (lambda () (to-string (send self 'pretty)))]
            [(eq? msg 'pretty) (lambda () (list whoami))]
            [(eq? msg 'type-of) (lambda () whoami)]
            [(eq? msg 'class-of) (lambda () object)]
            [else (errorf object "msg ~a not found" msg)])
      )))

(define (point x y)
  (let ([whoami 'point]
        [super (object)])
    (lambda (self msg)
      (cond [(eq? msg 'getx) (lambda () x)]
            [(eq? msg 'gety) (lambda () y)]
            [(eq? msg 'add) (lambda (other)
                              (new-instance (send self 'class-of)
                                            (+ x (send other 'getx))
                                            (+ y (send other 'gety))
                                            ))]
            [(eq? msg 'pretty) (lambda () (list whoami x y))]
            [(eq? msg 'move) (lambda (dx dy)
                               (send self 'add (new-instance point dx dy)))]
            [(eq? msg 'type-of) (lambda () whoami)]
            [(eq? msg 'class-of) (lambda () point)]
            [(eq? msg 'with-color) (lambda (color)
                                     (new-instance color-point
                                                   (send self 'getx)
                                                   (send self 'gety)
                                                   color))]
            [else (super self msg)]))
    ))


(define p1 (new-instance point 10 20))
(define p2 (new-instance point 1 1))

(define (color-point x y . color)
  (let ([color (if (null? color) 'green (car color))]
        [whoami 'color-point]
        [super (point x y)])
    (lambda (self msg)
      (cond [(eq? msg 'get-color) (lambda () color)]
            [(eq? msg 'type-of) (lambda () whoami)]
            [(eq? msg 'pretty) (lambda ()
                                 (list whoami
                                       (send self 'getx)
                                       (send self 'gety)
                                       (send self 'get-color)))]
            [(eq? msg 'class-of) (lambda () color-point)]
            [else (super self msg)]))
    ))

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
