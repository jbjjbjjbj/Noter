(define (make-list-ft from to)
  (if (> from to)
      '()
      (cons from (make-list-ft (1+ from) to))))

;;# Exercise 1.3 (proper lists)
;;? Program own version of list?, thus proper-list?
;; This is done by running to the end of list, always checking if pair.
;; If last element is '() its a proper list, otherwize its not.
(define (proper-list? list)
  (if (pair? list)
      (proper-list? (cdr list))
      (null? list)))

;;? Can you write your predicate without using if or cond?
;; Hmm i cant see how this would be done, as we are using recursion which requires a stop condition.
;; Hmm reading through the solution, i see that we can use other conditional functions like `or` and `and`.
;; Lets try that
(define (proper-list? list)
  (or (null? list) (and (pair? list) (proper-list? (cdr list)))))

;;? Is your function efficient? What is the time complexity?
;; This runs over all the elements in the list, so O(n).

;; Okay thats just his solution

;;# Exercise 1.5 (every second element)
;; Hmm the text mentions that we could write it with (every-nth-element)
(define (every-nth-element n list)
  (let recur ((list list) (index 0))
    (cond ((null? list) '())
	  ((zero? (modulo index n)) (cons (car list) (recur (cdr list) (1+ index))))
	  (else (recur (cdr list) (1+ index))))))

;; With letrec
(define (every-nth-element n list)
  (letrec ([recur (lambda (list index)
		    (cond [(null? list) '()]
			  [(zero?
			    (modulo index n)) (cons (car list) (recur (cdr list) (1+ index)))]
			  [else (recur (cdr list) (1+ index))]))])
    (recur list 0)))

(define (every-2th-element list)
  (every-nth-element 2 list))


;;# Exercise 1.6 (Creation of association list)
;;? Program a function pair-up that constructs an association list from a list of keys and a list of values
;;? Think of a reasonable solution in case the length of the key list is different from the length of the value list.
(define (pair-up keys values)
  (cond [(null? keys) '()]
	[(null? values) '()]
	[else (cons (cons (car keys) (car values))
		    (pair-up (cdr keys) (cdr values)))]))
  
;;# Exercise 1.7 (Association list and property lists)
;;? Program a function that converts an association list to a property list.
(define (assoc->prop lst)
  (if (null? lst)
      '()
      (let ([elem (car lst)])
	(cons (car elem) (cons (cdr elem) (assoc->prop (cdr lst)))))))

;;? Next, program the function that converts a property list to an association list.
(define (prop->assoc lst)
  (if (null? lst)
      '()
      (cons (cons (car lst) (cadr lst)) (prop->assoc (cddr lst)))))

;;# Exercise 1.8
;;? The function should return the value of key in property-list. Like assoc, get-prop should return #f if key is not found in property-list.
;;? How will you handle the case where the property list is malformed - a property list with an odd number of elements?
(define (get-prop lst index)
  (cond [(null? lst) #f]
	[(null? (cdr lst)) #f]
	[(eqv? (car lst) index) (cadr lst)]
	[else (get-prop (cddr lst) index)]
	))

;;? Discuss pros and cons of property lists and get-prop, compared to association lists and assoc.
;; I don't see many pros of property lists, feels kind of like a hack.
;; If you get a snippet of a property list, it's impossible to know where keys and values are.
;; One pro is that they are easier to write out by hand.

;;? Does the #f value, returned in cases where we do not find the key, bother you?
;; YEEEES WTF
;; What if you want to store booleans, with the possability of having false values.
;; Then you have to wrap booleans in something else, like a one element list.

;;# Exercise (list tail counterpart)
;;? Program your own version of list-tail. Call it my-list-tail.
(define (my-list-tail lst index)
  (cond [(null? lst) '()]
	[(zero? index) lst]
	[else (my-list-tail (cdr lst) (1- index))]
	))

;;? Next, program a function list-prefix which is a prefix counterpart to list-tail. (list-prefix lst n) returns a prefix of the list of length n.
(define (list-prefix lst index)
  (cond [(null? lst) '()]
	[(zero? index) (cons (car lst) '())]
	[else (cons (car lst) (list-prefix (cdr lst) (1- index)))]
	))

;;? Reflect on the difference between these two functions. Which one is most expensive in terms of memory allocation?
;; list-prefix builds up a copy of the existing array with consts.
;; Therefore a new const is created at each recursive step of the evaluation, which requires more space.
;; my-list-tail can just return the existing tail, without allocating a new array.
