;; Needed definitions
(define-syntax cons-stream
  (syntax-rules ()
    ((cons-stream x y)
     (cons x (delay y)))))

(define head car)

(define (tail stream) (force (cdr stream)))

(define empty-stream? null?)

(define the-empty-stream '())


(define (stream-section n stream)
  (cond ((= n 0) '())
	(else (cons (head stream)
		    (stream-section 
		     (- n 1)
		     (tail stream))))))

(define (add-streams s1 s2)
  (let ((h1 (head s1))
	(h2 (head s2)))
    (cons-stream 
     (+ h1 h2)
     (add-streams (tail s1) (tail s2)))))

(define ones (cons-stream 1 ones))

(define nat-nums 
 (cons-stream 1 
  (add-streams ones nat-nums)))

;;# Exercise 4.2
;;? Make a stream of factorial numbers.
;;? Use a helper function combine-streams that combines streams
;;? with a binary function.

(define (combine-streams op a b)
  (cons-stream (op (head a) (head b))
	       (combine-streams op (tail a) (tail b))
	       ))

(define fib-stream
  (cons-stream 1
	       (combine-streams *
				(tail nat-nums)
				fib-stream)))

;;# Exercise 4.4
;;? Create a stream that converges on the square root of x.
;;? The initial guess is 1.0 and the rest is done with newtons method.
;;-- BEGIN FUNCTIONS GIVEN
(define (improve-sqrt-guess guess x)
  (/ (+ guess (/ x guess)) 2))
(define (map-stream f stream)
  (cond ((empty-stream? stream) the-empty-stream)
        (else (cons-stream (f (head stream)) (map-stream f (tail stream))))))
;;-- END

(define (newton-approx-stream x)
  (letrec
      ([res (cons-stream 1.0 (map-stream (lambda (g) (improve-sqrt-guess g x)) res))]
       ) res))

;;# Exercise 4.3
;;? Program af append-streams. How will it work for infinite lists.
;; Hmm this seems kind of useless if the first is an infinite list.
(define (append-streams a b)
  (if (empty-stream? a)
      b
      (cons-stream (head a) (append-streams (tail a) b))))

(define finite-test-stream
  (cons-stream 'a (cons-stream 'b (cons-stream 'c the-empty-stream))))

;;? Now program a merge-streams that alternates two streams
;; This is more like it, here is makes sense even if both are infinite
(define (merge-streams a b)
  (cond [(empty-stream? a) b]
	[(empty-stream? b) a]
	[else (cons-stream (head a) (cons-stream (head b) (merge-streams
							   (tail a)
							   (tail b))))]
	))

;;? Now use the merge to create a list of all natural numbers.
(define (negate x) (* -1 x))
(define all-integers
  (cons-stream 0
	       (merge-streams nat-nums
			      (map-stream negate nat-nums))))
