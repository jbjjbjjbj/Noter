(define (make-list-ft from to)
  (if (> from to)
      '()
      (cons from (make-list-ft (1+ from) to))))

;; Exercise 1.3 (proper lists)
;;? Program own version of list?, thus proper-list?
;; This is done by running to the end of list, always checking if pair.
;; If last element is '() its a proper list, otherwize its not.
(define (proper-list? list)
  (if (pair? list)
      (proper-list? (cdr list))
      (null? list)))

;;? Can you write your predicate without using if or cond?
;; Hmm i cant see how this would be done, as we are using recursion which requires a stop condition.

;;? Is your function efficient? What is the time complexity?
;; This runs over all the elements in the list, so O(n).
;; Hmm reading through the solution, i see that we can use other conditional functions like `or` and `and`.
;; Lets try that
(define (proper-list? list)
  (or (null? list) (and (pair? list) (proper-list? (cdr list)))))

;; Okay thats just his solution

;; Exercise 1.5 (every second element)
;; Hmm the text mentions that we could write it with (every-nth-element)
(define (every-nth-element n list)
  (let recur ((list list) (index 0))
    (cond ((null? list) '())
	  ((zero? (modulo index n)) (cons (car list) (recur (cdr list) (1+ index))))
	  (else (recur (cdr list) (1+ index))))))

(define (every-2th-element list)
  (every-nth-element 2 list))
