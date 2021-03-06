(display "loading aod/core\n")
;; putting the autload info here, among other necessary things (that I use often)
(provide 'aod.core)

(load "aod/autoloads.scm")
;; comment, map-indexed, dotimes, range, mod
;; on the (rootlet)
(require aod.clj)

;; ignornig tests: test expansion/macro replaced in aod.test
(define-expansion (test . body) #<unspecified>)
(define-expansion (testgui . body) #<unspecified>)

(define (filter pred col)
  (let loop ((res (list ))
	     (s col))
    (if (pair? s)
	(begin
	  (when (pred (car s))
	    (set! res (append res (list (car s)))))
	  (loop res (cdr s)))
	res)))

(comment
 (filter (lambda (x)
	   (> x 0))
	 '( 0 1 2 -1 -5 10))
 ;; => (1 2 10)
 )

(define (print . args)
  (format *stderr* "~A\n" (apply string-append
				 (map
				  (lambda (x)
				    (format #f "~A " x)
				    )
				  args))))

;; returns the last argument
;; useful for in-drop debugging, printing what we return
(define (print-ret . args)
  (apply print args)
  (if (pair? args)
      (car (reverse args))
      ()))

(comment
 (print 'a 'b "aasa" '(a b c))

 (let->list (curlet))
 ((curlet) (string->symbol "lines"))
 geom/echo
 )

;; hmm not sure how it's useful
;; from s7.html
(define (concat . args)
  (apply append (map (lambda (arg) (map values arg)) args)))

;; aod.ns has tests and may make some use of the rest of
;; internal funtions, so requiring at the end
(require aod.ns)

(define (memoize fn)
  (let ((mem (make-hash-table)))
    (lambda args
      (or (mem args)
	  (begin
	    ;; (print "not found, fn" fn "args " args)
	    (let ((ret (apply fn args)))
	      ;; (print "ret " ret)
	      (set! (mem args) ret)
	      ret))))))

;; if-let, when-let
;; only for one variable
;; TODO
;; - validate input? only one
;; syntax is clj like, passing one list (symbol val)
;; eg (when-let (x #f) ..)
(define-macro (if-let binding then else)
  `(let ((,(car binding) ,(cadr binding)))
     (if ,(car binding)
	 ,then
	 ,else)))

(define-macro (when-let binding . body)
  `(let ((,(car binding) ,(cadr binding)))
     (when ,(car bindings)
       ,@body)))

;; from s7 stuff.scm
(define-macro (and-let* vars . body)      ; bind vars, if any is #f stop, else evaluate body with those bindings
  (if (list? vars)
      `(let () (and ,@(map (lambda (v) (cons 'define v)) vars) (begin ,@body)))
      (error 'wrong-type-arg "and-let* var list is ~S" vars)))

(define when-let* and-let*)

(define-macro (if-let* vars then else)      ; bind vars, if all are #t evaluate "then", otherwise "else"
  (if (list? vars)
      `(let ()
	 (if (and ,@(map (lambda (v) (cons 'define v)) vars))
	     ,then
	     ,else))
      (error 'wrong-type-arg "and-let* var list is ~S" vars)))

(comment
 (if-let (x #t)
	 1
	 2)

 (when-let (x #f)
	   (print "one")
	   (print "two"))
 
 (if-let* ((x #t)
	  (y #t))
	 (print "true?")
	 (print "false?"))

 (when-let* ((x #f))
	   (print "this")
	   (print "that"))
 )
